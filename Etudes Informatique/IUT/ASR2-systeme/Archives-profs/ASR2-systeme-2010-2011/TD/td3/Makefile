TEXFILES :=	fiche_td3.tex 
PDFFILES :=	$(TEXFILES:%.tex=%.pdf)
FILES  	 :=	$(TEXFILES:%.tex=%)

headers= 
images=

all: $(PDFFILES) 

$(PDFFILES): $(TEXFILES) $(headers) 
	rubber -d $(FILES)	

force:
	rubber --warn all --force -d  $(FILES)

clean:
	rm -rf *.aux *.log *.tns *.out *.nav *.toc *.snm  *~ 

cleanall: 	
	rubber --clean -d  $(FILES)	
	rm -rf *.pdf

