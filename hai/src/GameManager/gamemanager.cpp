#include "gamemanager.h"

#include <QUrlQuery>

static const QString TRAINING_API = "/api/training";
static const QString ARENA_API    = "/api/arena";

GameManager::GameManager(QObject *parent, const QString& serverURL)
  : QObject{parent}
  , m_currentGameID(QString())
{
  m_serverURL = serverURL;
  m_postMan   = new PostMan;
  connect(m_postMan, &PostMan::newResponseFromServer, this, &GameManager::newPostManResponse);
}

void GameManager::startNewGame(GAME_MODE mode)
{
  m_currentGameID.clear();
  QString serverUrl = m_serverURL + (mode == TRAINING ? TRAINING_API : ARENA_API);

  QUrlQuery postData;

  m_postMan->makeNetworkRequest(serverUrl, postData);
}

void GameManager::newPostManResponse(const QString&response)
{
}
