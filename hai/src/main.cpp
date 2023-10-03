#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>
#include <iostream>

#include "src/GameManager/gamemanager.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  QStringList args = a.arguments();

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

  GameManager gameMan(nullptr, keyFilePath, serverUrl);
  gameMan.startNewGame(GameManager::TRAINING);

  return(a.exec());
}
