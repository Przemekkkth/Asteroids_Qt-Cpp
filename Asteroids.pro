greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    animation.cpp \
    asteroid.cpp \
    bullet.cpp \
    entity.cpp \
    game.cpp \
    gamescene.cpp \
    main.cpp \
    player.cpp \
    view.cpp

HEADERS += \
    animation.h \
    asteroid.h \
    bullet.h \
    entity.h \
    game.h \
    gamescene.h \
    player.h \
    view.h

RESOURCES += \
    resource.qrc
