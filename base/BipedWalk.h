#ifndef _BIPEDWALK_H_
#define _BIPEDWALK_H_
#include "Hermite.h"
#include <QMatrix4x4>

enum WalkState { StandIdle,	Moving,	Stopping };

enum Side	{ Left=0, Right=1, None=2 };


class BipedWalk
{
public:
	BipedWalk();
	virtual ~BipedWalk();

	void	Setup(float width, float height, float stride, float duration);

    void	StandAt(QVector3D pos);
	void	TriggerStep();
	void	Stop();
	void	SetDirection(float dir);
	void	ChangeDirection(float dir);

	void	Update(float dt);

	WalkState	state;

    QVector3D	feet[2];
    QVector3D	body;
	float	direction;

private:
	Side	movingSide;
	Side	idleSide;
    QVector3D	worldTranslation;
    QMatrix4x4	rotationMatrix;
	float	zOffset;
	float	height;
	float	width;
	
	float	stride, currentStride;
	float	t;
	float	duration;

	Hermite* footHeightCurve;
	bool	mustStop;

	void	RefreshMoving();
	void	RefreshDependants();
	void	UpdateMovingFoot(float weight);
};

#endif
