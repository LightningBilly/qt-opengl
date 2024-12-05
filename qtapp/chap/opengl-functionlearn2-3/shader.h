#ifndef SHADER_H
#define SHADER_H

#include <QDebug>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QString>

class Shader {
public:
    Shader(const QString & vertexSourcePath, const QString & fragmentSourcePath);
    ~Shader();
    QOpenGLShaderProgram shaderProgram;

    void use();

    void setMat4(const QString& name, const QMatrix4x4& value);
    void setInt(const QString& name, const GLint& value);
    void setFloat(const QString& name, const GLfloat& value);
    void setVec4(const QString& name, const QVector4D& value);
    void setVec3(const QString& name, const QVector3D& value);
};


#endif // SHADER_H
