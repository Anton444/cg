#include "glwidget.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <windows.h>

using namespace std;

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent){}

void GLWidget::initializeGL() {
    glClearColor(0.94, 0.94, 0.94, 0);
}
//!!!!!!!!!!!!!!!
bool coorTest = true;
double red[20], green[20], blue[20], coorX[20], coorY[20], alpha[20];
double rotAngle = 45;
double dpth = 1;
//!!!!!!!!!!!!!!!

void constVar(int w, int h) {
    srand(time(0));
    if(coorTest == true){
        for(int i = 0; i < 20; i++){
            red[i] = (rand() % 100)/100.0;
            green[i] = (rand() % 100)/100.0;
            blue[i] = (rand() % 100)/100.0;
            alpha[i] = (rand() % 100)/100.0;
            coorX[i] = rand()%640 + 30;
            coorY[i] = rand()%580 + 30;
        }
        coorTest = false;
    }
    for(int i = 0; i < 20; i++) {
        glColor4f(red[i], green[i], blue[i], alpha[i]);
        glVertex3f(w - coorX[i], h - coorY[i], 0);
    }
    glEnd();
    return;

}
void drawRect(double x, double y, double len, double angle) {
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(x - len*cos(angle), y, 0);
    glVertex3f(x + len*cos(angle), y, 0);
    glVertex3f(x + len*cos(angle), y - len*sin(angle), 0);
    glVertex3f(x - len*cos(angle), y - len*sin(angle), 0);
    glEnd();
}
void fractal(double len, double dep, double x, double y, double angle) {
    double inclineL = rotAngle;
    double inclineR = 90 - inclineL;
    if(dep > 0) {
        glColor4f(dep/60, 1/dep, 0.1 , 0.5);
        glVertex3f(x + len*sin(angle)/2 - len*sin(angle)/5                  , y + len*cos(angle)/2 - len*cos(angle)/5, 0);
        glVertex3f(x + len*cos(angle) + len*sin(angle)/2 - len*sin(angle)/5 , y - len*sin(angle) + len*cos(angle)/2 - len*cos(angle)/5, 0);
        glVertex3f(x + len*cos(angle) - len*sin(angle)/2 + len*sin(angle)/5 , y - len*sin(angle) - len*cos(angle)/2 + len*cos(angle)/5, 0);
        glVertex3f(x - len*sin(angle)/2 + len*sin(angle)/5                  , y - len*cos(angle)/2 + len*cos(angle)/5, 0);

        x = x + len*cos(angle);
        y = y - len*sin(angle);
        fractal(len*cos(inclineL*M_PI/180), dep - 1, x, y, angle + inclineL*M_PI/180);

        fractal(len*cos(inclineR*M_PI/180), dep - 1, x, y, angle - inclineR*M_PI/180);
    }
}

