#include "axbopenglwidget.h"
#include <iostream>
#include <qlogging.h>
#include<QTime>
#include <cmath>
using namespace std;
float colorRatio = 0.5f;
float vertices[] =
{
    //位置坐标              纹理坐标
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 0.0f,
     0.5f, 0.5f, -0.5f,     1.0f, 1.0f,
     0.5f, 0.5f, -0.5f,     1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f,     0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f,     0.0f, 0.0f,
    0.5f, -0.5f, 0.5f,      1.0f, 0.0f,
    0.5f, 0.5f, 0.5f,       1.0f, 1.0f,
    0.5f, 0.5f, 0.5f,       1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,      0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,     0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f,      1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f,     1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,     0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,      1.0f, 0.0f,

     0.5f, 0.5f, 0.5f,      1.0f, 0.0f,
     0.5f, 0.5f, -0.5f,     1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
     0.5f, -0.5f, 0.5f,     0.0f, 0.0f,
     0.5f, 0.5f, 0.5f,      1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 1.0f,
     0.5f, -0.5f, 0.5f,     1.0f, 0.0f,
     0.5f, -0.5f, 0.5f,     1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,     0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f,     0.0f, 1.0f,
     0.5f, 0.5f, -0.5f,     1.0f, 1.0f,
     0.5f, 0.5f, 0.5f,      1.0f, 0.0f,
     0.5f, 0.5f, 0.5f,      1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,      0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f,     0.0f, 1.0f
};
QVector<QVector3D> cubePositions =
{
    QVector3D( 0.0f, 0.0f, 0.0f),
    QVector3D( 2.0f, 5.0f, -15.0f),
    QVector3D(-1.5f, -2.2f, -2.5f),
    QVector3D(-3.8f, -2.0f, -12.3f),
    QVector3D( 2.4f, -0.4f, -3.5f),
    QVector3D(-1.7f, 3.0f, -7.5f),
    QVector3D( 1.3f, -2.0f, -2.5f),
    QVector3D( 1.5f, 2.0f, -2.5f),
    QVector3D( 1.5f, 0.2f, -1.5f),
    QVector3D(-1.3f, 1.0f, -1.5f)
};
unsigned int indices[] = {
    0,1,3,
    1,2,3,
};
AXBOpenGLWidget::AXBOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    // cout<<fragmentShaderSource<<endl;
    // qDebug()<<vertexShaderSource<<endl;
    connect(&timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
    timer.start(60);

    setFocusPolicy(Qt::StrongFocus);
}

unsigned int VBO, VAO, EBO;
unsigned int shaderProgram;

AXBOpenGLWidget::~AXBOpenGLWidget() {
    // if(!isValid())return;
    makeCurrent();
    glDeleteBuffers(1, &VBO);glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
    doneCurrent();
}

void AXBOpenGLWidget::drawShape(AXBOpenGLWidget::Shape shape) {
    m_shape = shape;
    update();
}

void AXBOpenGLWidget::setWireframe(bool val)
{
    makeCurrent();
    if(val) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    update();
    doneCurrent();
}

void AXBOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    //---------以下是使用自定义着色器----------------------------


    //链接两个编译好的着色器
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/shapes.vert");//创建着色器程序对象
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/shapes.frag");// 创建
    bool succ = shaderProgram.link();
    if(!succ){
        cout<<"sh failed"<<endl;
    }

    //1、创建VBO和VAO对象，并赋予ID
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //2、绑定VBO和VAO对象
    glBindVertexArray(VAO);//使OpenGL知道这个uint类型的对象表示一个VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //为当前绑定到GL_ARRAY_BUFFER的缓冲区对象创建一个新的数据存储，使用参数三的数据初始化数据存储
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    auto step = 5 * sizeof(float);
    //告知显卡如何解析缓冲里的属性值：
    //第0个数据：有3个值；float类型；不需要标准化；步长；偏移量是0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, step, (void*)0);
    //开启VAO管理的第一个属性值
    glEnableVertexAttribArray(0);

    //第1个数据：有3个值；float类型；不需要标准化；步长；偏移量是3*float（因为是第一个数据，所以没有偏移量）
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, step, (void*)(3*sizeof(float)));
    //开启VAO管理的第一个属性值
    glEnableVertexAttribArray(1);


    //VAO、VBO已经记录了足够的信息了，解除绑定
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);

    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (indices),
                 indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    textureWall = new QOpenGLTexture(QImage(":/image/images/wall.jpg").mirrored());
    textureSmile = new QOpenGLTexture(QImage(":/image/images/awesomeface.png").mirrored());

    shaderProgram.bind();
    shaderProgram.setUniformValue("textureWall",0);
    shaderProgram.setUniformValue("textureSmile",1);
    // textureSmile->generateMipMaps();
    glBindVertexArray(0);


    QMatrix4x4 projection;
    projection.perspective(45, float(width())/height(), 0.1, 100);
    shaderProgram.setUniformValue("projection", projection);
}

void AXBOpenGLWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
}

void AXBOpenGLWidget::paintGL()
{
    QMatrix4x4 model;
    QMatrix4x4 view;
    unsigned int time = QTime::currentTime().msec();

    // matrix.translate(0.5, -0.5,0);
    model.rotate(time, 1.0f, 0.0f, 0.0f);
    view.translate(0.0, 0.0, -3);

    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    shaderProgram.bind();//使用此着色器，没有这行则使用默认的着色器
    glBindVertexArray(VAO);//绑定VAO以便知道该如何使用数据。
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glDrawArrays(GL_TRIANGLES,0,6);//从0开始找6个点------------注意这里的改变---
    shaderProgram.setUniformValue("ratio", colorRatio);
    switch(m_shape) {
    case Rect:
        // glActiveTexture(GL_TEXTURE0);
        textureWall->bind(0);
        // glActiveTexture(GL_TEXTURE1);
        textureSmile->bind(1);
        shaderProgram.setUniformValue("view", view);

        foreach(auto item, cubePositions){
            model.setToIdentity();
            model.translate(item);
            model.rotate(time, 1.0f, 0.0f, 0.0f);
            shaderProgram.setUniformValue("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        break;
    default:
        break;
    }

}

#include<QKeyEvent>
void AXBOpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up :
        colorRatio+=0.1f;
        break;
    case Qt::Key_Down:
        colorRatio-=0.1f;
        break;
    default:
        break;
    }
    if(colorRatio>1) colorRatio=1;
    if(colorRatio<0)colorRatio=0;
    shaderProgram.bind();
    shaderProgram.setUniformValue("ratio", colorRatio);
    update();
}

void AXBOpenGLWidget::on_timeout()
{
    if(m_shape == Shape::None)return;
    makeCurrent();
/*
    int timeValue = QTime::currentTime().second();
    float greenValue = (sin(timeValue)/2.0f)+0.5f;
    shaderProgram.setUniformValue("ourColor", 0.0f, greenValue, 0.0f, 1.0f);
*/
    doneCurrent();
    update();
}
