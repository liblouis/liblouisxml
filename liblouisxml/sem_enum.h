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

/* Semantic actions */
typedef enum
{
  /* General */
  no = 0,
  skip,
  generic,
  cdata,
  htmllink,
  htmltarget,
  changetable,
  reverse,
  /* styles */
  document,
  para,
  list,
  caption,
  exercise1,
  exercise2,
  exercise3,
  directions,
  stanza,
  line,
  heading1,
  heading2,
  heading3,
  heading4,
  section,
  subsection,
  table,
  volume,
  titlepage,
  dedication,
  contentsheader,
  contents1,
  contents2,
  contents3,
  contents4,
  code,
  quotation,
  attribution,
  spatial,
  arith,
  matrix,
  note,
  trnote,
  dispmath,
  disptext,
  music,
  graph,
  graphlabel,
   indexx,
  glossary,
  biblio,
  blanklinebefore,
  style1,
  style2,
  style3,
  style4,
  style5,
  /* translation */
  notranslate,
  compbrl,
  uncontracted,
  contracted,
  /* General text */
  pagenum,
  runninghead,
  footer,
  tblhead,
  tblbody,
  tblrow,
  tblcol,
  frontmatter,
  acknowledge,
  bodymatter,
  rearmatter,
  boxline,
  italicx,
  boldx,
  center,
  blankline,
  softreturn,
  newpage,
  righthandpage,
  endnotes,
  preface,
  jacket,
  copyright,
  booktitle,
  author,
  transcriber,
  tnpage,
  /* MathML */
  math,
  mi,
  mn,
  mo,
  mtext,
  mspace,
  ms,
  mglyph,
  mrow,
  mfrac,
  msqrt,
  mroot,
  mstyle,
  merror,
  mpadded,
  mphantom,
  mfenced,
  menclose,
  msub,
  msup,
  msubsup,
  munder,
  mover,
  munderover,
  mmultiscripts,
  none,
  semantics,
  mprescripts,
  mtable,
  mtr,
  mtd,
  maligngroup,
  malignmark,
  mlabeledtr,
  maction,
  /* Other technical notations */
  chemistry,
  graphic,
  end_all
}
sem_act;
