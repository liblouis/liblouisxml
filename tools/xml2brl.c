/* liblouisxml Braille Transcription Library

   This file may contain code borrowed from the Linux screenreader
   BRLTTY, copyright (C) 1999-2006 by
   the BRLTTY Team

   Copyright (C) 2004, 2005, 2006
   ViewPlus Technologies, Inc. www.viewplus.com
   and
   JJB Software, Inc. www.jjb-software.com
   All rights reserved

   This file is free software; you can redistribute it and/or modify it
   under the terms of the Lesser or Library GNU General Public License 
   as published by the
   Free Software Foundation; either version 3, or (at your option) any
   later version.

   This file is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
   Library GNU General Public License for more details.

   You should have received a copy of the Library GNU General Public 
   License along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.

   Maintained by John J. Boyer john.boyer@jjb-software.com
   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "louisxml.h"

int
main (int argc, char **argv)
{
  int curarg = 1;
  int mode = dontInit;
  char *configFileName = NULL;
  char *inputFileName = NULL;
  char *outputFileName = NULL;
  char tempFileName[MAXNAMELEN];
  char *logFileName = NULL;
  char whichProc = 0;
  char *configSettings = NULL;
  FILE *inputFile = NULL;
  FILE *tempFile;
  int ch = 0;
  int pch = 0;
  int nch = 0;
  int charsRead = 0;
  int k;
  UserData *ud;
  while (curarg < argc)
    {
      if (argv[curarg][0] == '-')
	switch (argv[curarg][1])
	  {
	  case 'h':
	    printf
	      ("Usage: xml2brl [Options] [-f configFile] [inputFile] [outputFile]\n");
	    printf
	      ("-f configFile: configuration file name, default: default.cfg.\n");
	    printf ("inputFile : input file, '--' means stdin\n");
	    printf ("outputFile : output file\n");
	    printf ("xml2brl with no argumenst takes input on stdin\n");
	    printf ("and gives output on stdout.\n");
	    printf ("OPTIONS\n");
	    printf ("-h, print this message and exit.\n");
	    printf ("-b, back-translate a braille file.\n");
	    printf ("-r, reformat a braille file.\n");
	    printf ("-p, translate a Poorly formattted file.\n");
	    printf ("[-t]: h(t)ml document, not xhtml");
	    printf ("[-l]: write errors to log file instead of stderr.\n");
	    exit (0);
	  case 'l':
	    logFileName = "xml2brl.log";
	    break;
	  case 'f':
	    if (argc < (curarg + 1))
	      {
		fprintf (stderr, "No configuration file!");
		exit (1);
	      }
	    configFileName = argv[curarg + 1];
	    curarg++;
	    break;
	  case 't':
	    mode |= htmlDoc;
	    break;
	  case 'b':
	  case 'p':
	  case 'r':
	  case 'x':
	    whichProc = argv[curarg][1];
	    break;
	  case 'C':
	    if (configSettings == NULL)
	      {
		configSettings = malloc (BUFSIZE);
		configSettings[0] = 0;
	      }
	    strcat (configSettings, &argv[curarg][2]);
	    strcat (configSettings, "\n");
	    break;
	  case '-':
	    inputFileName = "stdin";
	    break;
	  default:
	    fprintf (stderr, "Invalid option %s.\n", argv[curarg]);
	    exit (1);
	  }
      else
	{
	  if (inputFileName == NULL)
	    inputFileName = argv[curarg];
	  else
	    outputFileName = argv[curarg];
	}
      curarg++;
    }
  if (whichProc == 0)
    whichProc = 'x';
  if (configFileName == NULL)
    configFileName = "default.cfg";
  if (inputFileName == NULL)
    inputFileName = "stdin";
  if (outputFileName == NULL)
    outputFileName = "stdout";
  if (configSettings != NULL)
    for (k = 0; configSettings[k]; k++)
      if (configSettings[k] == '=')
	configSettings[k] = ' ';
  if ((ud = lbx_initialize (configFileName, logFileName,
			    configSettings)) == NULL)
    exit (1);
  if (strcmp (inputFileName, "stdin") != 0)
    {
      if (!(inputFile = fopen (inputFileName, "r")))
	{
	  lou_logPrint ("Can't open file %s.\n", inputFileName);
	  exit (1);
	}
    }
  else
    inputFile = stdin;
  /*Create somewhat edited temporary file to facilitate use of stdin. */
  strcpy (tempFileName, ud->writeable_path);
  strcat (tempFileName, "xml2brl.temp");
  if (!(tempFile = fopen (tempFileName, "w")))
    {
      lou_logPrint ("Can't open temporary file.\n");
      exit (1);
    }
  if (whichProc == 'p')
    {
      int ppch = 0;
      int firstCh = 0;
      int skipit = 0;
      while ((ch = fgetc (inputFile)) != EOF)
	{
	  if (firstCh == 0)
	    firstCh = ch;
	  if (ch == 12 || ch == 13)
	    continue;
	  if (ch == '<' && firstCh == '<')
	    {
	      skipit = 1;
	      continue;
	    }
	  if (skipit)
	    {
	      if (ch == '>')
		skipit = 0;
	      continue;
	    }
	  if (ch <= 32 && pch <= 32)
	    continue;
	  if (ch == '-')
	    {
	      nch = fgetc (inputFile);
	      if (nch == 10)
		continue;
	      ungetc (nch, inputFile);
	    }
	  if (!(pch == 10 && ((ppch >= 97 && ppch <= 122) || ppch == ',')))
	    {
	      if (pch == 10 && ch < 97)
		fputc (10, tempFile);
	    }
	  ppch = pch;
	  pch = ch;
	  fputc (ch, tempFile);
	  charsRead++;
	}
    }
  else
    while ((ch = fgetc (inputFile)) != EOF)
      {
	if (charsRead == 0 && ch <= ' ')
	  continue;
	if (ch == 13)
	  continue;
	if (charsRead == 0)
	  {
	    if (ch != '<' && whichProc == 'x')
	      whichProc = 't';
	    nch = fgetc (inputFile);
	    if (!(mode & htmlDoc) && whichProc == 'x' && nch != '?')
	      fprintf (tempFile, "%s\n", ud->xml_header);
	  }
	if (pch == '>' && ch == '<')
	  fputc (10, tempFile);
	fputc (ch, tempFile);
	pch = ch;
	charsRead++;
	if (charsRead == 1)
	  {
	    fputc (nch, tempFile);
	    charsRead++;
	  }
      }
  fclose (tempFile);
  if (inputFile != stdin)
    fclose (inputFile);
  if (charsRead > 2)
    switch (whichProc)
      {
      case 'b':
	lbx_backTranslateFile (configFileName, tempFileName,
			       outputFileName, mode);
	break;
      case 'r':
	{
	  char temp2FileName[MAXNAMELEN];
	  strcpy (temp2FileName, ud->writeable_path);
	  strcat (temp2FileName, "xml2brl2.temp");
	  if ((lbx_backTranslateFile (configFileName, tempFileName,
				      temp2FileName, mode)) != 1)
	    exit (1);
	  if (ud->back_text == html)
	    lbx_translateFile (configFileName, temp2FileName,
			       outputFileName, mode);
	  else
	    lbx_translateTextFile (configFileName, temp2FileName,
				   outputFileName, mode);
	}
	break;
      case 't':
      case 'p':
	lbx_translateTextFile (configFileName, tempFileName,
			       outputFileName, mode);
	break;
      case 'x':
	lbx_translateFile (configFileName, tempFileName, outputFileName,
			   mode);
	break;
      default:
	lou_logPrint ("Program bug %c\n", whichProc);
	break;
      }
  lbx_free ();
  if (configSettings != NULL)
    free (configSettings);
  return 0;
}
