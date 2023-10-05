/******************************************************************************
 *
 * @file gamemanager.cpp
 *
 * @brief GameManager - Main entry point/manager for game.
 *
 * @author              Hai Pham
 *
 */
#include "gamemanager.h"

#include <QUrlQuery>
#include <QFile>

#include "src/RosettaStone/jsonparser.h"
#include "src/Cartographer/cartographer.h"

static const QString TRAINING_API = "/api/training";
static const QString ARENA_API    = "/api/arena";

GameManager::GameManager(QObject *parent, const QString& keyFilePath, const QString& serverURL)
  : QObject{parent}
  , m_apiKey(QString())
  , m_currentGameID(QString())
  , m_currentPlayUrl(QString())
{
  readAPIKey(keyFilePath);

  m_serverURL = serverURL;
  m_postMan   = new PostMan(this);
  connect(m_postMan, &PostMan::newResponseFromServer, this, &GameManager::newPostManResponse);

  m_cartMan = new Cartographer(this);
  connect(m_cartMan, &Cartographer::mapUpdated, this, &GameManager::newMapFromCartographer);
}

void GameManager::startNewGame(MegaBlocks::GAME_MODE mode)
{
  m_currentGameID.clear();
  QString serverUrl = m_serverURL + (mode == MegaBlocks::TRAINING ? TRAINING_API : ARENA_API);

  if (m_apiKey.isEmpty())
  {
    qErrnoWarning(2, "Could not read API Key!");
  }

  QUrlQuery postData;
  postData.addQueryItem("key", m_apiKey);

  m_postMan->makeNetworkRequest(serverUrl, postData);
}

void GameManager::newPostManResponse(const QString&response)
{
  JSONParser           jParser;
  MegaBlocks::GameData parsedGameData = jParser.parseJSONString(response);

  m_currentPlayUrl = parsedGameData.m_playUrl;

  m_cartMan->parseMap(parsedGameData.m_mapSize, parsedGameData.m_gameMap);

  emit gameMapUpdated(parsedGameData.m_mapSize, m_cartMan->getCurrentMap());

//  if (parsedGameData.m_currentTurnCount < parsedGameData.m_totalTurns)
//  {
//    qDebug() << parsedGameData.m_mapSize;
//    qDebug() << "Turn " << parsedGameData.m_currentTurnCount << " of " << parsedGameData.m_totalTurns;
//    QUrl      playURL = parsedGameData.m_playUrl;
//    QUrlQuery postData;
//    postData.addQueryItem("key", m_apiKey);
//    postData.addQueryItem("dir", "North");

//    m_postMan->makeNetworkRequest(playURL, postData);
//  }
//  else
//  {
//    qDebug() << "Game Over!";
//    qDebug() << parsedGameData.m_viewUrl;
//  }
}

void GameManager::setNewDestination(const int index)
{
  qDebug() << m_cartMan->setDestinationAndGetMove(index);
}

void GameManager::testMap(const QString&inputMap)
{
  m_cartMan->parseMap(28, inputMap);

  emit gameMapUpdated(28, m_cartMan->getCurrentMap());
}

void GameManager::newMapFromCartographer()
{
  emit gameMapUpdated(m_cartMan->mapCacheSize(), m_cartMan->getCurrentMap());
}

void GameManager::readAPIKey(const QString&keyFilePath)
{
  QFile keyFile(keyFilePath);

  if (keyFile.exists() && keyFile.open(QIODevice::ReadOnly))
  {
    QString apiKey = keyFile.readAll();
    qDebug() << "API Key: " << apiKey;
    m_apiKey = apiKey;
  }
}
