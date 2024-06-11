#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#define CIRCLE_RADIUS  0.15f
#define PI 3.14159265358979323846

int eggs_caught=0,missed_eggs=0,level_count=1,points=0;
int egg_xc,egg_yc;

// for coordinates of egg
int basket_x,basket_y;

// for coordinates of basket
int a=620,b=650; // for default size of the screen
int s=0;

// for menu option
int dropped_eggs=0;
int speed_1 = 1.5, speed_2 = 2, speed_3 = 2.5, speed_4 = 3;
int w=48,h=48,t=10,e=9,g=12, count;
int df = 10;
clock_t start,end;

void myinit();
void start_screen(int,int);
void cloud1();
void egg();
void basket(int,int);
void duck(int,int);
void print_score();
void egg_start();
void color();
void score();
void display(void);
void basket_set(int,int);
void myReshape(int,int);
void keys(unsigned char,int,int);
void menu(int);

void myinit(){
	glViewport(0,0,a,b);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,(GLdouble)a,0,(GLdouble)b);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void start_screen(int i,int j){
	int k;
	char cat[4]="EGG";
	char orr[9]="Catching";
	char hatch[5]="Game";
	char start[20]="Press S for start";
	glColor3f(0,1,0);
	glRasterPos2i(150,320);

	for(k=0;k<4;k++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,cat[k]);
	glColor3f(1,1,1);
	glRasterPos2i(200,320);

	for(k=0;k<9;k++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,orr[k]);
	glColor3f(1,0,0);
	glRasterPos2i(300,320);

	for(k=0;k<5;k++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,hatch[k]);
	glColor3f(1,1,0);
	glRasterPos2i(210,200);

	for(k=0;k<20;k++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,start[k]);
	glColor3f(1,.5,.5);

}

void sun() {
	float theta;
	GLfloat angle;
	glLineWidth(1.5);
	glColor3f(1,0.2,0);
	glBegin(GL_POLYGON);

	for (int i = 0; i <360 ; i++){
	theta  = i*PI*i/180;
	glVertex2f(500+80*cos(theta)/2, 600+80*sin(theta)/2);
	}
	glEnd();
	glFlush();
}

void cloud1() {
	float theta;
	GLfloat angle;
	glLineWidth(1.5);
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
	
	for (int i = 0; i <360 ; i++){
		theta  = i*PI*i/180;
		glVertex2f(100+50*cos(theta)/2, 590+50*sin(theta)/2);
	}
	glEnd();
	//GLfloat angle;
	glLineWidth(1.5);
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
	
	for (int i = 0; i <360 ; i++){
		theta  = i*PI*i/180;
		glVertex2f(130+50*cos(theta)/2, 580+50*sin(theta)/2);
	}
	glEnd();
	glLineWidth(1.5);
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);

	for (int i = 0; i <360 ; i++){
		theta  = i*PI*i/180;
		glVertex2f(140+50*cos(theta)/2, 600+50*sin(theta)/2);
	}
	glEnd();
	glLineWidth(1.5);
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);

	for (int i = 0; i <360 ; i++){
		theta  = i*PI*i/180;
		glVertex2f(170+50*cos(theta)/2, 590+50*sin(theta)/2);
	}
	glEnd();
	glFlush();
}


void cloud2(){
	float theta;
	glLineWidth(1.5);
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
	
	for (int i = 0; i <360 ; i++){
		theta  = i*PI*i/180;
		glVertex2f(420+45*cos(theta)/2, 540+45*sin(theta)/2);
	}
	glEnd();
	glLineWidth(1.5);
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);

	for (int i = 0; i <360 ; i++){
		theta  = i*PI*i/180;
		glVertex2f(455+45*cos(theta)/2, 550+45*sin(theta)/2);
	}
	glEnd();
	glLineWidth(1.5);
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);

	for (int i = 0; i <360 ; i++){
		theta  = i*PI*i/180;
		glVertex2f(455+45*cos(theta)/2, 530+45*sin(theta)/2);
	}
	glEnd();
	glLineWidth(1.5);
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);

	for (int i = 0; i <360 ; i++){
		theta  = i*PI*i/180;
		glVertex2f(490+45*cos(theta)/2, 540+45*sin(theta)/2);
	}
	glEnd();
	glFlush();
}

