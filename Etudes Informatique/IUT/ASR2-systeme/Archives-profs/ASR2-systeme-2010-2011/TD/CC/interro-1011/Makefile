

pdf =  mbi-cc-asr2-4mai11.pdf

all: $(pdf)

%.pdf :  %.tex sujets.sty
	rubber -d  $<

clean:
	rm -f *~ *.aux *.log
	rubber --clean $(pdf:.pdf=.tex)

