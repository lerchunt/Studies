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
struct jpeg_decompress_struct cinfo;
struct jpeg_error_mgr jerr;
int IdTex[9];

int anglex;
int angley;
int yold;
int xold;
int presse;

//Déclaration des cubes
struct Cube c1 = {.x = -1.5, .y =  0.5, .text = 1, .pos = 1};
struct Cube c2 = {.x = -0.5, .y =  0.5, .text = 2, .pos = 2};
struct Cube c3 = {.x =  0.5, .y =  0.5, .text = 3, .pos = 3};
struct Cube c4 = {.x = -1.5, .y = -0.5, .text = 4, .pos = 4};
struct Cube c5 = {.x = -0.5, .y = -0.5, .text = 5, .pos = 5};
struct Cube c6 = {.x =  0.5, .y = -0.5, .text = 6, .pos = 6};
struct Cube c7 = {.x = -1.5, .y = -1.5, .text = 7, .pos = 7};
struct Cube c8 = {.x =  0.5, .y = -1.5, .text = 8, .pos = 8};
struct Cube cVide = {.x = -0.5, .y = -1.5, .pos = 9};
struct Cube tabCube[9];

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
	void clavier(unsigned char touche,int x,int y){
		switch(touche)
		{
			case 'p':
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glutPostRedisplay();
				break;
			case 'f':
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glutPostRedisplay();
				break;
			case 's':
				glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
				glutPostRedisplay();
				break;
			case 'd':
				glEnable(GL_DEPTH_TEST);
				glutPostRedisplay();
				break;
			case 'D':
				glDisable(GL_DEPTH_TEST);
				glutPostRedisplay();
				break;
			case 'q':
				exit(0);

		}
	}

	void mouse(int button, int etat, int x, int y){
		if ( button == GLUT_LEFT_BUTTON && etat == GLUT_DOWN)
		{
			presse =1;
			xold = x;
			yold = y;
		}
		
		if(button == GLUT_LEFT_BUTTON && etat == GLUT_UP)
			presse = 0;
	}

	void mouseMotion(int x, int y){
		if(presse)
		{
			anglex = anglex+(x-xold);
			angley = angley+(y-yold);
			glutPostRedisplay();
		}
		
		xold=x;
		yold=y;
	}
	
	
	void affichage(){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
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
		glutInitWindowPosition(200,200);
		glutInitWindowSize(400,400);
		glutCreateWindow("projet");
		
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
		
		//glClearColor(couleurAP[0],couleurAP[1],couleurAP[2],couleurAP[3]);
		//glColor3f(1.0,1.0,1.0);
		//glShadeModel(GL_SMOOTH);
		
		//glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();
		//gluPerspective(45.0,1,0.1,16.0);
		//glMatrixMode(GL_MODELVIEW);
		
		glEnable(GL_TEXTURE_2D);
		
		//masqueClear=GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
		glEnable(GL_DEPTH_TEST);
		
		glutDisplayFunc(affichage);
		glutMouseFunc(mouse);
		glutMotionFunc(mouseMotion);
		
		glutMainLoop();
		return 0;
	}
}
