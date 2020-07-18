FLAGS=-file-line-error -halt-on-error


all: fiche_td4.pdf

fiche_td4.pdf: fiche_td4.tex 
	pdflatex $(FLAGS) $^

clean:
	rm -f *~ *.aux *.log *.dvi

