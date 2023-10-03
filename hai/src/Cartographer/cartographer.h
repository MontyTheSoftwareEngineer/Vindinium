/******************************************************************************
 *
 * @file cartographer.h
 *
 * @brief Cartographer - Class for handling map related functions.
 *
 * @author              Hai Pham
 *
 */

#ifndef CARTOGRAPHER_H
#define CARTOGRAPHER_H

#include <QObject>
#include <QMap>

class Cartographer : public QObject
{
  Q_OBJECT
public:

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

  /**
   * @enum TILE_TYPE
   * @brief The TILE_TYPE enum defines the different types of tiles available in the game map.
   */
  enum TILE_TYPE
  {
    PLAYER_ONE = 0,        // Represents the first player's tile.
    PLAYER_TWO,            // Represents the second player's tile.
    PLAYER_THREE,          // Represents the third player's tile.
    PLAYER_FOUR,           // Represents the fourth player's tile.
    MINE_FREE,             // Represents a mine that's free.
    MINE_ONE,              // Represents a mine owned by the first player.
    MINE_TWO,              // Represents a mine owned by the second player.
    MINE_THREE,            // Represents a mine owned by the third player.
    MINE_FOUR,             // Represents a mine owned by the fourth player.
    TAVERN,                // Represents a tavern tile.
    FREE_SPACE,            // Represents a free space tile.
    IMPASSABLE             // Represents an impassable tile.
  };
  Q_ENUM(TILE_TYPE)

  /**
   * @brief Default constructor.
   * @param parent The parent QObject for the Cartographer.
   */
  explicit Cartographer(QObject *parent = nullptr);

  /**
   * @brief Used to parse the 1D 2Char map into a 1D 1Char/Enum Map.
   * @param size The size of the map.
   * @param map The map representation in QString format (2Char per tile).
   */
  void parseMap(const int& size, const QString& map);

  /**
   * @brief Print map to console.
   * @param size The size of the one-dimensional map.
   * @param inputMap The map to be printed Tile_type representation.
   */
  void printMap(const int& size, const QList <TILE_TYPE> inputMap);

  /**
   * @brief Convert a TILE_TYPE to its corresponding string representation.
   * @param tile The TILE_TYPE to be converted.
   * @return The string representation of the provided TILE_TYPE.
   */
  QString tileTypeToString(TILE_TYPE tile);

  /**
   * @brief Convert a string representation to its corresponding TILE_TYPE.
   * @param tileString The string to be converted.
   * @return The TILE_TYPE representation of the provided string.
   */
  TILE_TYPE stringToTileType(const QString tileString);

  /**
   * @brief Helper function to add mine or player to mine list.
   * @param mapSize size of the game map.
   * @param index 1d index of unit location.
   * @param tileType TILE_TYPE of tile.
   */
  void addMineOrPlayerToList(const int mapSize, const int index, TILE_TYPE tileType);

signals:

private:
  QMap <QString, TILE_TYPE> m_tileLegend; //Map for easier conversion from string -> tile_type.
  QList <TILE_TYPE> m_mapCache;
  QList <Unit> m_mineList;
  QList <Unit> m_tavernList;
  QList <Unit> m_playerList;

  int m_myLocation;
};

#endif // CARTOGRAPHER_H
