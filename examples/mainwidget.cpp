#include "mainwidget.h"
#include <QMouseEvent>
#include <math.h>
#include <QMatrix4x4>
#include "Core.h"
#include "Graphics.h"
#include "InputTracker.h"
//#include "Ogl.h"


MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent)
  , firstTime(true)
{
    //== Disable VSync, get more than 60FPS
    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setSwapInterval(0);
    QSurfaceFormat::setDefaultFormat(format);
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture and the buffers.
    makeCurrent();
    doneCurrent();
}

void MainWidget::closeEvent(QCloseEvent *event)
{
    Graphics::DestroyAll();
}

void MainWidget::initializeGL()
{
    this->setAttribute(Qt::WA_AcceptTouchEvents);

    ogl.initializeOpenGLFunctions();
    ogl.glClearColor(0, 0, 0, 1);
    ogl.glEnable(GL_DEPTH_TEST);
    ogl.glDisable(GL_CULL_FACE);

    Graphics::DPI.Update();

    if (!Graphics::Init())
        close();

    //QString fontPath = ":/fonts/pipe48.json";
    //UI::Font.LoadFont("Pipe", fontPath);

    Core::Random.ReSeed( time(0) );
    Core::Clock.ResetTimer();
}

void MainWidget::InitViews()
{

}

void MainWidget::resizeGL(int w, int h)
{
    Graphics::Screen.SetHighPoint(w,h);
    Graphics::DPI.Update();

    //if (!!mainView)         mainView->Resize(w,h);
}

void MainWidget::paintGL()
{
    if (firstTime)
    {
        InitViews();
        firstTime = false;
    }

    //ButtonManager::Instance().ExecuteRemovals();
    Core::Clock.UpdateTimer();
    float frameDt = Core::Clock.Ellapsed;
    if (frameDt>0.5f)   frameDt = 0.5f;

    Core::CoreDelegates.Process();
    //Core::CoreEvents.Process();

//    if (activeView)
//    {
//        activeView->Update( frameDt );
//        ogl.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        activeView->Render();
//    }
    update();
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button()==Qt::LeftButton)
    {
        QVector2D invpos(e->localPos().x(), Graphics::Screen.Height() - e->localPos().y());
        //ButtonManager::Instance().TapBeginHandler(123456, invpos);

        //QVector2D pos(e->localPos().x(), e->localPos().y());
        InputTracker::Instance().feedTapBegin( invpos );
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent *e)
{
    // Note that the returned value is always Qt::NoButton for mouse move events.
    // for mouseMoveEvent you should use buttons method.
    if (e->buttons()==Qt::LeftButton)
    {
        QVector2D invpos(e->localPos().x(), Graphics::Screen.Height() - e->localPos().y());
        //ButtonManager::Instance().TapMoveHandler(123456, invpos);

        //QVector2D pos(e->localPos().x(), e->localPos().y());
        InputTracker::Instance().feedTapMove( invpos );
    }
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button()==Qt::LeftButton)
    {
        QVector2D invpos(e->localPos().x(), Graphics::Screen.Height() - e->localPos().y());
        //ButtonManager::Instance().TapEndHandler(123456, invpos);

        //QVector2D pos(e->localPos().x(), e->localPos().y());
        InputTracker::Instance().feedTapEnd( invpos );
    }
}


static unsigned int someSeed = 1;
void MainWidget::keyReleaseEvent(QKeyEvent *ev)
{
    switch(ev->key())
    {
    case Qt::Key_Escape :
    case Qt::Key_Back :
        ev->accept();
        emit exitGame();
        break;

    case Qt::Key_Left:        break;
    case Qt::Key_Right:       break;
    case Qt::Key_Space:       break;
    }
}

bool MainWidget::event(QEvent *event)
{
    QEvent::Type eventType = event->type();

    //qDebug() << "Event type : " << eventType;

    if (eventType==QEvent::UpdateRequest || eventType==QEvent::Paint)
    {
        return QWidget::event(event);
    }

    return QWidget::event(event);
}

void MainWidget::playButtonClicked()
{
    //mainView->DisableButtons();

}

void MainWidget::quitButtonClicked()
{
    emit exitGame();
}
