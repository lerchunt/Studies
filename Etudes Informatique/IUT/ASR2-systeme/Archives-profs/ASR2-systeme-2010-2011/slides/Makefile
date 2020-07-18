#TEXFILES :=	cours1.tex cours2.tex cours3.tex 
TEXFILES +=	cours4.tex cours4_bis.tex  
PDFFILES :=	$(TEXFILES:%.tex=%.pdf)
FILES  	 :=	$(TEXFILES:%.tex=%)


.PHONY: all force clean cleanall 

all: $(PDFFILES) 

$(PDFFILES): $(TEXFILES) header.tex 
	rubber -d $(FILES)	

force:
	rubber --warn all --force -d  $(FILES)

clean:
	rm -rf *.aux *.log *.tns *.out *.nav *.toc *.snm *.bbl  *.blg *~ 

cleanall: clean  	
	rubber --clean -d  $(FILES)	
