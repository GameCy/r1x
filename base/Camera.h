#ifndef _CAMERA_HEADER_
#define _CAMERA_HEADER_
#include <QMatrix4x4>
#include <QVector3D>
#include <QQuaternion>
#include "IClipper.h"
#include "Shader.h"

#define default_fov 50.0f
#define default_near 1.0f
#define default_far 1000.0f
#define default_aspect 1.5f

class Camera
{
public:
    Camera(ShaderPtr shader);
	virtual ~Camera();

    void    Setup(int width, int height, float nearZ= default_near, float farZ= default_far, float fov= default_fov, float aspect= default_aspect);
    void	ResetPosition();
    void    moveModel(QVector3D pos, QQuaternion rot, float scale=1.0f);

	void	SetClippingAreaSize(float dx, float dz);
	//  IClipper interface
    virtual bool	InVisibleArea(QVector3D pos);

    QVector3D mouseToGlobalCoords(float x, float y);
    bool    ScreenPointToGround(float tapX, float tapY, QVector3D& outPoint);
    void	UpdateViewVectors();

    QVector3D	Position;
    QVector3D	LookAt;
    QVector3D	UpVector;	// camera up vector

	float	FieldOfView, Near, Far, Aspect;
    float   PixelWidth, PixelHeight; // viewport in pixels
    float   CanvasWidth, CanvasHeight;  // viewport in units

    QMatrix4x4	projectionMatrix; // projection
    QMatrix4x4	modelMatrix; // model view

    QVector3D ScreenUp;
    QVector3D ScreenRight;
    QVector3D ScreenUpRight;
    QVector3D ScreenDownRight;

    ShaderPtr getShader() const;
    void setShader(const ShaderPtr &value);

private:
    float	clipHalfX, clipHalfZ;
    ShaderPtr   shader;
};

typedef Camera* CameraPtr;

#endif
