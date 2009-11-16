# docdir is only needed if you have Autoconf older than 2.60
docdir = ${datadir}/doc/${PACKAGE}

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
	liblouisxml.txt

CLEANFILES = liblouisxml.html liblouisxml.txt

info_TEXINFOS = liblouisxml.texi

# generate one big html file
AM_MAKEINFOHTMLFLAGS = --no-headers --no-split

SUFFIXES                = .txt

.texi.txt:
	$(MAKEINFO) --plaintext $< -o $@

