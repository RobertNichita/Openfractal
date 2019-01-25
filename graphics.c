#define PI 3.14159265358979323846
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<math.h>
#include<time.h>
#include"freeglut.h"
#include"glut.h"
#include"GL\glu.h"



void reshape(){
	
}

void Init(){
	glLineWidth(5.0);
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,1920,0.0,1080);
}

void tick(){
	glutPostRedisplay();
}


void drawLine(int x1,int y1,int x2,int y2){
	glVertex2i(x1,y1);
	glVertex2i(x2,y2);
}

void linetobox(int x1,int y1, int x2, int y2, int width){
	float m = atan2((y2-y1),(x2-x1));
	float perp = -1/m;
	glVertex2i(x1,y1);
	glVertex2i(x2,y2);
	glVertex2i(x2+width*cos(perp),y2+width*sin(perp));
	glVertex2i(x1+width*cos(perp),y1+width*sin(perp));
	
}

void treeFractal(double x,double y,double length,double angle, double rot, int iter, int stem,float sfac){
	if(iter == 0){
		return;
	}
	if(stem){
		glColor3d(1.0,0.0,0.0);
		drawLine(x,y,x,y+length/3.0);
		glColor3d((rand()%1000)/1000.0,(rand()%1000)/1000.0,0.0);
		drawLine(x,y+length/3.0,x + length/3.0*cos(angle/2+rot),y+length/3.0+length/3.0*sin(angle/2+rot));
		treeFractal(x + length/3.0*cos(angle/2+rot),y+length/3.0+length/3.0*sin(angle/2+rot),length*sfac,angle,rot+(angle/3),iter-1,0,sfac);
		glColor3d((rand()%1000)/1000.0,(rand()%1000)/1000.0,0.0);
		drawLine(x,y+length/3.0,x + length/3.0*cos(PI/2+angle/2+rot),y+length/3.0+length/3.0*sin(PI/2+angle/2+rot));
		treeFractal(x + length/3.0*cos(PI/2+angle/2+rot),y+length/3.0+length/3.0*sin(PI/2+angle/2+rot),length*sfac,angle,rot+(angle/3),iter-1,0,sfac);
	}else{
		double rotmod = (rand()%3-2)*10*PI/180;
		glColor3d((rand()%1000)/1000.0,(rand()%1000)/1000.0,0.0);
		drawLine(x,y,x + length/3.0*cos(angle/2+rot),y+length/3.0*sin(angle/2+rot));
		treeFractal(x + length/3.0*cos(angle/2+rot),y+length/3.0*sin(angle/2+rot),length*sfac,angle,rot+(angle/3)+rotmod,iter-1,0,sfac);
		glColor3d((rand()%1000)/1000.0,(rand()%1000)/1000.0,0.0);
		drawLine(x,y,x + length/3.0*cos(PI/2+angle/2+rot),y+length/3.0*sin(PI/2+angle/2+rot));
		treeFractal(x + length/3.0*cos(PI/2+angle/2+rot),y+length/3.0*sin(PI/2+angle/2+rot),length*sfac,angle,rot+(angle/3)+rotmod,iter-1,0,sfac);
	}
}

void Loop(){
	glutPostRedisplay();
	
	glutTimerFunc(100,Loop,0);
}

void genFractal(char* instructions, int* out){
	
	
}

void  display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5.0f);
	glBegin(GL_LINES);
		//linetobox(50,50,300,300,10);
		treeFractal(960,0,300,30*PI/180,PI/9,16,1,0.9);
	glEnd();
	glFlush();
}	


int main(int argc, char **argv){
	srand(time(NULL));
	
	glutInit(&argc,argv);
	glutCreateWindow("OpenFractal Vizualiser");
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1920,1080);
	Init();
	glutDisplayFunc(display);
	//glutIdleFunc(tick);
	glutTimerFunc(1,Loop,0);
	glutMainLoop();
	
	return 0;
}