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

/* Contributed by Michel Such <michel.such@free.fr */
#ifdef _WIN32

/* Adapted from BRLTTY code (see sys_progs_wihdows.h) */

#include <shlobj.h>

static void
noMemory (void)
{
  printf ("Insufficient memory: %s", strerror (errno), "\n");
  exit (3);
}

void *
reallocWrapper (void *address, size_t size)
{
  if (!(address = realloc (address, size)) && size)
    noMemory ();
  return address;
}

char *
strdupWrapper (const char *string)
{
  char *address = strdup (string);
  if (!address)
    noMemory ();
  return address;
}

char *
getProgramPath (void)
{
  char *path = NULL;
  HMODULE handle;

  if ((handle = GetModuleHandle (NULL)))
    {
      size_t size = 0X80;
      char *buffer = NULL;

      while (1)
	{
	  buffer = reallocWrapper (buffer, size <<= 1);

	  {
	    DWORD length = GetModuleFileName (handle, buffer, size);

	    if (!length)
	      {
		printf ("GetModuleFileName\n");
		exit (3);
		3;
	      }

	    if (length < size)
	      {
		buffer[length] = 0;
		path = strdupWrapper (buffer);

		while (length > 0)
		  if (path[--length] == '\\')
		    break;

		strncpy (path, path, length + 1);
		path[length + 1] = '\0';
		break;
	      }
	  }
	}

      free (buffer);
    }
  else
    {
      printf ("GetModuleHandle\n");
      exit (3);
    }

  return path;
}
#endif
/* End of MS contribution */

static char *lastPath = NULL;

static int
addPath (const char *path)
{
  int k;
  int curLen = strlen (ud->path_list);
  if ((curLen + 1 + strlen (path)) >= sizeof (ud->path_list))
    return 0;
  if (path[0] == 0)
    return 1;
  for (k = 0; path[k]; k++)
    if (path[k] == ',')
      {
	lou_logPrint ("Path %s must not contain a comma", path);
	return 0;
      }
  if (curLen > 0)
    {
      ud->path_list[curLen++] = ',';
      ud->path_list[curLen] = 0;
    }
  lastPath = &ud->path_list[strlen (ud->path_list)];
  strcpy (lastPath, path);
  return 1;
}

int
set_paths (const char *configPath)
{
  char currentPath[MAXNAMELEN];

/*Set configuration path first*/
  if (configPath[0] != 0)
    {
      if (!addPath (configPath))
	return 0;
    }

/*Set other paths here*/
#ifdef _WIN32
/* Set Windows Paths */
  {
    char louisPath[MAXNAMELEN];
    char lbxPath[MAXNAMELEN];
    strcpy (currentPath, getProgramPath ());
    strcat (currentPath, "..\\");
    if (!addPath (currentPath))
      return 0;
    strcpy (lbxPath, currentPath);
    strcat (lbxPath, "share\\liblouisxml\\lbx_files\\");
    addPath (lbxPath);
    strcpy (louisPath, currentPath);
    strcat (louisPath, "share\\liblouis\\tables\\");
    addPath (louisPath);
  }
#else
/* Set Unix paths (Linux, Mac OS X, etc.) */
  addPath (LIBLOUIS_TABLES_PATH);
  addPath (LBX_PATH);
#endif /*WWIN32 */

/* set current directory last*/
  currentPath[0] = '.';
  currentPath[1] = ud->file_separator;
  currentPath[2] = 0;
  if (!addPath (currentPath))
    return 0;
  ud->writeable_path = lastPath;
  return 1;
}
