#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL/QGLWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT
private:
    QString type = "GL_POINTS";
    //Alpha-test
    int Func = GL_ALWAYS;
    int Ref = 1.0;
    //Scissor-test
    int x = 0, y = 0;
    int scWidth = 642, scHeight = 597;
    int winWidth, winHeight;
    //Color-test
    int sFactor= GL_ZERO, dFactor = GL_ZERO;

public:
    explicit GLWidget(QWidget *parent = 0);
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);


private slots:
    void changeType(QString type);
    //Alpha-test
    void changeFunc(int f);
    void changeRef(int r);
    //Scissor-test
    void changeX(int x);
    void changeY(int y);
    void changeWidth(int width);
    void changeHeight(int height);
    //Color-test
    void changeSfactor(QString s);
    void changeDfactor(QString d);
    //lab3
    void changeAngle(int angle);
    void changeDepth(int depth);
};

#endif // GLWIDGET_H
