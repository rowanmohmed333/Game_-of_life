#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include<math.h>
#include<stdio.h>
using namespace std;

int phyWidth = 700;
int phyHeight = 700;
int logWidth = 52;
int logHeight = 60;
int centerX = logWidth/2;
int centerY = logHeight/2;
int mouseX= centerX, mouseY = centerY;
int movesq=0;
//mat
int mat[100][52][52];
int currentmat=0;

int flag=1;

void reset(){
    currentmat=0;
for (int j = 0;j<52;j++){

for (int k = 0;k<52;k++){

    mat[0][j][k]=0;
}}
}

void doMat(){




    for (int i = 0;i<99;i++){

        for (int j = 1;j<51;j++){

                for (int k = 1;k<51;k++){


                    int sum=0;
                    sum=sum+mat[i][j-1][k-1];
                    sum=sum+mat[i][j-1][k];
                    sum=sum+mat[i][j-1][k+1];
                    sum=sum+mat[i][j][k+1];
                    sum=sum+mat[i][j+1][k+1];
                    sum=sum+mat[i][j+1][k];
                    sum=sum+mat[i][j+1][k-1];
                    sum=sum+mat[i][j][k-1];


                    if((sum==0)||(sum==1)){
                        mat[i+1][j][k]=0;
                    }else if(sum == 2){
                        mat[i+1][j][k]=mat[i][j][k];
                    }else if(sum== 3){
                        mat[i+1][j][k]=1;
                    }else{
                        mat[i+1][j][k]=0;
                    }

}
}
}
}
void mouseClick(int btn, int state, int x, int y)
{


    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
     mouseX = x;
     mouseX=0.5+1.0*mouseX*logWidth/phyWidth;
     mouseY = phyHeight - y;
     mouseY=0.5+1.0*mouseY*logHeight/phyHeight;

     mat[0][mouseX][mouseY]=1;



     if((mouseX>=20) && (mouseX <= 28) &&(mouseY >= 35) &&(mouseY<=40 )&&(flag==1) ){
        flag=0;
        reset();
     }
     if((mouseX>=20) && (mouseX <= 28) &&(mouseY >= 25) &&(mouseY<=30 )&&(flag==1) ){
        exit(1);
     }

    }

    glutPostRedisplay();
}
void printSome(char *str, int x, int y){


glColor3f(1,1,1);
glRasterPos2d(x,y);
for(int i=0;i<strlen(str);i++){
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
}
}


void unit(int x,int y) {
if(x==0 || y==0 || x==51 || y==51) {
glLineWidth(3.0);
glColor3f(1,0,0);
}
else{
glLineWidth(10);
if(mat[currentmat][x][y]==1){
    glColor3f(0,0,1);
}else {
glColor3f(1,1,1);
}


}
glBegin(GL_QUADS);
      glVertex2f(x+0.1,y+0.1);
      glVertex2f(x+1-0.1,y+0.1);
      glVertex2f(x+1-0.1,y+1-0.1);
      glVertex2f(x+0.1,y+1-0.1);
glEnd();
}

void drawgrid() {
    for (int x=0;x<52;x++){
        for (int y=0; y<52;y++){
            unit(x,y);
        }
    }
}

init2D(){
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,logWidth,0,logHeight);
}




void intro(){



glColor3f(1,0.75,0.8);
glBegin(GL_QUADS);
glVertex2f(0,0);
glVertex2f(52,0);
glVertex2f(52,60);
glVertex2f(0,60);
glEnd();

glColor3f(1,1,1);
printSome("Conway's Game of Life",17,50);

glBegin(GL_QUADS);
glVertex2f(19,34);
glVertex2f(29,34);
glVertex2f(29,41);
glVertex2f(19,41);
glEnd();

glColor3f(0.5,0.5,0.5);
glBegin(GL_QUADS);
glVertex2f(20,35);
glVertex2f(28,35);
glVertex2f(28,40);
glVertex2f(20,40);
glEnd();
printSome("play",23,37);


glBegin(GL_QUADS);
glVertex2f(19,24);
glVertex2f(29,24);
glVertex2f(29,31);
glVertex2f(19,31);
glEnd();
glColor3f(0.5,0.5,0.5);
glBegin(GL_QUADS);
glVertex2f(20,25);
glVertex2f(28,25);
glVertex2f(28,30);
glVertex2f(20,30);
glEnd();
printSome("Exit",23,27);




for (int i=0 ; i<22;i++){

glBegin(GL_QUADS);
glVertex2f(1,1+3*i+movesq);
glVertex2f(3,1+3*i+movesq);
glVertex2f(3,3+3*i+movesq);
glVertex2f(1,3+3*i+movesq);
glEnd();

glBegin(GL_QUADS);
glVertex2f(49,1+3*i-movesq);
glVertex2f(51,1+3*i-movesq);
glVertex2f(51,3+3*i-movesq);
glVertex2f(49,3+3*i-movesq);
glEnd();

}

movesq++;
movesq=movesq%3;

}


void specialKeyboard(int key, int x, int y)
{

doMat();

if(key== GLUT_KEY_LEFT)
currentmat--;
if(key== GLUT_KEY_RIGHT)
currentmat++;
if(key== GLUT_KEY_F1)
reset();
if(key== GLUT_KEY_F2)
flag=1;


if(currentmat<0)
    currentmat=0;
if(currentmat>99)
    currentmat=99;

//printf("(current layer is [%d]\n)",currentmat);
glutPostRedisplay();
}



static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);


    drawgrid();
    printSome("Game of life",20,55);


char buf[10];

    sprintf(buf,"%d",currentmat);


printSome("current level:",2,55);
printSome(buf,12,55);


if (flag==1)
    intro();

    glutSwapBuffers();
    glFlush();
}

void Timer(int value) {

glutTimerFunc(100, Timer, value);
glutPostRedisplay();

}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(phyWidth,phyHeight);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Game Of Life Mohamad Ashraf & Rowan Mohamad");
    init2D();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutSpecialFunc(specialKeyboard);
    Timer(0);
    glutMainLoop();
}
