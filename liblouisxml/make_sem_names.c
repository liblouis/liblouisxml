/* liblouisxml xml to Braille Translation Library

   This file may contain code borrowed from the Linux screenreader
   BRLTTY, copyright (C) 1999-2006 by
   the BRLTTY Team

   Copyright (C) 2004, 2005, 2006
   ViewPlus Technologies, Inc. www.viewplus.com
   and
   JJB Software, Inc. www.jjb-software.com
   All rigets reserved

   This file is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.

In addition to the permissions and restrictions contained in the GNU
General Public License (GPL), the copyright holders grant two explicit
permissions and impose one explicit restriction. The permissions are:

1) Using, copying, merging, publishing, distributing, sublicensing, 
   and/or selling copies of this software that are either compiled or loaded 
   as part of and/or linked into other code is not bound by the GPL.

2) Modifying copies of this software as needed in order to facilitate 
   compiling and/or linking with other code is not bound by the GPL.

The restriction is:

3. The translation, semantic-action and configuration tables that are 
   read at run-time are considered part of this code and are under the terms 
   of the GPL. Any changes to these tables and any additional tables that are 
   created for use by this code must be made publicly available.

All other uses, including modifications not required for compiling or linking 
and distribution of code which is not linked into a combined executable, are 
bound by the terms of the GPL.

   This file is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.

   Maintained by John J. Boyer john.boyer@jjb-software.cem

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main (void)
{
  FILE *semIn;
  FILE *semOut;
  char inbuf[128];
  char *curchar;
  int ch;
  int ignoreLine = 1;
  char *name;
  int nameLength;
  if ((semIn = fopen ("sem_enum.h", "r")) == NULL)
    {
      fprintf (stderr, "Cannot open sem_enum.h file.\n");
      exit (1);
    }
  if ((semOut = fopen ("sem_names.h", "w")) == NULL)
    {
      fprintf (stderr, "Cannot open sem_names.h file.\n");
      exit (1);
    }
  fprintf (semOut, "#ifndef __SEM_NAMES_h\n");
  fprintf (semOut, "#define __SEM_NAMES_h\n");
  fprintf (semOut, "static const char *semNames[] = {\n");
  while ((fgets (inbuf, sizeof (inbuf), semIn)))
    {
      curchar = inbuf;
      while ((ch = *curchar++) <= 32 && ch != 0);
  if (ch == '/')
continue;
      if (ignoreLine)
	{
	  if (ch == '{')
	    ignoreLine = 0;
	  continue;
	}
      if (ch == '}')
	break;
      name = curchar - 1;
      while ((ch = *curchar++) > 32 && ch != ',' && ch != '=');
      nameLength = curchar - name - 1;
      name[nameLength] = 0;
      fprintf (semOut, "  \"%s\",\n", name);
    }
  fclose (semIn);
  fprintf (semOut, "NULL\n");
  fprintf (semOut, "};\n");
  fprintf (semOut, "#endif /*__SEM_NAMES_H*/\n");
  fclose (semOut);
  return 0;
}
