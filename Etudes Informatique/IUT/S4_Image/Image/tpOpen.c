#include <GL/glut.h>

typedef struct{
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;

} point;

int anglex;
int angley;
int yold;
int xold;
int presse;

void affichage(){
	int i;
	int j;
	
	point p[8]={
		{-0.5,-0.5,0.5,1.0,0.0,0.0},
		{-0.5, 0.5,0.5, 0.0, 1.0, 0.0 },
		{0.5, 0.5,0.5,0.0 ,0.0,1.0},
		{0.5,-0.5,0.5,1.0,1.0,1.0},
		{-0.5,-0.5,-0.5,1.0,0.0,0.0},
		{-0.5, 0.5,-0.5,0.0,1.0,0.0},
		{0.5,0.5,-0.5,0.0,0.0,1.0},
		{0.5,-0.5,-0.5,1.0,1.0,1.0}};

	int f[6][4]={
		{0,1,2,3},
		{3,2,6,7},
		{4,5,6,7},
		{0,1,5,4},
		{1,5,6,2},
		{0,4,7,3}};
		
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPointSize(2.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();
	glRotatef(-angley,1.0,0.0,0.0);
	glRotatef(-anglex,0.0,1.0,0.0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	for (i=0;i<6;i++)
	{
		glBegin(GL_POLYGON);
		for (j=0;j<4;j++)
			{
				glColor3f(p[f[i][j]].r,p[f[i][j]].g,p[f[i][j]].b);
				glVertex3f(p[f[i][j]].x,p[f[i][j]].y,p[f[i][j]].z);
			}
		glEnd();
	}
	
	glFlush();		
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

void reshape(int x, int y){
	if(x<y)
		glViewport(0,(y-x)/2,x,x);
	else
		glViewport((x-y)/2,0,y,y);
}


int main(int argc, char * argv[]){		

	glutInit (&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(250,250);
	glutCreateWindow("ogl1");
	glutDisplayFunc(affichage);
	glutKeyboardFunc(clavier);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutReshapeFunc(reshape);
	
	glutMainLoop();
	
	return 0;

}
