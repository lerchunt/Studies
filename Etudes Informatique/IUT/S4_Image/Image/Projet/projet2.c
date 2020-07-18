#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <jerror.h>
#include <tiffio.h>
#include <math.h>

struct Cube
{
	float x;
	float y;
	int text;
	int pos;
};


struct Cube c1 = {.x = -1.5, .y =  0.5, .text = 1, .pos = 1};
//tabCube[0]=c1;

struct Cube c2 = {.x = -0.5, .y =  0.5, .text = 2, .pos = 2};
//tabCube[1]=c2;
struct Cube c3 = {.x =  0.5, .y =  0.5, .text = 3, .pos = 3};
//tabCube[2]=c3;
struct Cube c4 = {.x = -1.5, .y = -0.5, .text = 4, .pos = 4};
//tabCube[3]=c4;
struct Cube c5 = {.x = -0.5, .y = -0.5, .text = 5, .pos = 5};
//tabCube[4]=c5;
struct Cube c6 = {.x =  0.5, .y = -0.5, .text = 6, .pos = 6};
//tabCube[5]=c6;
struct Cube c7 = {.x = -1.5, .y = -1.5, .text = 7, .pos = 7};
//tabCube[6]=c7;
struct Cube c8 = {.x =  0.5, .y = -1.5, .text = 8, .pos = 8};
//tabCube[7]=c8;
struct Cube cVide = {.x = -0.5, .y = -1.5, .pos = 9};
//tabCube[8]=cVide;
int i;
struct Cube tabCube[9];


unsigned char image [256*256*3];
unsigned char texture[256][256][3];
char presse;
px
int anglex, angley,x,y,xold,yold,r;
//~ int xprec,yprec;
float distance = 10.5;
float decalx =0;

GLbitfield masqueClear;
GLfloat couleurAP[]={0.8,0.8,0.8,1.0};
int IdTex[9];
float pz=0.0,px=0.0,Sin[360],Cos[360];

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

void dessineCube(float x, float y, float z, int idTex)
{
	//face 1
	glBindTexture(GL_TEXTURE_2D, idTex);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0,1.0); glVertex3f(x,y+1, z);
	glTexCoord2f(0.0,0.0); glVertex3f(x,y, z);
	glTexCoord2f(1.0,0.0); glVertex3f(x+1,y, z);
	glTexCoord2f(1.0,1.0); glVertex3f(x+1,y+1, z);
	glEnd();
	
	//face 2
	glBindTexture(GL_TEXTURE_2D, idTex);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); glVertex3f(x+1,y+1, z);
	glTexCoord2f(1.0,0.0); glVertex3f(x+1,y, z);
	glTexCoord2f(1.0,1.0); glVertex3f(x+1,y, z-1);
	glTexCoord2f(0.0,1.0); glVertex3f(x+1,y+1, z-1);
	glEnd();
	
	//face 3
	// Superposition des texture
	//~ glBindTexture(GL_TEXTURE_2D, idTex);
	//~ glBegin(GL_POLYGON);
	//~ glTexCoord2f(0.0,1.0); glVertex3f(x+1,y+1, z-1); 
	//~ glTexCoord2f(0.0,0.0); glVertex3f(x+1,y, z-1);
	//~ glTexCoord2f(1.0,0.0); glVertex3f(x,y, z-1);
	//~ glTexCoord2f(1.0,1.0); glVertex3f(x,y+1, z-1);
	//~ glEnd();
	
	//face 4
	glBindTexture(GL_TEXTURE_2D, idTex);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); glVertex3f(x,y+1, z-1);
	glTexCoord2f(1.0,0.0); glVertex3f(x,y, z-1);
	glTexCoord2f(1.0,1.0); glVertex3f(x,y, z);
	glTexCoord2f(0.0,1.0); glVertex3f(x,y+1, z);
	glEnd();
	
	//face 5
	glBindTexture(GL_TEXTURE_2D, idTex);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); glVertex3f(x,y+1, z-1);
	glTexCoord2f(1.0,0.0); glVertex3f(x,y+1, z);
	glTexCoord2f(1.0,1.0); glVertex3f(x+1,y+1, z);
	glTexCoord2f(0.0,1.0); glVertex3f(x+1,y+1, z-1);
	glEnd();
	
	//face 6
	glBindTexture(GL_TEXTURE_2D, idTex);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); glVertex3f(x,y, z-1);
	glTexCoord2f(1.0,0.0); glVertex3f(x,y, z);
	glTexCoord2f(1.0,1.0); glVertex3f(x+1,y, z);
	glTexCoord2f(0.0,1.0); glVertex3f(x+1,y, z-1);
	glEnd();
}

