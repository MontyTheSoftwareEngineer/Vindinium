#include "jsonparser.h"
#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>

JSONParser::JSONParser(QObject *parent)
  : QObject{parent}
{
}

JSONParser::GameData JSONParser::parseJSONString(const QString&jsonString)
{
  GameData parsedData;

  QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());

  QJsonObject jsonObj = jsonDoc.object();

  parsedData.m_gameID  = jsonObj.value("game").toObject().value("id").toString();
  parsedData.m_playUrl = jsonObj.value("playUrl").toString();
  parsedData.m_mapSize = jsonObj.value("game").toObject().value("board").toObject().value("size").toInt();
  parsedData.m_gameMap = jsonObj.value("game").toObject().value("board").toObject().value("tiles").toString();

  return(parsedData);
}