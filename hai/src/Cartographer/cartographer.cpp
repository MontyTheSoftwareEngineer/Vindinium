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

void Cartographer::parseMap(const int&size, const QString&inputMap, QList <TILE_TYPE>&outputMap)
{
  outputMap.clear();

  for (int index = 0; index < inputMap.size(); index += 2)
  {
    QString stringTile = inputMap.mid(index, 2);
    outputMap.append(stringToTileType(stringTile));
  }

  //printOneDMap(size, outputMap);
}

void Cartographer::printMap(const int&size, const QList <TILE_TYPE> inputMap)
{
  qDebug() << "Map Size: " << size;
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
