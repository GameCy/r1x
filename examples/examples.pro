
TEMPLATE = app
TARGET = Examples

QT += core gui widgets multimedia

INCLUDEPATH += base

include($$PWD/../base/base.pri)

SOURCES += \
    InputTracker.cpp \
    main.cpp \
    mainwidget.cpp \
    UIFactory.cpp

HEADERS += \
    InputTracker.h \
    mainwidget.h \
    UIFactory.h

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

