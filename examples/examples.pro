
TEMPLATE = app
TARGET = Examples

QT += core gui widgets multimedia

INCLUDEPATH += $$PWD/../graphics
INCLUDEPATH += $$PWD/../user-interface
INCLUDEPATH += $$PWD/../components

include($$PWD/../graphics/graphics.pri)
include($$PWD/../user-interface/user-interface.pri)
include($$PWD/../components/components.pri)

SOURCES += \
    InputTracker.cpp \
    main.cpp \
    mainwidget.cpp \
    UIFactory.cpp \
    SpritesFromAtlas.cpp

HEADERS += \
    InputTracker.h \
    mainwidget.h \
    UIFactory.h \
    ExampleBase.h \
    SpritesFromAtlas.h

RESOURCES += \
    assets/textures.qrc \
    assets/fonts.qrc

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

