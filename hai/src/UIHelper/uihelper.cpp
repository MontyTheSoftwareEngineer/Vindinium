/******************************************************************************
 *
 * @file uihelper.cpp
 *
 * @brief UIHelper - Class for helping to draw to qml.
 *
 * @author              Hai Pham
 *
 */
#include "uihelper.h"
#include <QDebug>

UIHelper::UIHelper(QObject *parent)
  : QObject{parent}
  , m_mapSize(28)
  , m_gameStats("Game Stats")
{
}

int UIHelper::mapSize() const
{
  return(m_mapSize);
}

void UIHelper::setMapSize(int newMapSize)
{
  if (m_mapSize == newMapSize)
  {
    return;
  }
  m_mapSize = newMapSize;
  emit mapSizeChanged();
}

QString UIHelper::getCellColor(const int cellIndex)
{
  if (cellIndex < m_currentCachedMap.size())
  {
    return(tileTypeToCellColor(m_currentCachedMap[cellIndex]));
  }

  return("white");
}

QString UIHelper::getCellText(const int cellIndex)
{
  if (cellIndex < m_currentCachedMap.size())
  {
    return(tileTypeToDisplayText(m_currentCachedMap[cellIndex]));
  }

  return("");
}

void UIHelper::newMapAvailable(const int mapSize, QList <MegaBlocks::TILE_TYPE> newMap)
{
  qDebug() << "UPDATE MAP@@@";
  m_currentCachedMap = newMap;
  setMapSize(mapSize);

  emit mapUpdate();
}

void UIHelper::setDest(const int index)
{
  emit newWayPoint(index);
}

QString UIHelper::tileTypeToCellColor(const MegaBlocks::TILE_TYPE tile)
{
  switch (tile)
  {
  case MegaBlocks::PLAYER_ONE:
    return("red");

  case MegaBlocks::PLAYER_TWO:
    return("yellow");

  case MegaBlocks::PLAYER_THREE:
    return("green");

  case MegaBlocks::PLAYER_FOUR:
    return("#5693f5");

  case MegaBlocks::MINE_ONE:
    return("#fcb495");

  case MegaBlocks::MINE_TWO:
    return("#eaedad");

  case MegaBlocks::MINE_THREE:
    return("#b5eb91");

  case MegaBlocks::MINE_FOUR:
    return("#91baeb");

  case MegaBlocks::MINE_FREE:
    return("#695442");

  case MegaBlocks::IMPASSABLE:
    return("lightgrey");

  case MegaBlocks::TAVERN:
    return("orange");

  case MegaBlocks::FREE_SPACE:
    return("white");

  case MegaBlocks::PATH:
    return("#bce8ae");

  default: {
    qErrnoWarning("tileTypeToCellColor unknown tile type");
  }
  }
}

QString UIHelper::tileTypeToDisplayText(const MegaBlocks::TILE_TYPE tile)
{
  switch (tile)
  {
  case MegaBlocks::PLAYER_ONE:
    return("@1");

  case MegaBlocks::PLAYER_TWO:
    return("@2");

  case MegaBlocks::PLAYER_THREE:
    return("@3");

  case MegaBlocks::PLAYER_FOUR:
    return("@4");

  case MegaBlocks::MINE_ONE:
    return("$1");

  case MegaBlocks::MINE_TWO:
    return("$2");

  case MegaBlocks::MINE_THREE:
    return("$3");

  case MegaBlocks::MINE_FOUR:
    return("$4");

  case MegaBlocks::MINE_FREE:
    return("$-");

  case MegaBlocks::IMPASSABLE:
    return("XX");

  case MegaBlocks::TAVERN:
    return("[]");

  case MegaBlocks::FREE_SPACE:
    return("  ");

  case MegaBlocks::PATH:
    return("  ");

  default: {
    qErrnoWarning("tileTypeToCellColor unknown tile type");
  }
  }
}

QString UIHelper::gameStats() const
{
  return(m_gameStats);
}

void UIHelper::setGameStats(const QString&newGameStats)
{
  if (m_gameStats == newGameStats)
  {
    return;
  }
  m_gameStats = newGameStats;
  emit gameStatsChanged();
}
