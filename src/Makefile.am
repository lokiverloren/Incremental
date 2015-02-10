## Process this file with automake to produce Makefile.in

## Created by Anjuta



AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(INCREMENTAL_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = incremental

incremental_SOURCES = \
	config.vapi Incremental.vala

incremental_VALAFLAGS =  \
	--pkg gtk+-3.0


incremental_LDFLAGS = \
	-Wl,--export-dynamic

incremental_LDADD = $(INCREMENTAL_LIBS)




