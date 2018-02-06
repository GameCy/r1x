#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QOpenGLWidget>
#include "ExampleBase.h"
#include "UserInterface.h"

class MainWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    bool firstTime;

protected:
    void keyReleaseEvent(QKeyEvent* ev);
    bool event(QEvent *event) Q_DECL_OVERRIDE; // to process QTouchEvent

    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

protected slots:
    void nextButtonClicked();
    void previousButtonClicked();
    void quitButtonClicked();
signals:
    void exitGame();
private:
    ExampleBase*    example;
    UserInterface*  userInterface;

    int exampleIndex;

    void InstantiateExample(int idxChange);
};

#endif // MAINWIDGET_H
