#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>

#include "src/GameManager/gamemanager.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  GameManager gameMan(nullptr, "http://10.23.78.17:9000");

  return(a.exec());
}
