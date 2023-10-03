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

Cartographer::Cartographer(QObject *parent)
  : QObject{parent}
{
  m_tileLegend["@1"] = PLAYER_ONE;
  m_tileLegend["@2"] = PLAYER_TWO;
  m_tileLegend["@3"] = PLAYER_THREE;
  m_tileLegend["@4"] = PLAYER_FOUR;
  m_tileLegend["$1"] = MINE_ONE;
  m_tileLegend["$2"] = MINE_TWO;
  m_tileLegend["$3"] = MINE_THREE;
  m_tileLegend["$4"] = MINE_FOUR;
  m_tileLegend["$-"] = MINE_FREE;
  m_tileLegend["##"] = IMPASSABLE;
  m_tileLegend["[]"] = TAVERN;
  m_tileLegend["  "] = FREE_SPACE;
}

void Cartographer::addMineOrPlayerToList(const int mapSize, const int index, TILE_TYPE tileType)
{
  int  owner  = 0;
  bool isMine = false;

  switch (tileType)
  {
  case MINE_ONE:
    owner  = 1;
    isMine = true;
    break;

  case MINE_TWO:
    owner  = 2;
    isMine = true;
    break;

  case MINE_THREE:
    owner  = 3;
    isMine = true;
    break;

  case MINE_FOUR:
    owner  = 4;
    isMine = true;
    break;

  case MINE_FREE:
    owner  = 0;
    isMine = true;
    break;

  case PLAYER_ONE:
    owner = 1;
    break;

  case PLAYER_TWO:
    owner = 3;
    break;

  case PLAYER_THREE:
    owner = 3;
    break;

  case PLAYER_FOUR:
    owner = 4;
    break;

  default:
    qErrnoWarning(2, "Tried to input invalid unit.");
    break;
  }

  Unit newUnit(index, indexToCartesian(mapSize, index), owner);
  if (isMine)
  {
    m_mineList.append(newUnit);
  }
  else //player unit
  {
    m_playerList.append(newUnit);
  }
}

void Cartographer::parseMap(const int&size, const QString&inputMap)
{
  m_mapCache.clear();
  m_mineList.clear();
  m_tavernList.clear();
  m_playerList.clear();

  for (int index = 0; index < inputMap.size(); index += 2)
  {
    QString stringTile = inputMap.mid(index, 2);

    TILE_TYPE tileType = stringToTileType(stringTile);
    if (tileType == MINE_ONE || tileType == MINE_TWO ||
        tileType == MINE_THREE || tileType == MINE_FOUR ||
        tileType == MINE_FREE)
    {
      addMineOrPlayerToList(size, index, tileType);
    }
    else if (tileType == TAVERN)
    {
      Unit newTavern(index, indexToCartesian(size, index), 0);
      m_tavernList.append(newTavern);
    }
    else if (tileType == PLAYER_ONE || tileType == PLAYER_TWO ||
             tileType == PLAYER_THREE || tileType == PLAYER_FOUR)
    {
      addMineOrPlayerToList(size, index, tileType);
    }

    m_mapCache.append(tileType);
  }

  //printMap(size, m_mapCache);
}

void Cartographer::printMap(const int&size, const QList <TILE_TYPE> inputMap)
{
  qDebug() << "Map Size: " << size;
  qDebug() << m_mineList.size() << m_tavernList.size() << m_playerList.size();

  int     colCount = 0;
  QString ezMap;
  for (int index = 0; index < inputMap.size(); index++)
  {
    if (colCount >= size)
    {
      colCount = 0;
      ezMap.append("\n");
    }
    ezMap.append(tileTypeToString(inputMap[index]));
    colCount++;
  }

  qDebug().noquote() << ezMap;
}

QString Cartographer::tileTypeToString(TILE_TYPE tile)
{
  switch (tile)
  {
  case PLAYER_ONE:
    return("1");

  case PLAYER_TWO:
    return("2");

  case PLAYER_THREE:
    return("3");

  case PLAYER_FOUR:
    return("4");

  case MINE_ONE:
    return("A");

  case MINE_TWO:
    return("B");

  case MINE_THREE:
    return("C");

  case MINE_FOUR:
    return("D");

  case MINE_FREE:
    return("O");

  case FREE_SPACE:
    return(" ");

  case IMPASSABLE:
    return("X");

  case TAVERN:
    return("T");
  }
}

Cartographer::TILE_TYPE Cartographer::stringToTileType(const QString tileString)
{
  if (m_tileLegend.contains(tileString))
  {
    return(m_tileLegend[tileString]);
  }
  qErrnoWarning(QString("Tile type not found brother: " + tileString).toUtf8());
}

QPair <int, int> Cartographer::indexToCartesian(const int size, const int index)
{
  int xCoord = index % size;
  int yCoord = (int)(index / size);

  return(QPair <int, int>(xCoord, yCoord));
}

int Cartographer::cartesianToIndex(const int size, QPair <int, int> inputCoord)
{
  int index = (inputCoord.second * size) + inputCoord.first;

  return(index);
}
