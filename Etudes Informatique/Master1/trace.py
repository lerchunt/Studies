#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
from math import *


def trace(function, xmin, xmax, nstep, output):
    function = eval("lambda x:" + function)
    Largeur = 590.
    Hauteur = 800.
    n=(xmax-xmin)/Largeur
    print(n)
    output.write("%!\nnewpath\n")
    for i in range(nstep+1):
        x = i
        try:
            
            y = function(x)
        
        except:
            continue
        if i == 0:
            yprec=y
            output.write("/Times-Roman findfont\n")
            output.write("9 scalefont\n")
            output.write("setfont\n")
            output.write("%s %s moveto\n" % (i+15,Hauteur/2))
            output.write("(xmin) show\n")
        else :
        	output.write("%s %s rlineto\n" % (x*n+15, (y-yprec)*100))
        yprec=y
    output.write("(xmax) show\n")
    output.write("gsave\n")
    output.write("1 setlinewidth\n") #epaisseur
    output.write("[5 2] 4 setdash\n") #pointillés
    output.write("%s %s moveto\n" % (15,Hauteur/2))
    output.write("%s %s rlineto\n" % (Largeur+15, 0))
    output.write("%s %s moveto\n" % (30,15))
    output.write("%s %s rlineto\n" % (0, Hauteur-15))
    
    output.write("%s %s moveto\n" % (15+(Largeur/2),15))
    output.write("%s %s rlineto\n" % (0, Hauteur-15))
    
    output.write("%s %s moveto\n" % (15+(Largeur/4),15))
    output.write("%s %s rlineto\n" % (0, Hauteur-15))
    
    output.write("%s %s moveto\n" % (15+(3*Largeur/4),15))
    output.write("%s %s rlineto\n" % (0, Hauteur-15))
    
    output.write("%s %s moveto\n" % (15,Hauteur/4))
    output.write("%s %s rlineto\n" % (Largeur+15, 0))
    
    output.write("%s %s moveto\n" % (15,3*Hauteur/4))
    output.write("%s %s rlineto\n" % (Largeur+15, 0))
    output.write("stroke\nshowpage")


def main(argv=None):
    if argv is None:
        argv = sys.argv
    
    import getopt
    try:
        options, argv = getopt.getopt(argv[1:], "o:m:M:p:h", ["output=","min=","max=","points=","help"])
    except getopt.GetoptError as message:
        sys.stderr.write("%s\n" % message)
        sys.exit(1)
    
    if len(argv) > 5:
        print("Le programme s'est arrete")
        sys.exit(1)
    
    
    output = sys.stdout
    xmin, xmax = 0., 1.
    nstep = 10
    if options[0][0] in ["-h","--help"]:
        print("-o --output : indiquer la fichier en sortie \n-m --min: choix du xmin \n-M --max: choix du xmax \n-p --points: choix du nombre de points\n")
        sys.exit(1)
    else:    
        for option, value in options:
            if option in ["-o", "--output"]:
			    output = file(value, "w")
			
            elif option in ["-m", "--min"]:
                xmin = float(value)
	        
            elif option in ["-M", "--max"]:
               	xmax = float(value)
               	
            elif option in ["-p", "--points"]:
                nstep = int(value)
            
            else:
                print("utilisez -h --help pour afficher les options disponibles")
                sys.exit(1)
    
    function = argv[0]
    trace(function, xmin, xmax, nstep, output)


if __name__ == "__main__":
    sys.exit(main())

