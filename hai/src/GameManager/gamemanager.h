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
#include "src/MegaBlocks/megablocks.h"
#include "src/Network/postman.h"
#include "src/Cartographer/cartographer.h"
#include "src/BotModels/ibotmodel.h"


class GameManager : public QObject
{
  Q_OBJECT
public:

  /**
   * @brief Default constructor.
   * @param parent The parent QObject for the GameManager.
   * @param keyFilePath QString containing location for apiKey.
   * @param serverURL QString containing URL for game server.
   */
  explicit GameManager(QObject *parent, const QString&keyFilePath, const QString& serverURL, const QString& botModel);

public slots:


  /**
   * @brief Starts a new game.
   * @param mode GAME_MODE for type of game (training or arena).
   */
  void startNewGame(MegaBlocks::GAME_MODE mode);

  /**
   * @brief Slot to handle new network data from PostMan.
   * @param reponse QString containing network reply from PostMan.
   */
  void newPostManResponse(const QString& response);

  void setNewDestination(const int index);

  void newMapFromCartographer();

  void errorFromPostMan();

signals:

  /**
   * @brief Signal indicating map size changed.
   * @param mapSize int of new map size.
   */
  void gameMapUpdated(const int mapSize, const QList <MegaBlocks::TILE_TYPE>& newMap);

private:

  /**
   * @brief reads API Key from file.
   * @param keyFilePath QString containing path to txt file with apiKey.
   */
  void readAPIKey(const QString& keyFilePath);

  PostMan *m_postMan;
  Cartographer *m_cartMan;

  QString m_apiKey;
  QString m_serverURL;
  QString m_currentGameID;
  QString m_currentPlayUrl;

  QString m_state;

  MegaBlocks::GameData m_cachedGameData;

  IBotModel *m_botModel;
};

#endif // GAMEMANAGER_H
