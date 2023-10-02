#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "src/Network/postman.h"

class GameManager : public QObject
{
  Q_OBJECT
public:
  enum GAME_MODE
  {
    TRAINING = 0,
    ARENA
  };
  Q_ENUM(GAME_MODE)

  explicit GameManager(QObject *parent, const QString&keyFilePath, const QString& serverURL);

public slots:
  void startNewGame(GAME_MODE mode);
  void newPostManResponse(const QString& response);

signals:

private:
  void readAPIKey(const QString& keyFilePath);

  PostMan *m_postMan;

  QString m_apiKey;
  QString m_serverURL;
  QString m_currentGameID;
};

#endif // GAMEMANAGER_H
