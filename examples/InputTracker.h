#ifndef INPUTTRACKER_H
#define INPUTTRACKER_H
#include <QObject>
#include <QVector2D>
#include <QVector3D>

class InputTracker : public QObject
{
    Q_OBJECT
public:
    static InputTracker& Instance();

public slots:
    void    feedTapBegin(QVector2D pos);
    void    feedTapMove(QVector2D pos);
    void    feedTapEnd(QVector2D pos);

signals:
    void    TapBegin(QVector2D pos);
    void    TapMove(QVector2D pos);
    void    TapEnd(QVector2D pos);

private:
    InputTracker();
    static InputTracker* instance;
};

#endif // INPUTTRACKER_H