void affichage(){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(masqueClear);
	
	glLoadIdentity();
	//~ glRotated(r,0.0,1.0,0.0);
	//~ glTranslatef(-px,0.0,-pz);
	
	gluLookAt(0.0,0.0,distance,0.0,0.0,0.0,0.0,1.0,0.0);
	glRotatef(-angley,1.0,0.0,0.0);
	glRotatef(-anglex,0.0,1.0,0.0);
	
	
	/*Boite en bois*/
	glBindTexture(GL_TEXTURE_2D,IdTex[0]);
	
	// Face 1, de devant.
		glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); glVertex3f(-1.5,1.5,-0.6);
	glTexCoord2f(0.0,1.0); glVertex3f(-1.5,-1.5,-0.6);
	glTexCoord2f(1.0,1.0); glVertex3f(1.5,-1.5,-0.6);
	glTexCoord2f(1.0,0.0); glVertex3f(1.5,1.5,-0.6);
		glEnd();
		
	//Face 2 de droite
		glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); glVertex3f(1.5,1.5,-0.5);
	glTexCoord2f(0.0,1.0); glVertex3f(1.5,-1.5,-0.5);
	glTexCoord2f(1.0,1.0); glVertex3f(1.5,-1.5,-1.5);
	glTexCoord2f(1.0,0.0); glVertex3f(1.5,1.5,-1.5);
		glEnd();
		
	//Face 3 du dessous
		glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); glVertex3f(-1.5,-1.5,-1.5);
	glTexCoord2f(0.0,1.0); glVertex3f(-1.5,-1.5,-0.5);
	glTexCoord2f(1.0,1.0); glVertex3f(1.5,-1.5,-0.5);
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
	glTexCoord2f(1.0,1.0); glVertex3f(-1.5,-1.5,-0.5);
	glTexCoord2f(1.0,0.0); glVertex3f(-1.5,1.5,-0.5);
		glEnd();
	
		//Face 6, du dessus
		glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); glVertex3f(-1.5,1.5,-1.5);
	glTexCoord2f(0.0,1.0); glVertex3f(-1.5,1.5,-0.5);
	glTexCoord2f(1.0,1.0); glVertex3f(1.5,1.5,-0.5);
	glTexCoord2f(1.0,0.0); glVertex3f(1.5,1.5,-1.5);
		glEnd();
		
/*************************************************************/
	dessineCube(c1.x,c1.y,0.5,IdTex[c1.text]);
	dessineCube(c2.x,c2.y,0.5,IdTex[c2.text]);
	dessineCube(c3.x,c3.y,0.5,IdTex[c3.text]);
	dessineCube(c4.x,c4.y,0.5,IdTex[c4.text]);
	dessineCube(c5.x,c5.y,0.5,IdTex[c5.text]);
	dessineCube(c6.x,c6.y,0.5,IdTex[c6.text]);
	dessineCube(c7.x,c7.y,0.5,IdTex[c7.text]);
	dessineCube(c8.x,c8.y,0.5,IdTex[c8.text]);
	glutSwapBuffers();
}

void deplacer(){
	 GLdouble ox=0.0, oy=0.0,oz=0.0;
	 GLint viewport[4];
	 GLdouble modelview[16],projection[16];
	 GLfloat wx=x,wy,wz;
	 glGetIntegerv(GL_VIEWPORT, viewport);
	 y=viewport[3]-y;
	 wy=y;
	 glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	 glGetDoublev(GL_PROJECTION_MATRIX, projection);
	 glReadPixels(x,y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT, &wz);
	 gluUnProject(wx,wy,wz,modelview,projection,viewport,&ox,&oy,&oz);
	
		glutPostRedisplay();
		printf("%f",wy);
		printf("%s","\n");
	
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
void souris(int button, int etat, int x, int y){
		if ( button == GLUT_LEFT_BUTTON && etat == GLUT_DOWN)
	{
		presse =1;
		xold = x;
		yold = y;
	}
	
	if(button == GLUT_LEFT_BUTTON && etat == GLUT_UP)
		presse = 0;
}

void sourismouv(int x, int y){
	
	
		anglex = anglex+(x-xold);
		angley = angley+(y-yold);
		
	if(anglex>=360)
		r-=360;
		
	
	xold=x;
	yold=y;
	glutPostRedisplay();
}

void reshape(int x, int y){
	if(x<y)
		glViewport(0,(y-x)/2,x,x);
	else
		glViewport((x-y)/2,0,y,y);
}

int main (int argc, char * argv[]){
	tabCube[0]=c1;
	tabCube[1]=c2;
	tabCube[2]=c3;
	tabCube[3]=c4;
	tabCube[4]=c5;
	tabCube[5]=c6;
	tabCube[6]=c7;
	tabCube[7]=c8;
	tabCube[8]=cVide;
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(400,400);
	glutCreateWindow(argv[0]);
	glutReshapeFunc(reshape);
	
	glGenTextures(9,IdTex);
	chargeTextureTiff("texture.tif",IdTex[0]);
	chargeTextureTiff("texturehomer1.tif",IdTex[1]);
	chargeTextureTiff("texturehomer2.tif",IdTex[2]);
	chargeTextureTiff("texturehomer3.tif",IdTex[3]);
	chargeTextureTiff("texturehomer4.tif",IdTex[4]);
	chargeTextureTiff("texturehomer5.tif",IdTex[5]);
	chargeTextureTiff("texturehomer6.tif",IdTex[6]);
	chargeTextureTiff("texturehomer7.tif",IdTex[7]);
	chargeTextureTiff("texturehomer8.tif",IdTex[8]);
	
	glClearColor(couleurAP[0],couleurAP[1],couleurAP[2],couleurAP[3]);
	glColor3f(1.0,1.0,1.0);
	glShadeModel(GL_SMOOTH);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45.0,1,0.1,16.0);
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_TEXTURE_2D);
	
	masqueClear=GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
	glEnable(GL_DEPTH_TEST);
	
	//glutDisplayFunc(affichage);
	glutMouseFunc(souris);
	//glutMotionFunc(sourismouv);
	
	glutMainLoop();
	return 0;
}
