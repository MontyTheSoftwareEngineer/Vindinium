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

  explicit GameManager(QObject *parent = nullptr, const QString& serverURL = QString());

public slots:
  void startNewGame(GAME_MODE mode);
  void newPostManResponse(const QString& response);

signals:

private:
  PostMan *m_postMan;

  QString m_serverURL;
  QString m_currentGameID;
};

#endif // GAMEMANAGER_H