void lab1 (QString type, int w, int h){
    if(type == "GL_POINTS") {
        glPointSize(5);
        glBegin(GL_POINTS);
        constVar(w, h);
    }
    if(type == "GL_LINES") {
        glLineWidth(2);
        glBegin(GL_LINES);
        constVar(w, h);
    }
    if(type == "GL_LINE_STRIP") {
        glBegin(GL_LINE_STRIP);
        constVar(w, h);
    }
    if(type == "GL_LINE_LOOP") {
        glBegin(GL_LINE_LOOP);
        constVar(w, h);
    }
    if(type == "GL_TRIANGLES") {
        glBegin(GL_TRIANGLES);
        constVar(w, h);
    }
    if(type == "GL_TRIANGLE_STRIP") {
        glBegin(GL_TRIANGLE_STRIP);
        constVar(w, h);
    }
    if(type == "GL_TRIANGLE_FAN") {
        glBegin(GL_TRIANGLE_FAN);
        constVar(w, h);
    }
    if(type == "GL_QUADS") {
        glBegin(GL_QUADS);
        constVar(w, h);
    }
    if(type == "GL_QUAD_STRIP") {
        glBegin(GL_QUAD_STRIP);
        constVar(w, h);
    }
    if(type == "GL_POLYGON") {
        glBegin(GL_POLYGON);
        constVar(w, h);
        return;
    }
    if(type == "FRACTAL") {

        glBegin(GL_QUADS);
        glPointSize(10);
        double angle = -90;
        fractal(200, dpth, 450, 50, angle*M_PI/180);
        glEnd();
    }
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_SCISSOR_TEST);
    glScissor(this->x*this->winWidth/100.0f, this->y*this->winHeight/100, this->winWidth*this->scWidth/100, this->winHeight*this->scHeight/100);
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(this->x*this->winWidth/100.0f, this->y*this->winHeight/100, 0);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(this->winWidth*this->scWidth/100 + this->x*this->winWidth/100.0f, this->y*this->winHeight/100, 0);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(this->winWidth*this->scWidth/100 + this->x*this->winWidth/100.0f, this->winHeight*this->scHeight/100 + this->y*this->winHeight/100, 0);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(this->x*this->winWidth/100.0f, this->winHeight*this->scHeight/100 + this->y*this->winHeight/100, 0);
    glEnd();
    glEnable(GL_BLEND);
    glBlendFunc(this->sFactor, this->dFactor);
    glEnable(GL_ALPHA_TEST);
    cout<<this->Ref/100.0f<<endl;
    glAlphaFunc(GL_NEVER+this->Func, this->Ref/100.0f);
    lab1(type, width(), height());

    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_SCISSOR_TEST);
}

void GLWidget::resizeGL(int w, int h)
{
    this->winWidth = w;
    this->winHeight = h;

    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0 , w, 0 , h, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::changeType(QString type)
{
    this->type = type;
    glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();
}
//Alpha-test
void GLWidget::changeFunc(int f)
{
    this->Func = f;
    glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();
}

void GLWidget::changeRef(int r)
{
    this->Ref = r;
    rotAngle = r;
    glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();
}

//lab3
void GLWidget::changeAngle(int angle) {
    rotAngle = angle;
    this->updateGL();
}

void GLWidget::changeDepth(int depth) {
    this->updateGL();
}
//Scissor-test
void GLWidget::changeX(int x)
{
    this->x = x;
    glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();
}

void GLWidget::changeY(int y)
{
    this->y = y;
    glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();
}

void GLWidget::changeWidth(int scWidth)
{
    this->scWidth = scWidth;
    glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();
}

void GLWidget::changeHeight(int scHeight)
{
    if(scHeight > 15)
        this->scHeight = scHeight;
    else
        dpth = scHeight;
    glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();
}
//Color-test
int getBlend(QString m)
{
    if(m == "GL_ZERO")return GL_ZERO;
    if(m == "GL_ONE")return GL_ONE;
    if(m == "GL_DST_COLOR")return GL_DST_COLOR;
    if(m == "GL_ONE_MINUS_DST_COLOR")return GL_ONE_MINUS_DST_COLOR;
    if(m == "GL_SRC_ALPHA")return GL_SRC_ALPHA;
    if(m == "GL_ONE_MINUS_SRC_ALPHA")return GL_ONE_MINUS_SRC_ALPHA;
    if(m == "GL_DST_ALPHA")return GL_DST_ALPHA;
    if(m == "GL_ONE_MINUS_DST_ALPHA")return GL_ONE_MINUS_DST_ALPHA;
    if(m == "GL_SRC_ALPHA_SATURATE")return GL_SRC_ALPHA_SATURATE;
    if(m == "GL_SRC_COLOR") return GL_SRC_COLOR;
    if(m == "GL_ONE_MINUS_SRC_COLOR") return GL_ONE_MINUS_SRC_COLOR;
}

void GLWidget::changeSfactor(QString s)
{
    this->sFactor=getBlend(s);
    glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();
}

void GLWidget::changeDfactor(QString d)
{
    this->dFactor=getBlend(d);
    glClear(GL_COLOR_BUFFER_BIT);
    this->updateGL();
}

