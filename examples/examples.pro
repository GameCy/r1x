
TEMPLATE = app
TARGET = R1X-Examples

QT += core gui widgets multimedia

INCLUDEPATH += $$PWD/../audio
INCLUDEPATH += $$PWD/../graphics
INCLUDEPATH += $$PWD/../user-interface
INCLUDEPATH += $$PWD/../components

include($$PWD/../audio/audio.pri)
include($$PWD/../graphics/graphics.pri)
include($$PWD/../user-interface/user-interface.pri)
include($$PWD/../components/components.pri)

SOURCES += \
    DragToTarget.cpp \
    InputTracker.cpp \
    PlaySoundFx.cpp \
    main.cpp \
    mainwidget.cpp \
    UIFactory.cpp \
    SpritesFromAtlas.cpp \
    UserInterface.cpp \
    Viewd3dModels.cpp \
    SpriteParticleFade.cpp \
    TiledMap.cpp

HEADERS += \
    DragToTarget.h \
    InputTracker.h \
    PlaySoundFx.h \
    mainwidget.h \
    UIFactory.h \
    ExampleBase.h \
    SpritesFromAtlas.h \
    UserInterface.h \
    Viewd3dModels.h \
    SpriteParticleFade.h \
    TiledMap.h

RESOURCES += \
    assets/Sounds.qrc \
    assets/textures.qrc \
    assets/fonts.qrc \
    assets/models.qrc \
    assets/tiledmaps.qrc

# add files to  APK
DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

