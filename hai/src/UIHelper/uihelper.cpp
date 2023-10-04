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

void UIHelper::newMapAvailable(const int mapSize, QList <Cartographer::TILE_TYPE> newMap)
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

QString UIHelper::tileTypeToCellColor(const Cartographer::TILE_TYPE tile)
{
  switch (tile)
  {
  case Cartographer::PLAYER_ONE:
    return("red");

  case Cartographer::PLAYER_TWO:
    return("yellow");

  case Cartographer::PLAYER_THREE:
    return("green");

  case Cartographer::PLAYER_FOUR:
    return("#5693f5");

  case Cartographer::MINE_ONE:
    return("#fcb495");

  case Cartographer::MINE_TWO:
    return("#eaedad");

  case Cartographer::MINE_THREE:
    return("#b5eb91");

  case Cartographer::MINE_FOUR:
    return("#91baeb");

  case Cartographer::MINE_FREE:
    return("#695442");

  case Cartographer::IMPASSABLE:
    return("lightgrey");

  case Cartographer::TAVERN:
    return("orange");

  case Cartographer::FREE_SPACE:
    return("white");

  case Cartographer::PATH:
    return("#bce8ae");

  default: {
    qErrnoWarning("tileTypeToCellColor unknown tile type");
  }
  }
}

QString UIHelper::tileTypeToDisplayText(const Cartographer::TILE_TYPE tile)
{
  switch (tile)
  {
  case Cartographer::PLAYER_ONE:
    return("@1");

  case Cartographer::PLAYER_TWO:
    return("@2");

  case Cartographer::PLAYER_THREE:
    return("@3");

  case Cartographer::PLAYER_FOUR:
    return("@4");

  case Cartographer::MINE_ONE:
    return("$1");

  case Cartographer::MINE_TWO:
    return("$2");

  case Cartographer::MINE_THREE:
    return("$3");

  case Cartographer::MINE_FOUR:
    return("$4");

  case Cartographer::MINE_FREE:
    return("$-");

  case Cartographer::IMPASSABLE:
    return("XX");

  case Cartographer::TAVERN:
    return("[]");

  case Cartographer::FREE_SPACE:
    return("  ");

  case Cartographer::PATH:
    return("  ");

  default: {
    qErrnoWarning("tileTypeToCellColor unknown tile type");
  }
  }
}
