#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <jerror.h>
#include <tiffio.h>
#include <math.h>

#define PI 3.14159265

unsigned char image [256*256*3];
unsigned char texture[256][256][3];
char presse;
int anglex=30, angley=20,x,y,xold,yold,r;
int xprec,yprec;
float distance = 10.5;  

float pz=0.0,px=0.0,Sin[360],Cos[360];

GLbitfield masqueClear;
GLfloat couleurAP[]={0.8,0.8,0.8,1.0};
int IdTex[2];

unsigned char b_gauche=0;
unsigned char b_droit=0;

struct jpeg_decompress_struct cinfo;
struct jpeg_error_mgr jerr;

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

void affichage(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(masqueClear);
	
	glLoadIdentity();
	glRotated(r,0.0,1.0,0.0);
	glTranslatef(-px,0.0,-pz);
	
	gluLookAt(0.0,0.0,distance,0.0,0.0,0.0,0.0,1.0,0.0);
	glRotatef(angley,1.0,0.0,0.0);
	glRotatef(anglex,0.0,1.0,0.0);
	
	/*Boite en bois*/
	glBindTexture(GL_TEXTURE_2D,IdTex[0]);
	
	// Face 1, de davant.
		/*glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); glVertex3f(-1.5,1.5,1.5);
	glTexCoord2f(0.0,1.0); glVertex3f(-1.5,-1.5,1.5);
	glTexCoord2f(1.0,1.0); glVertex3f(1.5,-1.5,1.5);
	glTexCoord2f(1.0,0.0); glVertex3f(1.5,1.5,1.5);
		glEnd();*/
		
	//Face 2 de droite
	/*	glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); glVertex3f(1.5,1.5,1.5);
	glTexCoord2f(0.0,1.0); glVertex3f(1.5,-1.5,1.5);
	glTexCoord2f(1.0,1.0); glVertex3f(1.5,-1.5,-1.5);
	glTexCoord2f(1.0,0.0); glVertex3f(1.5,1.5,-1.5);
		glEnd();
		
	//Face 3 du dessous
		glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); glVertex3f(-1.5,-1.5,-1.5);
	glTexCoord2f(0.0,1.0); glVertex3f(-1.5,-1.5,1.5);
	glTexCoord2f(1.0,1.0); glVertex3f(1.5,-1.5,1.5);
	glTexCoord2f(1.0,0.0); glVertex3f(1.5,-1.5,-1.5);
		glEnd();

	//Face 4 du fond
		glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); glVertex3f(1.5,1.5,-1.5);
	glTexCoord2f(0.0,1.0); glVertex3f(-1.5,1.5,-1.5);
	glTexCoord2f(1.0,1.0); glVertex3f(-1.5,-1.5,-1.5);
	glTexCoord2f(1.0,0.0); glVertex3f(1.5,-1.5,-1.5);
		glEnd();
		
	//Face 5 de gauche
		glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); glVertex3f(-1.5,1.5,-1.5);
	glTexCoord2f(0.0,1.0); glVertex3f(-1.5,-1.5,-1.5);
	glTexCoord2f(1.0,1.0); glVertex3f(-1.5,-1.5,1.5);
	glTexCoord2f(1.0,0.0); glVertex3f(-1.5,1.5,1.5);
		glEnd();
	
		//Face 6, du dessus
		glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); glVertex3f(-1.5,1.5,-1.5);
	glTexCoord2f(0.0,1.0); glVertex3f(-1.5,1.5,1.5);
	glTexCoord2f(1.0,1.0); glVertex3f(1.5,1.5,1.5);
	glTexCoord2f(1.0,0.0); glVertex3f(1.5,1.5,-1.5);
		glEnd();*/
		

	
	/*Cube Homer*/
	glBindTexture(GL_TEXTURE_2D,IdTex[1]);
	//Face 1 de devant
		glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); glVertex3f(-0.5,0.5,0.5);
	glTexCoord2f(0.0,1.0); glVertex3f(-0.5,-0.5,0.5);
	glTexCoord2f(1.0,1.0); glVertex3f(0.5,-0.5,0.5);
	glTexCoord2f(1.0,0.0); glVertex3f(0.5,0.5,0.5);
		glEnd();
		
	//Face 2 de droite
		glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); glVertex3f(0.5,0.5,0.5);
	glTexCoord2f(0.0,1.0); glVertex3f(0.5,-0.5,0.5);
	glTexCoord2f(1.0,1.0); glVertex3f(0.5,-0.5,-0.5);
	glTexCoord2f(1.0,0.0); glVertex3f(0.5,0.5,-0.5);
		glEnd();
		
	//Face 3 du fond
		glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); glVertex3f(0.5,0.5,-0.5);
	glTexCoord2f(0.0,1.0); glVertex3f(0.5,-0.5,-0.5);
	glTexCoord2f(1.0,1.0); glVertex3f(-0.5,-0.5,-0.5);
	glTexCoord2f(1.0,0.0); glVertex3f(-0.5,0.5,-0.5);
		glEnd();

	//Face 4 de gauche
		glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); glVertex3f(-0.5,0.5,-0.5);
	glTexCoord2f(0.0,1.0); glVertex3f(-0.5,-0.5,-0.5);
	glTexCoord2f(1.0,1.0); glVertex3f(-0.5,-0.5,0.5);
	glTexCoord2f(1.0,0.0); glVertex3f(-0.5,0.5,0.5);
		glEnd();
		
	//Face 5 du dessous
		glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); glVertex3f(-0.5,-0.5,-0.5);
	glTexCoord2f(0.0,1.0); glVertex3f(-0.5,-0.5,0.5);
	glTexCoord2f(1.0,1.0); glVertex3f(0.5,-0.5,0.5);
	glTexCoord2f(1.0,0.0); glVertex3f(0.5,-0.5,-0.5);
		glEnd();
		
	//Face 6 du dessus
		glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); glVertex3f(-0.5,0.5,-0.5);
	glTexCoord2f(0.0,1.0); glVertex3f(-0.5,0.5,0.5);
	glTexCoord2f(1.0,1.0); glVertex3f (0.5,0.5,0.5);
	glTexCoord2f(1.0,0.0); glVertex3f(0.5,0.5,-0.5);
		glEnd();
		
	glutSwapBuffers();
}

