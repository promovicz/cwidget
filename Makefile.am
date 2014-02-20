# Adjust things so that 'make maintainer-clean' restores a pristine
# checkout.
MAINTAINERCLEANFILES=ChangeLog configure Makefile.in \
		     aclocal.m4 config.h.in config.guess \
		     config.sub depcomp INSTALL install-sh \
		     ltmain.sh missing

if DOXYGEN
DOXYGENCMD=doxygen
else
DOXYGENCMD=
endif

SUBDIRS=src doc

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = cwidget.pc

pkglib_HEADERS = cwidget-config.h

doc:
	$(MAKE) -C doc doc

.PHONY: doc all-local
