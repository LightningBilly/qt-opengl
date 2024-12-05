#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QTime>
#include "shader.h"
#include <QOpenGLTexture>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QOpenGLFunctions_3_3_Core *core;
    GLuint VBO[2], VAO[2], EBO;
    Shader *shader;
    QTime time = QTime::currentTime();
    int g=0;
    QOpenGLTexture *texture1;

protected:

    virtual void initializeGL(); // 初始化，vao, vbo,着色器，纹理，相机
    virtual void paintGL(); // 画，渲染一次，循环要添加update() 函数
    virtual void resizeGL(int w, int h); // 视图、窗口大小变化


};
#endif // WIDGET_H
