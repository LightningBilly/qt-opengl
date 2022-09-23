#ifndef AXBOPENGLWIDGET_H
#define AXBOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include<QOpenGLTexture>

class AXBOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    enum Shape{None, Rect, Circle, Triangle};
    explicit AXBOpenGLWidget(QWidget *parent = nullptr);

    ~AXBOpenGLWidget();
    void drawShape(Shape shape);
    void setWireframe(bool val);
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
signals:

public slots:
    void on_timeout();
private:
    Shape m_shape;
    QOpenGLShaderProgram shaderProgram;
    QTimer timer;
    QOpenGLTexture *textureWall;
    QOpenGLTexture *textureSmile;
};

#endif // AXBOPENGLWIDGET_H
