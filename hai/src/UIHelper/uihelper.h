/******************************************************************************
 *
 * @file uihelper.h
 *
 * @brief UIHelper - Class for helping to draw to qml.
 *
 * @author              Hai Pham
 *
 */
#ifndef UIHELPER_H
#define UIHELPER_H

#include <QObject>
#include <QList>

#include "src/MegaBlocks/megablocks.h"

class UIHelper : public QObject
{
  Q_OBJECT

  Q_PROPERTY(int mapSize READ mapSize WRITE setMapSize NOTIFY mapSizeChanged)
  Q_PROPERTY(QString gameStats READ gameStats WRITE setGameStats NOTIFY gameStatsChanged)
public:

  /**
   * @brief Default constructor.
   * @param parent The parent QObject for the Cartographer.
   */
  explicit UIHelper(QObject *parent = nullptr);

  /**
   * @brief Returns the size of the map.
   * @return Size of the map.
   */
  int mapSize() const;

  /**
   * @brief Sets the size of the map.
   * @param newMapSize New map size.
   */
  void setMapSize(int newMapSize);

  /**
   * @brief Gets the cell color for a given cell index.
   * @param cellIndex The index of the cell.
   * @return A string representing the color of the cell.
   */
  Q_INVOKABLE QString getCellColor(const int cellIndex);

  /**
   * @brief Gets the display text for a given cell index.
   * @param cellIndex The index of the cell.
   * @return A string representing the cell's content.
   */
  Q_INVOKABLE QString getCellText(const int cellIndex);

  QString gameStats() const;
  void setGameStats(const QString&newGameStats);

public slots:

  /**
   * @brief Updates the current cached map with a new map.
   * @param mapSize The size of the new map.
   * @param newMap The new map.
   */
  void newMapAvailable(const int mapSize, QList <MegaBlocks::TILE_TYPE> newMap);

  /**
   * @brief Sets the target destination for pathfinding.
   * @param index The index of the destination cell.
   */
  void setDest(const int index);

signals:

  /**
   * @brief Signal emitted when the map is updated.
   */
  void mapUpdate();


  /**
   * @brief Signal emitted when the map size changes.
   */
  void mapSizeChanged();


  /**
   * @brief Signal emitted when a new waypoint is set.
   * @param index The index of the new waypoint.
   */
  void newWayPoint(const int index);

  void gameStatsChanged();

private:

  /**
   * @brief Converts a tile type to a color string.
   * @param tile The type of the tile.
   * @return A string representing the color of the tile.
   */
  QString tileTypeToCellColor(const MegaBlocks::TILE_TYPE tile);

  /**
   * @brief Converts a tile type to display text.
   * @param tile The type of the tile.
   * @return A string representing the display text of the tile.
   */
  QString tileTypeToDisplayText(const MegaBlocks::TILE_TYPE tile);

  int m_mapSize;
  QList <MegaBlocks::TILE_TYPE> m_currentCachedMap;
  QString m_gameStats;
};

#endif // UIHELPER_H
