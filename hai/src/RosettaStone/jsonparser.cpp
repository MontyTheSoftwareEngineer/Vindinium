#include "jsonparser.h"
#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QJsonArray>

JSONParser::JSONParser(QObject *parent)
  : QObject{parent}
{
}

MegaBlocks::GameData JSONParser::parseJSONString(const QString&jsonString)
{
  qDebug() << jsonString;
  MegaBlocks::GameData parsedData;

  QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());

  QJsonObject jsonObj = jsonDoc.object();

  parsedData.m_gameID           = jsonObj.value("game").toObject().value("id").toString();
  parsedData.m_playUrl          = jsonObj.value("playUrl").toString();
  parsedData.m_currentTurnCount = jsonObj.value("game").toObject().value("turn").toInt();
  parsedData.m_totalTurns       = jsonObj.value("game").toObject().value("maxTurns").toInt();

  parsedData.m_viewUrl     = jsonObj.value("viewUrl").toString();
  parsedData.m_mapSize     = jsonObj.value("game").toObject().value("board").toObject().value("size").toInt();
  parsedData.m_gameMap     = jsonObj.value("game").toObject().value("board").toObject().value("tiles").toString();
  parsedData.m_ownPlayerID = jsonObj.value("hero").toObject().value("id").toInt();

  QMap <int, MegaBlocks::Player> playerMap;

  QJsonArray heroArray = jsonObj.value("heroes").toArray();
  for (int i = 0; i < heroArray.size(); i++)
  {
    MegaBlocks::Player newPlayer;
    newPlayer.id        = heroArray.at(i).toObject().value("id").toInt();
    newPlayer.name      = heroArray.at(i).toObject().value("name").toString();
    newPlayer.health    = heroArray.at(i).toObject().value("health").toInt();
    newPlayer.gold      = heroArray.at(i).toObject().value("gold").toInt();
    newPlayer.mineCount = heroArray.at(i).toObject().value("gold").toInt();

    playerMap[newPlayer.id] = newPlayer;
  }
  parsedData.m_playerMap = playerMap;

  qDebug() << "Game URL: " << parsedData.m_viewUrl;

  return(parsedData);
}
