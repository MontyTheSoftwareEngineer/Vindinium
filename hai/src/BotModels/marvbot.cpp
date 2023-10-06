#include "marvbot.h"
#include "src/Cartographer/cartographer.h"
#include "src/Cartographer/marsrover.h"

MarvBot::MarvBot(QObject *parent)
  : IBotModel{parent}
  , m_isHealing(false)
{
}

QString MarvBot::getNextMove(MegaBlocks::GameData& gameData)
{
  QString      nextMove;
  Cartographer cartographer;

  if (gameData.m_playerHealth >= 80)
  {
    m_isHealing = false;
  }
  if (gameData.m_playerHealth > 40 && !m_isHealing)
  {
    int playerWithMostMines = 0;
    int mostMines           = 0;
    for (int i = 1; i < 5; i++)
    {
      if (i != gameData.m_ownPlayerID && gameData.m_playerMap[i].mineCount > mostMines)
      {
        mostMines           = gameData.m_playerMap[i].mineCount;
        playerWithMostMines = i;
      }
    }

    int distanceToPlayerWithMostMines = MarsRover::roughDistance(gameData.m_mapSize, gameData.m_playerLocationIndex, gameData.m_playerMap[playerWithMostMines].indexLocation);

    int closestMineDistance = INT_MAX;
    int closestMineIndex    = -1;

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

    int targIndex = 0;
    if (distanceToPlayerWithMostMines < closestMineDistance)
    {
      targIndex = gameData.m_playerMap[playerWithMostMines].indexLocation;
    }
    else
    {
      targIndex = gameData.m_unownedMineList.at(closestMineIndex).m_indexLocation;
    }

    nextMove = cartographer.setDestinationAndGetMove(gameData, targIndex);
  }
  else
  {
    m_isHealing = true;
    return(goToClosestTavern(gameData));
  }

  return(nextMove);
}