void line(int i , int j){
	glBegin(GL_QUADS);
	glColor3f(1.0,.5,0.5);
	glVertex2f(0.0+i,10.0+j);
	glVertex2f(0.0+i,15.0+j);
	glVertex2f(600.0+i,15.0+j);
	glVertex2f(600.0+i,10.0+j);
	glEnd();
	glFlush();
}

void backk(int i , int j){
	glColor3f(0, .5, 1);
	glBegin(GL_QUADS);
	glVertex2f(0.0+i,0.0+j);
	glVertex2f(600.0+i, 0.0+j);
	glVertex2f(600.0+i,-500+j);
	glVertex2f(0.0+i,-500+j);
	glEnd();
	glFlush();
}

void ground(int i , int j){
	glBegin(GL_QUADS);
	glColor3f(0,1.0,0);
	glVertex2f(0.0+i,0.0+j);
	glVertex2f(600.0+i, 0.0+j);
	glVertex2f(600.0+i,-j);
	glVertex2f(0.0+i,-j);
	glEnd();
}

void egg(){
	float x,y,z;
	int t;
	glColor3f(1.0,10,1.0);
	glBegin(GL_POLYGON);

	for(t=0;t<=360;t+=1){
		x = egg_xc+8*(cos(t));
		y = egg_yc+16*(sin(t));
		z = 0;
		glVertex3f(x,y,z);
	}
	glEnd();
}

void basket(int i,int j){
	j=10;
	if(i>=a-60)i=a-60;
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);
	glVertex2f(0.0+i,30.0+j);
	glVertex2f(10.0+i,10.0+j);
	glVertex2f(50.0+i,10.0+j);
	glVertex2f(60.0+i,30.0+j);
	glEnd();
}

