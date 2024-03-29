#include "mainwidget.h"
#include <QMouseEvent>
#include <math.h>
#include <QMatrix4x4>
#include "Core.h"
#include "Ogl.h"
#include "Graphics.h"
#include "Temporal.h"
#include "UI.h"
#include "InputAreaManager.h"
#include "InputTracker.h"
#include "DragDrop.h"

// ** include examples **
#include "SpritesFromAtlas.h"
#include "Viewd3dModels.h"
#include "SpriteParticleFade.h"
#include "TiledMap.h"
#include "DragToTarget.h"
#include "PlaySoundFx.h"
//#include "CadTest.h"

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent)
  , firstTime(true)
  , example(nullptr)
  , userInterface(nullptr)
  , exampleIndex(0)
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
    TemporalPool::DestroyAll();
    Graphics::DestroyAll();
    UI::Fonts.ClearAll();
}

void MainWidget::initializeGL()
{
    this->setAttribute(Qt::WA_AcceptTouchEvents);

    ogl.initializeOpenGLFunctions();
    ogl.glClearColor(0.f, 0.f, 0.f, 1);
    ogl.glEnable(GL_DEPTH_TEST);
    ogl.glDisable(GL_CULL_FACE);

    //Graphics::DPI.Update( Graphics::Screen );

    if (!Graphics::Init())
        close();

    //UI::Fonts.LoadFont("Pipe", ":/fonts/pipe.json");
    UI::Fonts.LoadFont("Pipe48", ":/fonts/pipe48.json");

    Core::Random.ReSeed( time(nullptr) );
    Core::Clock.ResetTimer();

    connect(this, &MainWidget::exitGame, this, &MainWidget::close);
}


void MainWidget::resizeGL(int w, int h)
{
    Graphics::Screen.SetHighPoint(w,h);
    Graphics::DPI.Update( Graphics::Screen );

    if (userInterface)  userInterface->Resize( Graphics::Screen );
    if (example)        example->Resize( Graphics::Screen );
}


void MainWidget::paintGL()
{
    if (firstTime)
    {
        userInterface = new UserInterface();
        userInterface->Resize( Graphics::Screen );
        connect(userInterface->buttonNext, &Button::Clicked, this, &MainWidget::nextButtonClicked);
        connect(userInterface->buttonPrev, &Button::Clicked, this, &MainWidget::previousButtonClicked);
        InstantiateExample(0);
        example->Resize( Graphics::Screen );
        firstTime = false;
        return;
    }

    InputAreaManager::Instance().ExecuteRemovals();
    Core::Clock.UpdateTimer();
    float frameDt = Core::Clock.Ellapsed;
    if (frameDt>0.5f)   frameDt = 0.5f;

    Core::CoreDelegates.Process();
    //Core::CoreEvents.Process();
    TemporalPool::Update(frameDt);

    ogl.glClearColor(0.f, 0.f, 0.f, 1);
    ogl.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (example)
        example->Render();
    userInterface->Render();

    update();
}


void MainWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button()==Qt::LeftButton)
    {
        QVector2D invpos(e->position().x(), Graphics::Screen.Height() - e->position().y());
        InputAreaManager::Instance().TapBeginHandler(123456, invpos);

        //QVector2D pos(e->localPos().x(), e->localPos().y());
        InputTracker::Instance().feedTapBegin( invpos );

        DragDropManager::Instance()->InspectDraggables(Grab, 123456, invpos);
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent *e)
{
    // Note that the returned value is always Qt::NoButton for mouse move events.
    // for mouseMoveEvent you should use buttons method.
    if (e->buttons()==Qt::LeftButton)
    {
        QVector2D invpos(e->position().x(), Graphics::Screen.Height() - e->position().y());
        InputAreaManager::Instance().TapMoveHandler(123456, invpos);

        //QVector2D pos(e->localPos().x(), e->localPos().y());
        InputTracker::Instance().feedTapMove( invpos );

        DragDropManager::Instance()->InspectDraggables(Move, 123456, invpos);
    }
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button()==Qt::LeftButton)
    {
        QVector2D invpos(e->position().x(), Graphics::Screen.Height() - e->position().y());
        InputAreaManager::Instance().TapEndHandler(123456, invpos);

        //QVector2D pos(e->localPos().x(), e->localPos().y());
        InputTracker::Instance().feedTapEnd( invpos );

        DragDropManager::Instance()->InspectDraggables(Release, 123456, invpos);
    }
}

void MainWidget::keyReleaseEvent(QKeyEvent *ev)
{
    switch(ev->key())
    {
    case Qt::Key_Escape :
    case Qt::Key_Back :    { ev->accept();    emit exitGame(); }
        break;
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

void MainWidget::nextButtonClicked()
{
    InstantiateExample(+1);
}

void MainWidget::previousButtonClicked()
{
    InstantiateExample(-1);
}

void MainWidget::quitButtonClicked()
{
    emit exitGame();
}

void MainWidget::InstantiateExample(int idxChange)
{
    const int maxExampleIndex = 6;
    exampleIndex += idxChange;
    if (exampleIndex<0) exampleIndex = maxExampleIndex;
    if (exampleIndex>maxExampleIndex) exampleIndex = 0;
    if (example)
    {
        example->DeleteLater();
        example = nullptr;
    }
    switch(exampleIndex)
    {
        case 0 : example = new SpriteParticleFade(); break;
        case 1 : example = new SpritesFromAtlas();  break;
        case 2 : example = new Viewd3DModels();  break;
        case 3 : example = new TiledMap(); break;
        case 4 : example = new DragToTarget(); break;
        case 5 : example = new PlaySoundFx(); break;
        //case 6 : example = new CadTest(); break;
    }
}

