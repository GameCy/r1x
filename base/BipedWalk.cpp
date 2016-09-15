#include "BipedWalk.h"
#include <math.h>

#define NumControlPoints 6
#define NumCurveSamples 50
#define MaxH 0.2f
float curve_control_points[NumControlPoints*3] = { 0,0,0, 0,0.3f*MaxH,0.2f,  0.0,MaxH,0.4f,  0,0.9f*MaxH,0.6f, 0,0.7f*MaxH,0.8f, 0,0,1.0f };
//float curve_control_points[NumControlPoints*3] = { 0,0,0,  0,0.99f,0.5f, 0,0,1.0f };


BipedWalk::BipedWalk()
{
	footHeightCurve = new Hermite;
	footHeightCurve->init(1.0, NumCurveSamples, NumControlPoints, curve_control_points);
    StandAt( QVector3D(0,0,0));
	SetDirection(0.0f);
}

BipedWalk::~BipedWalk()
{
	delete footHeightCurve;
}

void BipedWalk::Setup(float width, float height, float stride, float duration)
{
	this->width = width;
	this->height = height;
	this->stride = stride;
	this->duration = duration;
}

void BipedWalk::StandAt(QVector3D pos)
{
	state = StandIdle;
	idleSide = movingSide = Left;

    feet[Left] = pos + rotationMatrix*QVector3D( -width/2.0f,0,0);
    feet[Right] = pos + rotationMatrix*QVector3D( width/2.0f,0,0);
		
	RefreshDependants();

	t=0;
	zOffset=0;
	mustStop=false;
}

void BipedWalk::Stop()
{
	if (state!=StandIdle)	mustStop = true;
}

void	BipedWalk::SetDirection(float dir)
{
	direction = dir;
    rotationMatrix.setToIdentity();
    rotationMatrix.rotate( QQuaternion::fromAxisAndAngle(0,1,0, direction) );

	if (state==StandIdle)	StandAt( (feet[0]+feet[1])/2.0f );
	else					RefreshMoving();
}

void	BipedWalk::ChangeDirection(float dir)
{
	SetDirection(direction+dir);
}

void	BipedWalk::RefreshDependants()
{
	body = (feet[0]+feet[1])/2.0f;
    body.setY( height+ 0.2f*body.y() );
}

void	BipedWalk::UpdateMovingFoot(float weight)
{
    QVector3D movingFoot;
    if (movingSide==Left)	movingFoot = QVector3D(-width, 0, zOffset);
    else					movingFoot = QVector3D( width, 0, zOffset);
    QVector3D v = footHeightCurve->GetPoint(weight);
	movingFoot += v*currentStride;

    feet[movingSide] = worldTranslation + rotationMatrix*movingFoot;
}


void	BipedWalk::RefreshMoving()
{
	float weight = t / duration;
	if (weight>1.0f)	weight=1.0f;

	UpdateMovingFoot(weight);
	feet[idleSide] = worldTranslation;

	RefreshDependants();
}


void BipedWalk::TriggerStep()
{
	// swap active foot
	idleSide = movingSide;
	movingSide = (idleSide==Left)? Right : Left;
	
	if (state==StandIdle)
	{
		state = Moving;
		currentStride = stride/2.0f;
		zOffset = 0;
		mustStop=false;
	}
	else if ((state==Moving))
	{
		if (mustStop)
		{
			currentStride = stride/2.0f;
			state = Stopping;
		}
		else	currentStride = stride;
		zOffset = -stride/2.0f;
	}
	else if (state==Stopping)
	{
		state = StandIdle;
		zOffset = 0;
	}
	
	t=0;
	worldTranslation = feet[idleSide]; // idle foot is planted on ground and not moving
}

void	BipedWalk::Update(float dt)
{
	if (state==StandIdle)	return;

	t +=dt;
	if (t>duration)		
	{
		UpdateMovingFoot(1.0f);
		TriggerStep();
	}

	if (state!=StandIdle)	RefreshMoving();
}


