// Please don't change lines 9-31 (It helps me to grade)
#ifdef __APPLE__
// For XCode only: New C++ terminal project. Build phases->Compile with libraries: add OpenGL and GLUT
// Import this whole code into a new C++ file (main.cpp, for example). Then run.
// Reference: https://en.wikibooks.org/wiki/OpenGL_Programming/Installation/Mac
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#endif
#ifdef _WIN32
// For VS on Windows only: Download CG_Demo.zip. UNZIP FIRST. Double click on CG_Demo/CG_Demo.sln
// Run
	#include "freeglut.h"
#endif
#ifdef __unix__
// For Linux users only: g++ CG_Demo.cpp -lglut -lGL -o CG_Demo
// ./CG_Demo
// Reference: https://www.linuxjournal.com/content/introduction-opengl-programming
	#include "GL/freeglut.h"
	#include "GL/gl.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <iostream>

/** FOG Properties */
float  fog_colour[] = {0.6f,0.58f,0.79f,0.0f};
float  fog_density  = 0.03f;
GLenum fog_mode     = GL_EXP; //GL_Exponential
// Far and near distances
float far_distance  = 200.0f;
float near_distance = 0.05f;

// Camera attributes
float zoom = 15.0f;
float rotx = 0;
float roty = 0.001f;
float tx = 0;
float ty = 0;
int lastx=0;
int lasty=0;
unsigned char Buttons[3] = {0};

void Init() {
	// Set the background colour to the Fog color
	glClearColor(fog_colour[0],
				 fog_colour[1],
				 fog_colour[2],
				 fog_colour[3]);

	//We set the fog atttributes
	glFogf (GL_FOG_START,  near_distance);
	glFogf (GL_FOG_END,    far_distance);
	glFogfv(GL_FOG_COLOR,  fog_colour);      
	glFogi (GL_FOG_MODE,   fog_mode);
	glFogf (GL_FOG_DENSITY,fog_density);

	// Enable the Fog
	glEnable(GL_FOG);

	// Enable the default lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//Enable depth testing	
	glEnable(GL_DEPTH_TEST);
}

void Display(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();

	// Set the camera position
	glTranslatef(0,0,-zoom);
	glTranslatef(tx,ty,0);
	glRotatef(rotx,1,0,0);
	glRotatef(roty,0,1,0);	

	//Draw some tets objects
	for(int i=-100;i<=100;i+=10) {
		for(int j=-100;j<=100;j+=10) {
			glPushMatrix();
				glTranslatef(i,0,j);
				glRotatef(-90,1,0,0);
				glutSolidCone(1,5,10,3);
			glPopMatrix();
		}

	}

	glutSwapBuffers();
}


void Reshape(int w, int h){
	// prevent divide by 0 error when minimised
	if(w==0) 
		h = 1;

	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)w/h,near_distance,far_distance);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Motion(int x,int y){
	int diffx=x-lastx;
	int diffy=y-lasty;
	lastx=x;
	lasty=y;

	if( Buttons[0] && Buttons[1] ){
		zoom -= (float) 0.05f * diffx;
	}
	else
		if( Buttons[0] ){
			rotx += (float) 0.5f * diffy;
			roty += (float) 0.5f * diffx;		
		}
		else
			if( Buttons[1] )
			{
				tx += (float) 0.05f * diffx;
				ty -= (float) 0.05f * diffy;
			}
			glutPostRedisplay();
}

void Mouse(int b,int s,int x,int y){
	lastx=x;
	lasty=y;
	switch(b){
	case GLUT_LEFT_BUTTON:
		Buttons[0] = ((GLUT_DOWN==s)?1:0);
		break;
	case GLUT_MIDDLE_BUTTON:
		Buttons[1] = ((GLUT_DOWN==s)?1:0);
		break;
	case GLUT_RIGHT_BUTTON:
		Buttons[2] = ((GLUT_DOWN==s)?1:0);
		break;
	default:
		break;		
	}
	glutPostRedisplay();
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	
	glutCreateWindow("Fog");

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);

	Init();

	glutMainLoop();

	return 0;
}

























