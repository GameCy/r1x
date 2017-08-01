#ifndef OGL_H
#define OGL_H
#include <QOpenGLFunctions>

class OGL : public QOpenGLFunctions
{
public:
    OGL();
};

extern OGL ogl;

#endif // OGL_H
