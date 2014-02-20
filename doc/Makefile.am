MAINTAINERCLEANFILES=Makefile.in

DOXYGEN=@DOXYGEN@

clean-local:
	rm -rf html latex
	rm -f doxygen*.tmp

doc:
	(cd .. && $(DOXYGEN))
