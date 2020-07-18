FLAGS=-file-line-error -halt-on-error


all: td-install-sl81.pdf

td-install-sl81.pdf: td-install-sl81.tex sujets.sty
	pdflatex $(FLAGS) $^

clean:
	rm -f *~ *.aux *.log

cleanall: clean
	rm td-install-sl81.pdf

