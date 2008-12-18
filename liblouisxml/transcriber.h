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

#ifndef transcriber_h
#define transcriber_h

typedef enum
{
  leftJustified = 0,
  rightJustified = 1,
  centered = 2,
  alignColumnsLeft = 3,
  alignColumnsRight = 4,
  listColumns = 5,
  listLines = 6,
  computerCoded = 7,
  contents = 8
} StyleFormat;

typedef struct
{				/*Paragraph formatting instructions */
  sem_act action;
  int lines_before;
  int lines_after;
  int left_margin;
  int first_line_indent;	/* At true margin if negative */
  sem_act translate;
  int skip_number_lines;	/*Don't write on lines with page numbers */
  StyleFormat format;
  int newpage_before;
  int newpage_after;
  int righthand_page;
} StyleType;

int insert_utf8 (unsigned char *intext);
int insert_utf16 (widechar * intext, int length);
int insert_translation ( char *table);
int write_paragraph (sem_act action);
int start_document (void);
int end_document (void);
int transcribe_text_string (void);
int transcribe_text_file (void);
int back_translate_file (void);
StyleType *find_current_style (void);
void insert_text (xmlNode * node);
int insert_linkOrTarget (xmlNode *node, int which);
#endif /*transcriber_h*/