void duck(int i,int j){
	int h;
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(45+i,45+j);
	glVertex2f(70+i,20+j);
	glVertex2f(95+i,20+j);
	glVertex2f(120+i,45+j);
	glVertex2f(95+i,70+j);
	glVertex2f(70+i,70+j);
	glVertex2f(95+i,95+j);
	glVertex2f(82.5+i,107.5+j);
	glVertex2f(32.5+i,57.5+j);
	glEnd();
	glFlush();

	for(h=0;h<13;h+=4){
		glBegin(GL_LINES);
		glColor3f(0.7,0.4,0);
		glVertex2f(57.5+h+i,52.5+h+j);
		glVertex2f(100+h+i,30+h+j);
		glEnd();
		glFlush();
	}

	glColor3f(0.0,1.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(82.5+i,107.5+j);
	glVertex2f(65+i,107.5+j);
	glVertex2f(50+i,95+j);
	glVertex2f(70+i,95+j);
	glEnd();
	glFlush();

	glColor3f(0.0,0.0,0.0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(76+i,101+j);
	glEnd();
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(72.5+i,107.5+j);
	glVertex2f(67.5+i,112.5+j);
	glVertex2f(72.5+i,110+j);
	glVertex2f(77.5+i,112.5+j);
	glEnd();
	glFlush();
}

void print_score(){
	printf("\nLevel reached: %d\n\n",level_count);
	printf("\nNo. of eggs dropped= %d \n",dropped_eggs);
	printf("\nNo. of eggs caught = %d\n",eggs_caught);
	printf("\nNo. of eggs missed = %d\n",missed_eggs);
	getchar();
	exit(0);
}

void egg_start(){
	egg_yc=375;
	if(missed_eggs>=10){
		printf("\n\n\t\t\t\tGAME OVER\n\n");
		print_score();
	}
	dropped_eggs++;
	switch(rand()%9){
		case 0:egg_xc=115; break;
		case 1:egg_xc=255; break;
		case 2:egg_xc=390; break;
		case 5:egg_xc=115; break;
		case 3:egg_xc=255; break;
		case 4:egg_xc=390; break;
		case 7:egg_xc=115; break;
		case 6:egg_xc=255; break;
		case 8:egg_xc=390; break;
	}
}

void score(){
	if(egg_yc<=50 && (egg_xc>=basket_x&&egg_xc<=basket_x+60)){
		printf("\a");
		eggs_caught++;
		egg_yc=-10;
	}
	missed_eggs=dropped_eggs-eggs_caught;
}

void output(int x, int y,const char *str){
	int len, i;
	glRasterPos2f(x,y);
	len=(int) strlen(str);
	for (i = 0; i < len; i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
	}
}

void drawstring(int x, int y,const char *str,void *font){
	int len, i;
	glRasterPos2f(x,y);
	len=(int) strlen(str);
	for (i = 0; i < len; i++){
		glutBitmapCharacter(font,str[i]);
	}
}

void frontscreen(void){
	 glClear(GL_COLOR_BUFFER_BIT);
	 glLoadIdentity();
	 glColor3f(1,1,1);
	 drawstring(120,5," Press ENTER to go To next screen",GLUT_BITMAP_HELVETICA_18);
	 drawstring(-45,5,"Maximize window for better view",GLUT_BITMAP_HELVETICA_12);
	 glColor3f(1,1,1);
	 output(5,160,"");
	 glColor3f(1,0,0);
	 drawstring(270,600,"SJBIT",GLUT_BITMAP_TIMES_ROMAN_24);
	 glColor3f(1,1,1);
	 output(210,500,"DEPARTMENT OF ");
	 output(80.0,450,"COMPUTER SCIENCE AND ENGINEERING");
	 glColor3f(1,0,1);
	 output(200,400,"A Mini Project On:-");
	 glColor3f(0,1,0.5);
	 output(160,350,"\"EGG CATCHING GAME\"");
	 glColor3f(1,0,1);
	 output(40,100,"");
	 //glBegin(GL_LINES);
	 glVertex2f(40,98);
	 glVertex2f(50,98);
	 glEnd();
	 glColor3f(1,0,0);
	 output(40,90," ");
	 output(40,80,"");
	 glColor3f(1,0,1);
	 output(40,60,"");
	 //glBegin(GL_LINES);
	 glVertex2f(40,58);
	 glVertex2f(98,58);
	 glEnd();
	 glColor3f(1,0,0);
	 output(40,50,"");
	 glColor3f(1,0,0);
	 drawstring(72,50,"",GLUT_BITMAP_HELVETICA_12);
	 glColor3f(1,0,0);
	 output(70,40,"");
	 glColor3f(1,0,0);
	 output(40,30,"");
	 glColor3f(1,0,0);
	 drawstring(72,30,"",GLUT_BITMAP_HELVETICA_12);
	 output(70,20,"");
	 glFlush();
}

void startscreen(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,1.0,0.0);
	output(25,600,"WELCOME TO THE EGG CATCHING GAME");
	output(50,500,"1. NEW GAME");
	output(50,400,"2. INSTRUCTIONS");
	output(50,300,"3. QUIT");
	glFlush();
}

void instructions(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,0.0);
	output(45,600,"INSTRUCTIONS:");
	glBegin(GL_LINES);
	glVertex2f(45,138);
	glVertex2f(90,138);
	glEnd();
	glColor3f(0,1,0);
	output(20,500,"* The objective of the game is to catch the eggs in the basket");
	output(20,450,"* To move Basket use mouse or A or D");
	output(20,400,"* To Start, press key 's' or 'S'");
	output(20,350,"* To Quit manually, press key 'q' or 'Q'");
	output(20,300,"* RULES : If the player misses 10 eggs,then 'Game Over'.");
	output(20,250,"* For each level, speed is Increased BEST OF LUCK");
	output(20,200,"* Press ESC to GO BACK");
	glFlush();
}

void winscreen(){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(0.0,1.0,0.0);
	output(55,120,"CONGRATS!!!");
	glColor3f(1.0,0.0,1.0);
	output(15,100,"YOU WON");
	output(35,60,"* PRESS ESC TO GO TO MAIN MENU");
	output(35,45,"* PRESS 1 TO RESTART THE GAME");
	glFlush();
}

void timeover(){
	 glClear(GL_COLOR_BUFFER_BIT);
	 glColor3f(1.0,0,0);
	 output(70,110,"TIMEOVER");
	 glColor3f(0,1,0);
	 output(50,100,"YOU HAVE LOST THE GAME");
	 output(50,90,"BETTER LUCK NEXT TIME");
	 output(40,40,"* PRESS ESC TO GO TO MAIN MENU");
	 output(40,30,"* PRESS 1 TO RESTART THE GAME");
	 glFlush();
}

