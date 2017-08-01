#include "Camera.h"
#include <math.h>


Camera::Camera(ShaderPtr shader)
    : shader(0)
{
	FieldOfView = default_fov;
	Near = default_near;
	Far = default_far;
	Aspect = default_aspect;
    UpVector = QVector3D(0, 1, 0);
}

Camera::~Camera()
{
}

void    Camera::Setup(int width, int height, float nearZ, float farZ, float fov, float aspect)
{
    PixelWidth = width;
    PixelHeight = height;
    FieldOfView = fov;
    Aspect = aspect;
    Near = nearZ;
    Far = farZ;

    CanvasHeight = 2.0;//*tan(FieldOfView * M_PI / 360.0) * Near;
    CanvasWidth = 2.0; //CanvasHeight*Aspect;
    //CanvasWidth = (PixelWidth/PixelHeight);
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(FieldOfView, Aspect, Near, Far);
}

// vectors used when particles need to face the screen
void	Camera::UpdateViewVectors()
{
    QMatrix4x4 inverse;
    inverse.lookAt(Position, LookAt, UpVector );
    inverse = inverse.inverted();

    // calculate dx dy dz based on camera orientation
    ScreenRight = inverse.column(0).toVector3D().normalized();
    ScreenUp    = inverse.column(1).toVector3D().normalized();
    ScreenUpRight = ScreenRight + ScreenUp;
    ScreenDownRight = ScreenRight - ScreenUp;
}

ShaderPtr Camera::getShader() const
{
    return shader;
}

void Camera::setShader(const ShaderPtr &value)
{
    shader = value;
}

void	Camera::ResetPosition()
{
    modelMatrix.setToIdentity();
    modelMatrix.lookAt(Position, LookAt, UpVector );

    //phongShaders.setUniformValue("lightPos", modelMatrix*LightPos);
}

void	Camera::SetClippingAreaSize(float dx, float dz)
{
	clipHalfX = dx/2.0f;
	clipHalfZ = dz/2.0f;
}

bool	Camera::InVisibleArea(QVector3D pos)
{
    if ( (pos.x() < (LookAt.x()-clipHalfX)) ||
         (pos.x() > (LookAt.x()+clipHalfX)) ||
         (pos.z() < (LookAt.z()-clipHalfZ)) ||
         (pos.z() > (LookAt.z()+clipHalfZ))
		)
		return false;
	return true;
}

void    Camera::moveModel(QVector3D pos, QQuaternion rot, float scale)
{
    ResetPosition();
    modelMatrix.translate(pos);
    modelMatrix.rotate(rot);
    modelMatrix.scale( scale );

    if (shader)
        shader->UpdateMatrices(projectionMatrix, modelMatrix );
}


bool Camera::ScreenPointToGround(float tapX, float tapY, QVector3D& outPoint)
{
    // the vectors we need when camera is not moved
    QVector3D planeNormal(0,1,0);

    ResetPosition(); // ?? this not needed IF method called after cam has been reset
    QVector3D ray = mouseToGlobalCoords(tapX, tapY);

    float D = QVector3D::dotProduct(planeNormal, ray);
    float N = QVector3D::dotProduct(planeNormal, Position);
    if (fabs(D)<0.001)
        return false;
    float factor = -N/D;
    //if (factor<0)   return false;

    outPoint =   Position + factor*ray;
    return true;
}

QVector3D Camera::mouseToGlobalCoords(float x, float y)
{
    float px = (x/PixelWidth - 0.5f)*CanvasWidth;
    float py = (0.5f - y/PixelHeight)*CanvasHeight;

    return (projectionMatrix*modelMatrix).inverted()*QVector3D(px, py, Near);
}
