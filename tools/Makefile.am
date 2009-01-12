INCLUDES =		\
	-I$(top_srcdir) \
	-I$(top_srcdir)/liblouisxml

LDADD = $(top_builddir)/liblouisxml/liblouisxml.la $(BASE_DEPENDENCIES_LIBS)

AM_CFLAGS =	\
	$(BASE_DEPENDENCIES_CFLAGS)

AM_LDFLAGS =	\
	$(BASE_DEPENDENCIES_LDFLAGS)

bin_PROGRAMS = \
	mathml2brl \
	xml2brl

bin_SCRIPTS = msword2brl
CLEANFILES = $(bin_SCRIPTS)

mathml2brl_SOURCES = mathml2brl.c
xml2brl_SOURCES = xml2brl.c
