#include "axbopenglwidget.h"
#include <iostream>
#include <qlogging.h>
using namespace std;

float vertices[] = {
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f
};

unsigned int indices[] = {
  0,1,3,
    1,2,3
};
AXBOpenGLWidget::AXBOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    // cout<<fragmentShaderSource<<endl;
    // qDebug()<<vertexShaderSource<<endl;
}

unsigned int VBO, VAO, EBO;
unsigned int shaderProgram;

AXBOpenGLWidget::~AXBOpenGLWidget() {
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

    shaderProgram.bind();
    GLint posLocation = 2;// shaderProgram.attributeLocation("aPos");
    shaderProgram.bindAttributeLocation("aPos", posLocation);
    cout<<"pos:"<<posLocation<<endl;
    //告知显卡如何解析缓冲里的属性值：
    //第0个数据：有3个值；float类型；不需要标准化；步长；偏移量是0（因为是第一个数据，所以没有偏移量）
    glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //开启VAO管理的第一个属性值
    glEnableVertexAttribArray(posLocation);

    //VAO、VBO已经记录了足够的信息了，解除绑定
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);

    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (indices),
                 indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void AXBOpenGLWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
}

void AXBOpenGLWidget::paintGL()
{
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.bind();//使用此着色器，没有这行则使用默认的着色器
    glBindVertexArray(VAO);//绑定VAO以便知道该如何使用数据。
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glDrawArrays(GL_TRIANGLES,0,6);//从0开始找6个点------------注意这里的改变---

    switch(m_shape) {
    case Rect:
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,&indices);
        break;
    default:
        break;
    }

}
