/******************************************************************************
 *
 * @file cartographer.cpp
 *
 * @brief Cartographer - Class for handling map related functions.
 *
 * @author              Hai Pham
 *
 */
#include "cartographer.h"
#include <QDebug>

#include "marsrover.h"

Cartographer::Cartographer(QObject *parent)
  : QObject{parent}
{
  m_tileLegend["@1"] = MegaBlocks::PLAYER_ONE;
  m_tileLegend["@2"] = MegaBlocks::PLAYER_TWO;
  m_tileLegend["@3"] = MegaBlocks::PLAYER_THREE;
  m_tileLegend["@4"] = MegaBlocks::PLAYER_FOUR;
  m_tileLegend["$1"] = MegaBlocks::MINE_ONE;
  m_tileLegend["$2"] = MegaBlocks::MINE_TWO;
  m_tileLegend["$3"] = MegaBlocks::MINE_THREE;
  m_tileLegend["$4"] = MegaBlocks::MINE_FOUR;
  m_tileLegend["$-"] = MegaBlocks::MINE_FREE;
  m_tileLegend["##"] = MegaBlocks::IMPASSABLE;
  m_tileLegend["[]"] = MegaBlocks::TAVERN;
  m_tileLegend["  "] = MegaBlocks::FREE_SPACE;
}

int Cartographer::mapCacheSize()
{
  return(m_mapSize);
}

void Cartographer::addMineOrPlayerToList(const int mapSize, const int index, MegaBlocks::TILE_TYPE tileType)
{
  int  owner  = 0;
  bool isMine = false;

  switch (tileType)
  {
  case MegaBlocks::MINE_ONE:
    owner  = 1;
    isMine = true;
    break;

  case MegaBlocks::MINE_TWO:
    owner  = 2;
    isMine = true;
    break;

  case MegaBlocks::MINE_THREE:
    owner  = 3;
    isMine = true;
    break;

  case MegaBlocks::MINE_FOUR:
    owner  = 4;
    isMine = true;
    break;

  case MegaBlocks::MINE_FREE:
    owner  = 0;
    isMine = true;
    break;

  case MegaBlocks::PLAYER_ONE:
    m_myLocation = index;
    owner        = 1;
    break;

  case MegaBlocks::PLAYER_TWO:
    owner = 3;
    break;

  case MegaBlocks::PLAYER_THREE:
    owner = 3;
    break;

  case MegaBlocks::PLAYER_FOUR:
    owner = 4;
    break;

  default:
    qErrnoWarning(2, "Tried to input invalid unit.");
    break;
  }

  MegaBlocks::Unit newUnit(index, MarsRover::indexToCartesian(mapSize, index), owner);
  if (isMine)
  {
    m_mineList.append(newUnit);
  }
  else //player unit
  {
    m_playerList.append(newUnit);
  }
}

QString Cartographer::setDestinationAndGetMove(const int index)
{
  m_mapCache       = m_origMap;
  m_targetLocation = index;
  MarsRover pathFinder;
  QList <MegaBlocks::TILE_TYPE> newMap = pathFinder.pathFind(m_mapSize, m_myLocation, m_targetLocation, m_mapCache);
  m_mapCache = newMap;

  emit mapUpdated();

  return(pathFinder.getNextMove());
}

void Cartographer::parseMap(const int&size, const QString&inputMap)
{
  m_mapCache.clear();

  m_mineList.clear();
  m_tavernList.clear();
  m_playerList.clear();
  m_myLocation = 0;
  m_mapSize    = size;

  for (int countIndex = 0; countIndex < inputMap.size(); countIndex += 2)
  {
    QString stringTile = inputMap.mid(countIndex, 2);

    MegaBlocks::TILE_TYPE tileType = stringToTileType(stringTile);
    if (tileType == MegaBlocks::MINE_ONE || tileType == MegaBlocks::MINE_TWO ||
        tileType == MegaBlocks::MINE_THREE || tileType == MegaBlocks::MINE_FOUR ||
        tileType == MegaBlocks::MINE_FREE)
    {
      addMineOrPlayerToList(size, countIndex / 2, tileType);
    }
    else if (tileType == MegaBlocks::TAVERN)
    {
      MegaBlocks::Unit newTavern(countIndex / 2, MarsRover::indexToCartesian(size, countIndex / 2), 0);
      m_tavernList.append(newTavern);
    }
    else if (tileType == MegaBlocks::PLAYER_ONE || tileType == MegaBlocks::PLAYER_TWO ||
             tileType == MegaBlocks::PLAYER_THREE || tileType == MegaBlocks::PLAYER_FOUR)
    {
      if (tileType == MegaBlocks::PLAYER_ONE)
      {
        m_myLocation = countIndex / 2;
      }
      addMineOrPlayerToList(size, countIndex / 2, tileType);
    }

    m_mapCache.append(tileType);
  }
  m_origMap = m_mapCache;

  //printMap(size, m_mapCache);
}

MegaBlocks::TILE_TYPE Cartographer::stringToTileType(const QString tileString)
{
  if (m_tileLegend.contains(tileString))
  {
    return(m_tileLegend[tileString]);
  }
  qErrnoWarning(QString("Tile type not found brother: " + tileString).toUtf8());
}
