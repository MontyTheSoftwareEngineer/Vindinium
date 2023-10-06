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

#include "src/MegaBlocks/megablocks.h"

class Cartographer : public QObject
{
  Q_OBJECT
public:

  /**
   * @brief Default constructor.
   * @param parent The parent QObject for the Cartographer.
   */
  explicit Cartographer(QObject *parent = nullptr);

  /**
   * @brief Return current map size from Cartographer.
   * @return map size.
   */
  int mapCacheSize();

  /**
   * @brief Used to parse the 1D 2Char map into a 1D 1Char/Enum Map.
   * @param size The size of the map.
   * @param gameData parsed gameData.
   */
  void parseMap(MegaBlocks::GameData& gameData);

  /**
   * @brief Convert a string representation to its corresponding TILE_TYPE.
   * @param tileString The string to be converted.
   * @return The TILE_TYPE representation of the provided string.
   */
  MegaBlocks::TILE_TYPE stringToTileType(const QString tileString);

  /**
   * @brief Helper function to add mine or player to mine list.
   * @param mapSize size of the game map.
   * @param index 1d index of unit location.
   * @param tileType TILE_TYPE of tile.
   */
  void addMineOrPlayerToList(MegaBlocks::GameData &gameData, const int mapSize, const int index, MegaBlocks::TILE_TYPE tileType);

  /**
   * @brief Return current game map.
   * @return QList of game map in 1D array.
   */
  QList <MegaBlocks::TILE_TYPE> getCurrentMap()
  {
    return(m_mapCache);
  }

  /**
   * @brief Sets a destination for pathfinder.
   * @param gameData reference to cached game data object.
   * @param targetIndex 1D location of target destination.
   */
  QString setDestinationAndGetMove(MegaBlocks::GameData& gameData, const int targetIndex);

signals:

  /**
   * @brief signal indicating a new map update is available.
   */
  void mapUpdated();

private:
  QMap <QString, MegaBlocks::TILE_TYPE> m_tileLegend; //Map for easier conversion from string -> tile_type.
  QList <MegaBlocks::TILE_TYPE> m_origMap;;
  QList <MegaBlocks::TILE_TYPE> m_mapCache;
  QList <MegaBlocks::Unit> m_mineList;
  QList <MegaBlocks::Unit> m_tavernList;
  QList <MegaBlocks::Unit> m_playerList;

  int m_mapSize;
  int m_myLocation;
  int m_targetLocation;
};

#endif // CARTOGRAPHER_H
