#include "widget.h"
#include "ui_widget.h"
#include "iostream"
#include <QOpenGLShader>
#include <QVector4D>
#include <QtMath>

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
        // 位置              // 颜色
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
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

    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof (GLfloat), (void*)0);
    // 1. location 用来跟着色器对应的，一般大小为16个
    // 2. 顶点属性的大小
    // 3. 类型
    // 4. 是否标准化
    // 5. 步长

    core->glEnableVertexAttribArray(0);

    core->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof (GLfloat), (void*)(3* sizeof(float)));
    core->glEnableVertexAttribArray(1);
    // 绑定空缓冲区
    core->glBindVertexArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);

    // 着色器
    shader = new Shader(":/shaders/shader/triangle.vert", ":/shaders/shader/triangle.frag");
}
void Widget::paintGL()
{
   // cout<<"paint GL"<<endl;
    core->glClearColor(0.6f, 0.8f,0.6f, 1.0f);
    core->glClear(GL_COLOR_BUFFER_BIT);

    shader->use();
    shader->setVec4("outColor", QVector4D(g%256*1.0/256, 0.5f, 0.2f, 1.0f));
    g++;
    core->glBindVertexArray(VAO[0]); // 执行数据传递过程
    //core->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    core->glDrawArrays(GL_TRIANGLES, 0, 3);
    //core->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    core->glBindVertexArray(0);

    update();
}
void Widget::resizeGL(int w, int h){
    cout<<"w : "<< w<< "h : "<<h<< endl;
}
