#include "widget.h"
#include "ui_widget.h"
#include "iostream"
#include <QOpenGLShader>
#include <QVector4D>
#include <QtMath>
#include <QImage>

using namespace std;

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent),VBO(QOpenGLBuffer::VertexBuffer), EBO(QOpenGLBuffer::IndexBuffer)
    //, ui(new Ui::Widget)
{
    //ui->setupUi(this);
}

Widget::~Widget()
{
    //delete ui;
    delete texture1;
}


unsigned int indices[] = {
    // 注意索引从0开始!
    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    // 这样可以由下标代表顶点组合成矩形

    0, 1, 3, // 第一个三角形
    1, 3, 2  // 第二个三角形
};

void Widget::initializeGL() {
    cout<<"initializeGL"<<endl;
    float vertices[] = {
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };

    this->initializeOpenGLFunctions();        //初始化opengl函数
   if(!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/shader/triangle.vert")){     //添加并编译顶点着色器
       qDebug()<<"ERROR:"<<shaderProgram.log();    //如果编译出错,打印报错信息
   }
   if(!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/shader/triangle.frag")){   //添加并编译片段着色器
       qDebug()<<"ERROR:"<<shaderProgram.log();    //如果编译出错,打印报错信息
   }
   if(!shaderProgram.link()){                      //链接着色器
       qDebug()<<"ERROR:"<<shaderProgram.log();    //如果链接出错,打印报错信息
   }

   //VAO.create();       //生成VAO对象
   //VAO.bind();         //绑定VAO，之后所以的顶点缓冲对象的操作都会存储到VAO中
   QOpenGLVertexArrayObject::Binder{&VAO};
   EBO.create();
   EBO.bind();
   EBO.allocate(indices,sizeof(indices));

   VBO.create();       //生成VBO对象
   VBO.bind();         //将VBO绑定到当前的顶点缓冲对象（QOpenGLBuffer::VertexBuffer）中
   //将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度
   VBO.allocate(vertices,sizeof(vertices));
// (int location, GLenum type, int offset, int tupleSize, 8*sizeof (GLfloat));
//   shaderProgram.setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(GLfloat) * 8);
//   shaderProgram.enableAttributeArray(0);

//   shaderProgram.setAttributeBuffer(1, GL_FLOAT, 3* sizeof(float), 3, sizeof(GLfloat) * 8);
//   shaderProgram.enableAttributeArray(1);

//   shaderProgram.setAttributeBuffer(2, GL_FLOAT, 6* sizeof(float), 2, sizeof(GLfloat) * 8);
//   shaderProgram.enableAttributeArray(2);


   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof (GLfloat), (void*)0);
   glEnableVertexAttribArray(0);

   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof (GLfloat), (void*)(3* sizeof(float)));
   glEnableVertexAttribArray(1);

   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof (GLfloat), (void*)(6* sizeof(float)));
   glEnableVertexAttribArray(2);

   // VAO.release();      //解绑VAO，安全使用

    texture1 = new QOpenGLTexture(QImage("D:/selfad/LearnOpenGL/resources/textures/container.jpg"));
    texture1->setWrapMode(QOpenGLTexture::Repeat);
    texture1->setMinificationFilter(QOpenGLTexture::Nearest);
    texture1->setMagnificationFilter(QOpenGLTexture::Linear);
}
void Widget::paintGL()
{
   // cout<<"paint GL"<<endl;
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE1);
    texture1->bind();
    shaderProgram.setUniformValue("texture2", 1);
    shaderProgram.setUniformValue("texture1", 0);
    shaderProgram.bind();
    QOpenGLVertexArrayObject::Binder{&VAO};
    // VAO.bind(); // 执行数据传递过程
    //core->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //core->glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // VAO.release();

    update();
}
void Widget::resizeGL(int w, int h){
    cout<<"w : "<< w<< "h : "<<h<< endl;
}
