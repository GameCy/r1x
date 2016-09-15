#ifndef _CAMERA_HEADER_
#define _CAMERA_HEADER_
#include <QMatrix4x4>
#include <QVector3D>
#include <QQuaternion>
#include "IClipper.h"
#include <QOpenGLShaderProgram>

#define default_fov 50.0f
#define default_near 1.0f
#define default_far 1000.0f
#define default_aspect 1.5f

class Camera : public IClipper
{
public:
	Camera();
	virtual ~Camera();

    bool    InitShaders();
    void    Setup(int width, int height, float nearZ= default_near, float farZ= default_far, float fov= default_fov, float aspect= default_aspect);
    void	ResetPosition();
    void    moveModel(QVector3D pos, QQuaternion rot);
    void    ParticleRenderingMode(bool on);

	void	SetClippingAreaSize(float dx, float dz);
	//  IClipper interface
    virtual bool	InVisibleArea(QVector3D pos);

    QVector3D mouseToGlobalCoords(float x, float y);
    bool    ScreenPointToGround(float tapX, float tapY, QVector3D& outPoint);
    void	UpdateViewVectors();

    QVector3D		Position;
    QVector3D		LookAt;
    QVector3D		UpVector;	// camera up vector

    QVector3D       LightPos;

	float	FieldOfView, Near, Far, Aspect;
    float   PixelWidth, PixelHeight; // viewport in pixels
    float   CanvasWidth, CanvasHeight;  // viewport in units

    QMatrix4x4		projectionMatrix; // projection
    QMatrix4x4		modelMatrix; // model view

    QOpenGLShaderProgram phongShaders;

    QVector3D ScreenUp;
    QVector3D ScreenRight;
    QVector3D ScreenUpRight;
    QVector3D ScreenDownRight;

private:
	float	clipHalfX, clipHalfZ;
};

#endif
