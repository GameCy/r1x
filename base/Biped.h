#ifndef _BIPED_H_
#define _BIPED_H_
#include <string>
#include "BipedWalk.h"
#include "model.h"
#include "Camera.h"

class Biped: public Model
{
public:
    Biped();
    virtual ~Biped();

    bool LoadFile(QString& Filename);

    virtual void Render(Camera &camera);
    virtual void Update(float dt);
    virtual bool IsFinished();

    virtual QVector3D GetPos();
    virtual void	 SetPos(QVector3D pos);

    void	 SetDirection(float dir);

    BipedWalk	walk;

private:

    int	leftFoot;
    int	rightFoot;
};

#endif
