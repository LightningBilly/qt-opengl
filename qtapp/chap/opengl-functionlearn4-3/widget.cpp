#include "widget.h"
#include "ui_widget.h"
#include "iostream"
#include <QOpenGLShader>
#include <QVector4D>
#include <QtMath>
#include <QImage>

using namespace std;

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
    //, ui(new Ui::Widget)
{
    //ui->setupUi(this);
}

Widget::~Widget()
{
    //delete ui;
    delete shader;
    delete texture1;
}


void Widget::initializeGL() {
    cout<<"initializeGL"<<endl;
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();

    core->glGenVertexArrays(2, VAO);
    // 所有跟gl_array_buffer有关系的操作状态，它都记录下来

    // 创造vbo
    core->glGenBuffers(2, VBO);
    core->glGenBuffers(1, &EBO);

    core->glBindVertexArray(VAO[0]); // 开始录制

    core->glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

    core->glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof (GLfloat), (void*)0);
    // 1. location 用来跟着色器对应的，一般大小为16个
    // 2. 顶点属性的大小
    // 3. 类型
    // 4. 是否标准化
    // 5. 步长

    core->glEnableVertexAttribArray(0);

    core->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof (GLfloat), (void*)(3* sizeof(float)));
    core->glEnableVertexAttribArray(1);

    // 绑定空缓冲区
    core->glBindVertexArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);

    texture1 = new QOpenGLTexture(QImage("D:/selfad/LearnOpenGL/resources/textures/container.jpg"));
    texture1->setWrapMode(QOpenGLTexture::Repeat);
    texture1->setMinificationFilter(QOpenGLTexture::Nearest);
    texture1->setMagnificationFilter(QOpenGLTexture::Linear);


    texture2 = new QOpenGLTexture(QImage("D:/selfad/LearnOpenGL/resources/textures/awesomeface.png").mirrored(false, true));
    texture2->setWrapMode(QOpenGLTexture::Repeat);
    texture2->setMinificationFilter(QOpenGLTexture::Nearest);
    texture2->setMagnificationFilter(QOpenGLTexture::Linear);
    // 着色器
    shader = new Shader(":/shaders/shader/triangle.vert", ":/shaders/shader/triangle.frag");
    shader->use();
    shader->setInt("texture1", 0);
    shader->setInt("texture2", 1);
}
void Widget::paintGL()
{
   // cout<<"paint GL"<<endl;
    core->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    core->glClear(GL_COLOR_BUFFER_BIT);
    core->glEnable(GL_DEPTH_TEST);
    core->glActiveTexture(GL_TEXTURE0);
    texture1->bind();
    core->glActiveTexture(GL_TEXTURE1);
    texture2->bind();
    shader->use();
    QMatrix4x4 model;
    model.rotate(time.elapsed()/50, QVector3D(5,1,0));
    shader->setMat4("model", model);


    QMatrix4x4 view;
    view.translate(QVector3D(0,0,-3));
    shader->setMat4("view", view);


    QMatrix4x4 projection;
    projection.perspective(45, this->width()*1.0/this->height(), 0.1, 100);
    shader->setMat4("projection", projection);


    core->glBindVertexArray(VAO[0]); // 执行数据传递过程
    //core->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    core->glDrawArrays(GL_TRIANGLES, 0, 36);
    //core->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    core->glBindVertexArray(0);

    update();
}
void Widget::resizeGL(int w, int h){
    cout<<"w : "<< w<< "h : "<<h<< endl;
}
