/******************************************************************************
 *
 * @file gamemanager.h
 *
 * @brief GameManager - Main entry point/manager for game.
 *
 * @author              Hai Pham
 *
 */

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "src/Network/postman.h"

class GameManager : public QObject
{
  Q_OBJECT
public:


  /**
   * @enum GAME_MODE
   * @brief The GAME_MODE enum defines the different game types available.
   */
  enum GAME_MODE
  {
    TRAINING = 0,
    ARENA
  };

  Q_ENUM(GAME_MODE)

  /**
   * @brief Default constructor.
   * @param parent The parent QObject for the GameManager.
   * @param keyFilePath QString containing location for apiKey.
   * @param serverURL QString containing URL for game server.
   */
  explicit GameManager(QObject *parent, const QString&keyFilePath, const QString& serverURL);

public slots:


  /**
   * @brief Starts a new game.
   * @param mode GAME_MODE for type of game (training or arena).
   */
  void startNewGame(GAME_MODE mode);

  /**
   * @brief Slot to handle new network data from PostMan.
   * @param reponse QString containing network reply from PostMan.
   */
  void newPostManResponse(const QString& response);

signals:

private:

  /**
   * @brief reads API Key from file.
   * @param keyFilePath QString containing path to txt file with apiKey.
   */
  void readAPIKey(const QString& keyFilePath);

  PostMan *m_postMan;

  QString m_apiKey;
  QString m_serverURL;
  QString m_currentGameID;
  QString m_currentPlayUrl;
};

#endif // GAMEMANAGER_H
