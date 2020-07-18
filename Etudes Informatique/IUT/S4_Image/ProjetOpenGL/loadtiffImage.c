/****************************************************/
/* void chargeTextureTiff(char *fichier,int numtex) */
/****************************************************/
/* chargement de l'image tif 'fichier' et placement */
/* dans la texture de numero 'numtex'               */
/****************************************************/

void chargeTextureTiff(char *fichier,int numtex)
{
  unsigned char image[256][256][3];
  uint32 l, h;
  int i,j;
  size_t npixels;
  uint32* raster;
  
  /* chargement de l'image TIF */
  TIFF* tif = TIFFOpen(fichier, "r");
  if (tif) {
    TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &l);
    TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h); 
    npixels = l * h;
    raster = (uint32*) _TIFFmalloc(npixels * sizeof (uint32)); 
    if (raster != NULL) {
      /* lecture de l'image */
      if (TIFFReadRGBAImage(tif, l, h, raster, 1)) {
	/* transfert de l'image vers le tableau 'image' */
	for (i=0;i<256;i++)
	  for (j=0;j<256;j++) {
	    image[i][j][0]=((unsigned char *)raster)[i*256*4+j*4+0];
	    image[i][j][1]=((unsigned char *)raster)[i*256*4+j*4+1];
	    image[i][j][2]=((unsigned char *)raster)[i*256*4+j*4+2];
	  }
      }
      else {
	printf("erreur de chargement du fichier %s\n",fichier);
	exit(0);
      }
      _TIFFfree(raster); 
    }
    TIFFClose(tif);
    
    /*      paramétrage de la texture */
    glBindTexture(GL_TEXTURE_2D,numtex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,256,256,0,
		 GL_RGB,GL_UNSIGNED_BYTE,image);
  }
  
}