docdir = $(datadir)/liblouisxml/doc

doc_DATA = \
	copyright-notice \
	example_canonical.cfg \
	example_default.cfg \
	example_html.sem \
	example_math.sem \
	liblouisxml-guide.html \
	liblouisxml-guide.txt

EXTRA_DIST = \
	copyright-notice \
	example_canonical.cfg \
	example_default.cfg \
	example_html.sem \
	example_math.sem \
	liblouisxml-guide.html \
	liblouisxml-guide.txt \
	xml2brl.asciidoc

info_TEXINFOS = liblouisxml-guide.texi

# generate one big html file
AM_MAKEINFOHTMLFLAGS = --no-headers --no-split

# man pages
dist_man_MANS = xml2brl.1 msword2brl.1
man_MANS = xml2brl.1 msword2brl.1

xml2brl.1: xml2brl.asciidoc

SUFFIXES                = .txt

.texi.txt:
	$(MAKEINFO) --plaintext $< -o $@

# man pages are generated from asciidoc. If you would like to
# regenerate the man page you need to have asciidoc installed.
.asciidoc.1:
	a2x -d manpage -f manpage $<
