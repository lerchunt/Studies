#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float pz=0.0,px=0.0,Sin[360],Cos[360];
int xold,r=0;

void testPosition(){
	if(px>10)
		px=10;
	if(px<-10)
		px=-10;
	if(pz>10)
		pz=10;
	if(pz<-10)
		pz=-10;
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	glRotated(r,0.0,1.0,0.0);
	
	glTranslatef(-px,0.0,-pz);
	glPushMatrix();
	
	glTranslatef(0,1.5,0);
	glScalef(1.0,0.25,1.0);
	glColor3d(1,0,0);
	glutWireCube(20);
	glPopMatrix();
	glPushMatrix();
	
	glTranslated(5,-1.5,5);
	glRotated(-90,1,0,0);
	glColor3f(1.0,1.0,1.0);
	
	glutWireCone(1,2,20,1);
	glPopMatrix();
	glPushMatrix();
	
	glTranslated(-5,0,-5);
	glutWireTorus(0.2,0.8,20,30);
	glPopMatrix();
	glPushMatrix();
	
	glTranslated(10,0,7);
	glutWireCube(2);
	glPopMatrix();
	
	glTranslated(-10,0,-4);
	glutWireSphere(1,20,20);
	
	testPosition();
	
	glFlush();
	glutSwapBuffers();
	
}

void keyboard(unsigned char key, int x, int y){
	switch (key)
	{
		case 'q':
			exit(0);
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
	}
}

void mousePress(int bouton, int state, int x, int y){
	if(bouton == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		xold=x;
	}
}

void MouseMotion(int x, int y){
	r+=x-xold;
	if(r>=360)
		r-=361;
	if(r<0)
		r+=361;
		
	xold=x;
	glutPostRedisplay();
}

void calcSinCosTable(){
	int i;
	for (i=0;i<360;i++)
	{
		Sin[i]=sin(i/360.0*6.283185);
		Cos[i]=cos(i/360.0*6.283185);
	}
}


int main(int argc, char * argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(500,500);
	glutCreateWindow("29");
	
	glClearColor(0.0,0.0,0.0,0.0);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(50,1.0,0.1,40.0);
	glMatrixMode(GL_MODELVIEW);
	
	calcSinCosTable();
	
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mousePress);
	glutMotionFunc(MouseMotion);
	
	glutMainLoop();
return 0;
}


