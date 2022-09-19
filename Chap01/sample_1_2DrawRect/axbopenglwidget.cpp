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
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

void AXBOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    //1、创建VBO和VAO对象，并赋予ID
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //2、绑定VBO和VAO对象
    glBindVertexArray(VAO);//使OpenGL知道这个uint类型的对象表示一个VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //为当前绑定到GL_ARRAY_BUFFER的缓冲区对象创建一个新的数据存储，使用参数三的数据初始化数据存储
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //告知显卡如何解析缓冲里的属性值：
    //第0个数据：有3个值；float类型；不需要标准化；步长；偏移量是0（因为是第一个数据，所以没有偏移量）
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //开启VAO管理的第一个属性值
    glEnableVertexAttribArray(0);

    //VAO、VBO已经记录了足够的信息了，解除绑定
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);

//---------以下是使用自定义着色器----------------------------

    //顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建顶点着色器对象 GL_VERTEX_SHADER表示顶点着色器
    glShaderSource(vertexShader, 1, &vertexShaderSource,nullptr);//顶点着色器绑定源码
    glCompileShader(vertexShader);//编译顶点着色器
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//检查编译错误
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        //qDebug()<< "编译顶点着色器出错，错误信息：" << infoLog ;
    }

    //片段着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//创建片段着色器 GL_FRAGMENT_SHADER表示片段着色器
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        //qDebug()<< "编译片段着色器出错，错误信息：" << infoLog ;
    }

    //链接两个编译好的着色器
    shaderProgram = glCreateProgram();//创建着色器程序对象
    glAttachShader(shaderProgram, vertexShader);//添加要编译的程序
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);//链接着色器
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success); //检测链接错误
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        //qDebug()<< "链接着色器出错，错误信息：" << infoLog;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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

    glUseProgram(shaderProgram);//使用此着色器，没有这行则使用默认的着色器
    glBindVertexArray(VAO);//绑定VAO以便知道该如何使用数据。
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glDrawArrays(GL_TRIANGLES,0,6);//从0开始找6个点------------注意这里的改变---

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,&indices);
}
