doc_DATA = \
	copyright-notice \
	example_canonical.cfg \
	example_default.cfg \
	example_html.sem \
	liblouisxml.html \
	liblouisxml.txt

EXTRA_DIST = \
	copyright-notice \
	example_canonical.cfg \
	example_default.cfg \
	example_html.sem \
	example_math.sem \
	liblouisxml.html \
	liblouisxml.txt \
	xml2brl.asciidoc

CLEANFILES = liblouisxml.html liblouisxml.txt

info_TEXINFOS = liblouisxml.texi

# generate one big html file
AM_MAKEINFOHTMLFLAGS = --no-headers --no-split

# man pages
dist_man_MANS = xml2brl.1 msword2brl.1
man_MANS = xml2brl.1 msword2brl.1

xml2brl.1: xml2brl.asciidoc

# The lead dev doesn't have help2man, so rather than have totally
# up-to-date man pages we'll have a lead dev that can hack away

# Autogenerate the man page using help2man. This happens whenever
# msword2brl is modified, which contains the usage message.
# msword2brl.1: $(top_srcdir)/tools/msword2brl
# 	help2man --info-page=liblouisxml --output=$@ $<

SUFFIXES                = .txt

.texi.txt:
	$(MAKEINFO) --plaintext $< -o $@

# man pages are generated from asciidoc. If you would like to
# regenerate the man page you need to have asciidoc installed.
.asciidoc.1:
	a2x -d manpage -f manpage $<
