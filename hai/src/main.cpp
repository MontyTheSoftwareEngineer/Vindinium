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

  QString keyFilePath;
  int     keyFileOptionIndex = args.indexOf("--keyFilePath");

  if (keyFileOptionIndex != -1 && keyFileOptionIndex + 1 < args.size())
  {
    keyFilePath = args.at(keyFileOptionIndex + 1);
    qDebug() << "Key file location: " << keyFilePath;
  }
  else
  {
    qErrnoWarning(1, "input location to key file path with --keyFilePath");
    return(-1);
  }

  GameManager gameMan(nullptr, keyFilePath, "http://10.23.78.17:9000");

  return(a.exec());
}
