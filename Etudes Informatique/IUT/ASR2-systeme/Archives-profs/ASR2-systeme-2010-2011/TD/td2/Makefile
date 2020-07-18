FLAGS=-file-line-error -halt-on-error


all: td-base-reseau.pdf

td-base-reseau.pdf: td-base-reseau.tex sujets.sty
	pdflatex $(FLAGS) $^

clean:
	rm -f *~ *.aux *.log

cleanall:
	rm -f *~ *.aux *.log td-base-reseau.pdf

