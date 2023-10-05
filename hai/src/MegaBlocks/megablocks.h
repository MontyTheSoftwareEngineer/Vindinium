#ifndef MEGABLOCKS_H
#define MEGABLOCKS_H

#include <QObject>
#include <QMap>

class MegaBlocks : public QObject
{
  Q_OBJECT
public:

  /**
   * @enum TILE_TYPE
   * @brief The TILE_TYPE enum defines the different types of tiles available in the game map.
   */
  enum TILE_TYPE
  {
    PLAYER_ONE = 0,            // Represents the first player's tile.
    PLAYER_TWO,                // Represents the second player's tile.
    PLAYER_THREE,              // Represents the third player's tile.
    PLAYER_FOUR,               // Represents the fourth player's tile.
    MINE_FREE,                 // Represents a mine that's free.
    MINE_ONE,                  // Represents a mine owned by the first player.
    MINE_TWO,                  // Represents a mine owned by the second player.
    MINE_THREE,                // Represents a mine owned by the third player.
    MINE_FOUR,                 // Represents a mine owned by the fourth player.
    TAVERN,                    // Represents a tavern tile.
    FREE_SPACE,                // Represents a free space tile.
    IMPASSABLE,                // Represents an impassable tile.
    PATH
  };
  Q_ENUM(TILE_TYPE)

  /**
   * @struct Unit
   * @brief The Unit struct defines a tile Unit which contains location and owner.
   */
  struct Unit
  {
    Unit(int index, QPair <int, int> cartCoord, int owner)
    {
      m_indexLocation     = index;
      m_cartesianLocation = cartCoord;
      m_owner             = owner;
    }
    int              m_indexLocation;
    QPair <int, int> m_cartesianLocation;
    int              m_owner;
  };

  struct Player
  {
    int     id;
    QString name;
    int     health;
    int     gold;
    int     mineCount;
  };

  struct GameData
  {
    QString            m_gameID;
    QString            m_playUrl;
    QString            m_viewUrl;
    int                m_ownPlayerID;
    int                m_mapSize;
    QString            m_gameMap;
    int                m_currentTurnCount;
    int                m_totalTurns;
    QMap <int, Player> m_playerMap;
  };


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
   * @enum DIR_MOVE
   * @brief The DIR_MOVE enum defines possible moves from a node.
   */
  enum DIR_MOVE
  {
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
  };
  Q_ENUM(DIR_MOVE)


  /**
   * @struct PathFindNode
   * @brief The PathFindNode struct defines Node for usage in path finding.
   * @param index location of node in 1d array map.
   * @param cameFrom parent node of this node in path finding.
   * @param fVal distance from start node + distance from end node.
   */
  struct PathFindNode
  {
    int     index;
    int     cameFrom;
    int     fVal;
    int     gVal;
    bool    visited;
    QString moveToHere;
  };
};

#endif // MEGABLOCKS_H
