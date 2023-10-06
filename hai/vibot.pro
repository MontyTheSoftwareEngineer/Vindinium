QT += quick quickcontrols2 qml network core gui \
    widgets

CONFIG += c++17 qtquickcompiler console
QTQUICK_COMPILER_SKIPPED_RESOURCES += qml.qrc

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/BotModels/aggroscallywag.cpp \
        src/BotModels/hunhun.cpp \
        src/BotModels/ibotmodel.cpp \
        src/BotModels/marvbot.cpp \
        src/BotModels/randobotmodel.cpp \
        src/BotModels/scallywag.cpp \
        src/Cartographer/cartographer.cpp \
        src/Cartographer/marsrover.cpp \
        src/GameManager/gamemanager.cpp \
        src/Network/postman.cpp \
        src/RosettaStone/jsonparser.cpp \
        src/Statistician/statistician.cpp \
        src/UIHelper/uihelper.cpp \
        src/main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
  src/BotModels/aggroscallywag.h \
  src/BotModels/hunhun.h \
  src/BotModels/ibotmodel.h \
  src/BotModels/marvbot.h \
  src/BotModels/randobotmodel.h \
  src/BotModels/scallywag.h \
  src/Cartographer/cartographer.h \
  src/Cartographer/marsrover.h \
  src/GameManager/gamemanager.h \
  src/MegaBlocks/megablocks.h \
  src/Network/postman.h \
  src/RosettaStone/jsonparser.h \
  src/Statistician/statistician.h \
  src/UIHelper/uihelper.h

RESOURCES += \
  qml.qrc
