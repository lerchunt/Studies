PDFOPT=-file-line-error -halt-on-error


ds: idees.pdf

%.pdf: %.tex
	pdflatex $(PDFOPT) $<

clean:
	rm -f *~ *.aux *.log

mrproper: clean
	rm -f idees.pdf