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
#include "src/BotModels/scallywag.h"
#include "src/BotModels/aggroscallywag.h"
#include "src/BotModels/hunhun.h"
#include "src/BotModels/randobotmodel.h"
#include "src/BotModels/marvbot.h"

static const QString TRAINING_API = "/api/training";
static const QString ARENA_API    = "/api/arena";

GameManager::GameManager(QObject *parent, const QString& keyFilePath, const QString& serverURL, const QString& botModel)
  : QObject{parent}
  , m_apiKey(QString())
  , m_currentGameID(QString())
  , m_currentPlayUrl(QString())
  , m_state(QString())
{
  readAPIKey(keyFilePath);

  m_serverURL = serverURL;
  m_postMan   = new PostMan(this);
  connect(m_postMan, &PostMan::newResponseFromServer, this, &GameManager::newPostManResponse);
  connect(m_postMan, &PostMan::errorFromServer, this, &GameManager::errorFromPostMan);

  m_cartMan = new Cartographer(this);
  connect(m_cartMan, &Cartographer::mapUpdated, this, &GameManager::newMapFromCartographer);

  if (botModel == "ScallyWag")
  {
    qDebug() << "Using bot model ScallyWag";
    m_botModel = new ScallyWag(this);
  }
  else if (botModel == "MarvBot")
  {
    qDebug() << "Using bot model MarvBot";
    m_botModel = new MarvBot(this);
  }
  else if (botModel == "AggroWag")
  {
    qDebug() << "Using bot model AggroWag";
    m_botModel = new AggroScallyWag(this);
  }
  else if (botModel == "HunHun")
  {
    qDebug() << "Using bot model HunHun";
    m_botModel = new HunHun(this);
  }
  else if (botModel == "Random")
  {
    qDebug() << "Using bot model Random";
    m_botModel = new RandoBotModel(this);
  }
  else
  {
    qErrnoWarning("Invalid bot model!");
  }
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
  JSONParser jParser;

  m_cachedGameData = jParser.parseJSONString(response);

  m_currentPlayUrl = m_cachedGameData.m_playUrl;

  m_cartMan->parseMap(m_cachedGameData);

  emit gameMapUpdated(m_cachedGameData.m_mapSize, m_cachedGameData.m_cachedMap);

  if (m_cachedGameData.m_playerHealth >= 80)
  {
    m_state = "";
  }

  if (m_cachedGameData.m_currentTurnCount < m_cachedGameData.m_totalTurns)
  {
    QString nextMove = m_botModel->getNextMove(m_cachedGameData);


    //qDebug() << m_cachedGameData.m_mapSize;
    qDebug() << "Turn " << m_cachedGameData.m_currentTurnCount << " of " << m_cachedGameData.m_totalTurns;
    QUrl      playURL = m_cachedGameData.m_playUrl;
    QUrlQuery postData;
    postData.addQueryItem("key", m_apiKey);
    postData.addQueryItem("dir", nextMove);

    m_postMan->makeNetworkRequest(playURL, postData);
  }
  else
  {
    qDebug() << "Game Over!";
    qDebug() << m_cachedGameData.m_viewUrl;
    startNewGame(MegaBlocks::ARENA);
  }
}

void GameManager::setNewDestination(const int index)
{
  qDebug() << m_cartMan->setDestinationAndGetMove(m_cachedGameData, index);
}

void GameManager::newMapFromCartographer()
{
  emit gameMapUpdated(m_cachedGameData.m_mapSize, m_cachedGameData.m_cachedMap);
}

void GameManager::errorFromPostMan()
{
  startNewGame(MegaBlocks::ARENA);
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