void idle(){
	if(df==1){
		end=clock();
		count=(end-start)/CLOCKS_PER_SEC;
	if(count==60){
		df=4;
	}
	else
		if(count<60){
			df=5;
		}
	}
	glutPostRedisplay();
}
 
void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	if(df==10)
		frontscreen();
      	else  if(df==0)
      		startscreen();
      	else if(df == 1){
		ground(0 , 650);
		backk(0, 650);
		duck(40,375);
		duck(180,375);
		duck(320,375);
		sun();
		cloud1();
		cloud2();
		line(0,375);

		int i;
		char z[12]="";
		char level1[12]="LEVEL 1";
		char level2[12]="LEVEL 2";
		char level3[12]="LEVEL 3";
		char level4[12]="LEVEL 4";

		if(s>=1){
			glColor3f(0,0,1);
			glRasterPos2i(10,10);
			for(i=0;i<12;i++)
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13,z[i]);
			if(level_count==1){
				glColor3f(1,1,1);
				glRasterPos2i(500,300);

				for(i=0;i<12;i++)
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13,level1[i]);
			}
			else if(level_count==2){
				glColor3f(1,0,0);
				glRasterPos2i(500,300);

				for(i=0;i<12;i++)
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13,level2[i]);
			}
			else if(level_count==3){
				glColor3f(0,1,1);
				glRasterPos2i(500,300);

				for(i=0;i<12;i++)
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13,level3[i]);
			}

			if(level_count==4){
				glColor3f(1,0,1);
				glRasterPos2i(500,300);

				for(i=0;i<12;i++)
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13,level4[i]);
			}

			if(egg_yc<=10)
				egg_start();
			egg();
			basket(basket_x,basket_y);

			if(eggs_caught>=10){
				egg_yc-=speed_2;
				level_count=2;
			}

			if(eggs_caught>=20){
				egg_yc-=speed_3;
				level_count=3;
			}

			if(eggs_caught>=30){
				egg_yc-=speed_4;
				level_count=4;
			}

			else
				egg_yc-=speed_1;
			score();
		}

		else
			start_screen(40,300);
	}
	else if(df==2)
        	instructions();
    	else if(df==3)
      		exit(1);
      	else if(df == 4)
      		timeover();
      	else if(df==5)
      		winscreen();
	glFlush();
	glutSwapBuffers();
}

void basket_set(int a,int b){
	basket_x=a;
	basket_y=b;
	glutPostRedisplay();
}

void myReshape(int w,int h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble)w,0.0,(GLdouble)h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0,0,w,h);
	a=w;
	b=h;
}

void keys(unsigned char key,int x,int y){
	if(df==10 && key==13) df=0;
	else if((df==0 || df==4 || df==5) && key=='1'){
	     df=1;
	     start=clock();
	     glutPostRedisplay();
	}
	else if(df==0 && key=='2') df=2;
	else if(df==0 && key=='3') df=3;
	else if(key==27) df = 0;
	if(key=='q'||key=='Q'){
		printf("\n\n\n\t\tQUIT BY PLAYER\n\n");
		print_score();
	}

	if(key=='s'||key=='S') s+=1;

	if(key=='a'||key=='A'){
		basket_x-=10;
		if(basket_x<=0) basket_x=10;
	}

	if(key=='d'||key=='D'){
		basket_x+=10;
		if(basket_x>=500) basket_x=490;
	}
	glutPostRedisplay ();
}

void menu(int id){
	switch(id){
		case 1: s+=1;
		break;

		case 2:print_score();
		break;

		case 3: printf("\n\n\n\t\tQUIT BY PLAYER\n");
		break;

		default:exit(0);
	}
	glutPostRedisplay();
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(a,b);
	glutCreateWindow("EGG GAME");
	myinit();
	glutInitWindowPosition(100, 100);
	glutCreateMenu(menu);
	glutAddMenuEntry("Start game",1);
	glutAddMenuEntry("score",2);
	glutAddMenuEntry("Quit",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(display);
	glutKeyboardFunc(keys);
	//glutIdleFunc(idle);
	glutPassiveMotionFunc(basket_set);
	glutIdleFunc(display);
	glutReshapeFunc(myReshape);
	glutMainLoop();
}
