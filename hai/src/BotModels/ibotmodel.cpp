#include "ibotmodel.h"

#include "src/Cartographer/cartographer.h"
#include "src/Cartographer/marsrover.h"

IBotModel::IBotModel(QObject *parent)
  : QObject{parent}
{
}

QString IBotModel::goToClosetMine(MegaBlocks::GameData&gameData)
{
  Cartographer cartographer;
  QString      nextMove;
  int          closestMineDistance = INT_MAX;
  int          closestMineIndex    = -1;

  for (int i = 0; i < gameData.m_unownedMineList.size(); i++)
  {
    int roughDistance = MarsRover::roughDistance(gameData.m_mapSize, gameData.m_playerLocationIndex,
                                                 gameData.m_unownedMineList.at(i).m_indexLocation);
    if (roughDistance < closestMineDistance)
    {
      closestMineDistance = roughDistance;
      closestMineIndex    = i;
    }
  }

  if (closestMineIndex == -1)
  {
    return(goToClosestTavern(gameData));
  }
  nextMove = cartographer.setDestinationAndGetMove(gameData, gameData.m_unownedMineList.at(closestMineIndex).m_indexLocation);

  if (nextMove == "STAY")
  {
    int badIndex = closestMineIndex;
    closestMineDistance = INT_MAX;
    closestMineIndex    = -1;
    for (int i = 0; i < gameData.m_unownedMineList.size(); i++)
    {
      if (i != badIndex)
      {
        int roughDistance = MarsRover::roughDistance(gameData.m_mapSize, gameData.m_playerLocationIndex,
                                                     gameData.m_unownedMineList.at(i).m_indexLocation);
        if (roughDistance < closestMineDistance)
        {
          closestMineDistance = roughDistance;
          closestMineIndex    = i;
        }
      }
    }
    if (closestMineIndex == -1)
    {
      return(goToClosestTavern(gameData));
    }
    nextMove = cartographer.setDestinationAndGetMove(gameData, gameData.m_unownedMineList.at(closestMineIndex).m_indexLocation);
  }
  return(nextMove);
}

QString IBotModel::goToClosestTavern(MegaBlocks::GameData&gameData)
{
  QString      nextMove;
  Cartographer cartographer;
  int          closestTavernDistance = INT_MAX;
  int          closestTavernIndex    = 0;

  for (int i = 0; i < gameData.m_tavernList.size(); i++)
  {
    int roughDistance = MarsRover::roughDistance(gameData.m_mapSize, gameData.m_playerLocationIndex,
                                                 gameData.m_tavernList.at(i).m_indexLocation);
    if (roughDistance < closestTavernDistance)
    {
      closestTavernDistance = roughDistance;
      closestTavernIndex    = i;
    }
  }
  nextMove = cartographer.setDestinationAndGetMove(gameData, gameData.m_tavernList.at(closestTavernIndex).m_indexLocation);

  if (nextMove == "STAY")
  {
    int badIndex = closestTavernIndex;
    closestTavernDistance = INT_MAX;
    closestTavernIndex    = 0;
    for (int i = 0; i < gameData.m_tavernList.size(); i++)
    {
      if (i != badIndex)
      {
        int roughDistance = MarsRover::roughDistance(gameData.m_mapSize, gameData.m_playerLocationIndex,
                                                     gameData.m_tavernList.at(i).m_indexLocation);
        if (roughDistance < closestTavernDistance)
        {
          closestTavernDistance = roughDistance;
          closestTavernIndex    = i;
        }
      }
    }

    nextMove = cartographer.setDestinationAndGetMove(gameData, gameData.m_tavernList.at(closestTavernIndex).m_indexLocation);
  }
  return(nextMove);
}
