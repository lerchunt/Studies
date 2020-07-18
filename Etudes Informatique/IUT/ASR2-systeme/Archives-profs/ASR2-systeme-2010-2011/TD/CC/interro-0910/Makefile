FLAGS=-file-line-error -halt-on-error


all: cc-asr2-6mai10.pdf  cc-asr2-20mai10.pdf 

cc-asr2-6mai10.pdf:  cc-asr2-6mai10.tex sujets.sty
	pdflatex $(FLAGS) $^

cc-asr2-20mai10.pdf:  cc-asr2-20mai10.tex sujets.sty
	pdflatex $(FLAGS) $^

clean:
	rm -f *~ *.aux *.log

cleanall: clean
	rm cc-asr2-6mai10.pdf  cc-asr2-20mai10.pdf 	
