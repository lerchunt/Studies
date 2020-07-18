.PHONY: all pdf ps clean cleanall

TEXINPUTS	:= .:./styles:
export TEXINPUTS

#MAIN		:= cc-asr2-9mai11 
MAIN		:= cc-asr2-6juin11

all: pdf

pdf:
	rubber --warn refs -d $(MAIN)

force:
	rubber --warn all --force -d $(MAIN)

clean:
	rubber --clean -d $(MAIN)
	rm -f main.maf  main.mtc *~

cleanall:
	rubber --clean -d $(MAIN)
	rm -rf *.pdf
