#include "shader.h"

Shader::Shader(const QString &vertexSourcePath, const QString &fragmentSourcePath)
{
    // 着色器
    QOpenGLShader vertexShader(QOpenGLShader::Vertex);
    bool succ = vertexShader.compileSourceFile(vertexSourcePath);
    if(!succ) {
        qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED"<<endl;
        qDebug() << vertexShader.log() <<endl;
    }

    QOpenGLShader fragmentShader(QOpenGLShader::Fragment);
    succ = fragmentShader.compileSourceFile(fragmentSourcePath);
    if(!succ) {
        qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED"<<endl;
        qDebug() << fragmentShader.log() <<endl;
    }

    shaderProgram.addShader(&vertexShader);
    shaderProgram.addShader(&fragmentShader);
    succ = shaderProgram.link();

    if(!succ) {
        qDebug() << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED"<<endl;
        qDebug() << shaderProgram.log() <<endl;
    }

}

Shader::~Shader()
{

}


void Shader::use() {
    shaderProgram.bind();
}


void Shader::setMat4(const QString& name, const QMatrix4x4& value) {
    GLuint loc = shaderProgram.uniformLocation(name);
    shaderProgram.setUniformValue(loc, value);
}

void Shader::setInt(const QString& name, const GLint& value){
    GLuint loc = shaderProgram.uniformLocation(name);
    shaderProgram.setUniformValue(loc, value);
}

void Shader::setFloat(const QString& name, const GLfloat& value){
    GLuint loc = shaderProgram.uniformLocation(name);
    shaderProgram.setUniformValue(loc, value);
}

void Shader::setVec4(const QString& name, const QVector4D& value){
    GLuint loc = shaderProgram.uniformLocation(name);
    shaderProgram.setUniformValue(loc, value);
}

void Shader::setVec3(const QString& name, const QVector3D& value){
    GLuint loc = shaderProgram.uniformLocation(name);
    shaderProgram.setUniformValue(loc, value);
}