void clavier(unsigned char touche, int x, int y){
	switch(touche){
		case 'l':
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glutPostRedisplay();
			break;
		case 'n':
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glutPostRedisplay();
			break;
			
		case 'z':
			pz-=0.5*Cos[r];
			px+=0.5*Sin[r];
			glutPostRedisplay();
			break;
		case 's':
			pz+=0.5*Cos[r];
			px-=0.5*Sin[r];
			glutPostRedisplay();
			break;
		case 27:
			exit(0);
	}
}
void souris(int bouton, int etat, int x, int y){
	if(bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN)
		xold=x;
}
void sourismouv(int x, int y){
	r+=x-xold;
	if(r>=360)
		r-=361;
	if(r<0)
		r+=361;
		
	xold=x;
	glutPostRedisplay();
}
void redim(int l, int h){}

void calcSinCosTable(){
	int i;
	for (i=0;i<360;i++)
	{
		Sin[i]=sin(i/360.0*6.283185);
		Cos[i]=cos(i/360.0*6.283185);
	}
}

int main (int argc, char * argv[]){

	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(400,400);
	glutCreateWindow(argv[0]);
	
	glGenTextures(2,IdTex);
	chargeTextureTiff("texture.tif",IdTex[0]);
	chargeTextureTiff("texturehomer1.tif",IdTex[1]);
	
	glClearColor(couleurAP[0],couleurAP[1],couleurAP[2],couleurAP[3]);
	glColor3f(1.0,1.0,1.0);
	glShadeModel(GL_SMOOTH);
	//glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,1,0.1,16.0);
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_TEXTURE_2D);
	
	masqueClear=GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
	glEnable(GL_DEPTH_TEST);
	
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,256,256,0,GL_RGB, 
				GL_UNSIGNED_BYTE, texture);
	glEnable(GL_TEXTURE_2D);*/
	
	calcSinCosTable();
	
	glutDisplayFunc(affichage);
	glutKeyboardFunc(clavier);
	glutMouseFunc(souris);
	glutMotionFunc(sourismouv);
	glutReshapeFunc(redim);
	
	glutMainLoop();
	return 0;
}

