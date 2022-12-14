#ifndef AXBOPENGLWIDGET_H
#define AXBOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>
#include <QTimer>

class AXBOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_4_5_Core
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
};

#endif // AXBOPENGLWIDGET_H
