#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <iostream>

#include <QCoreApplication>

#include "src/GameManager/gamemanager.h"
#include "src/UIHelper/uihelper.h"

int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QApplication app(argc, argv);
  app.setOrganizationName("Hai");
  app.setOrganizationDomain("Pham");
  app.setApplicationName("vindiniumclient");

  QStringList args = app.arguments();

  /**
   * Set keyFilePath and serverUrl runtime arguments before running.
   * Projects > Run > Command Line Arguments
   * Example: --keyFilePath "C:/Millipore/vindiniumKey.txt" --serverUrl "http://10.23.78.17:9000"
   *
   **/
  QString keyFilePath;
  int     keyFileOptionIndex = args.indexOf("--keyFilePath");

  if (keyFileOptionIndex != -1 && keyFileOptionIndex + 1 < args.size())
  {
    keyFilePath = args.at(keyFileOptionIndex + 1);
    qDebug() << "Key file location: " << keyFilePath;
  }
  else
  {
    qErrnoWarning(-1, "Missing keyFilePath argument (--keyFilePath \"path/to/file.txt\")");
  }

  QString serverUrl;
  int     serverUrlOptionIndex = args.indexOf("--serverUrl");

  if (serverUrlOptionIndex != -1 && serverUrlOptionIndex + 1 < args.size())
  {
    serverUrl = args.at(serverUrlOptionIndex + 1);
    qDebug() << "Server Url: " << serverUrl;
  }
  else
  {
    qErrnoWarning(-1, "Missing serverUrl argument. (--serverUrl \"http://127.0.0.1:9000\")");
  }
  bool isQmlLoaded = false;

  //qmlRegisterUncreatableType <GameManager>("Vindinium", 1, 0, "GameManager", "Uncreatable");

  qmlRegisterType <UIHelper>("Vindinium", 1, 0, "UIHelper");
  QQmlApplicationEngine engine;

  GameManager gameMan(nullptr, keyFilePath, serverUrl);
  UIHelper    uiHelper;

  QObject::connect(&gameMan, &GameManager::gameMapUpdated, &uiHelper, &UIHelper::newMapAvailable);
  QObject::connect(&uiHelper, &UIHelper::newWayPoint, &gameMan, &GameManager::setNewDestination);

  //gameMan.testMap("####################$-    ####    $-########################################    $-####$-    ##########################################            ####################################$-####    ########    ####$-############################  ##  ##  ########  ##  ##  ########################$-##          ########          ##$-####################    ##    ####  ####  ####    ##    ##################          ##  @1  $-$-  @4  ##          ####################  []  $-##  ########  ##$-  []  ########################    ##      ########      ##    ########################  ##      ############      ##  ######################              ########              ####################  ######  ##$-########$-##  ######  ####################  ##        ############        ##  ####################  ##        ############        ##  ####################  ######  ##$-########$-##  ######  ####################              ########              ######################  ##      ############      ##  ########################    ##      ########      ##    ########################  []  $-##  ########  ##$-  []  ####################          ##  @2  $-$-  @3  ##          ##################    ##    ####  ####  ####    ##    ####################$-##          ########          ##$-########################  ##  ##  ########  ##  ##  ############################$-####    ########    ####$-####################################            ##########################################    $-####$-    ########################################$-    ####    $-####################");
  gameMan.startNewGame(MegaBlocks::TRAINING);

  QObject::connect(&uiHelper, &UIHelper::mapUpdate, [&]() {
    if (!isQmlLoaded)
    {
      qDebug() << "Loading QML for the first time";
      engine.rootContext()->setContextProperty("uiHelper", &uiHelper);
      engine.load(QUrl(QStringLiteral("qrc:/ui/ui/main.qml")));
      isQmlLoaded = true;     // Set the flag
    }
  });

  engine.rootContext()->setContextProperty("uiHelper", &uiHelper);

  engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));
  return(app.exec());
}
