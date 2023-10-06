#include "aggroscallywag.h"
#include "src/Cartographer/cartographer.h"
#include "src/Cartographer/marsrover.h"

AggroScallyWag::AggroScallyWag(QObject *parent)
  : IBotModel{parent}
  , m_isHealing(false)
{
}

QString AggroScallyWag::getNextMove(MegaBlocks::GameData&gameData)
{
  QString      nextMove;
  Cartographer cartographer;

  if (gameData.m_playerHealth >= 80)
  {
    m_isHealing = false;
  }
  if (gameData.m_playerHealth > 40 && !m_isHealing)
  {
    int distanceToClosestPlayer = INT_MAX;
    int closestPlayerIndex      = 0;
    for (int i = 1; i < 5; i++)
    {
      if (i != gameData.m_ownPlayerID)
      {
        int distanceToCurrPlayer = MarsRover::roughDistance(gameData.m_mapSize, gameData.m_playerLocationIndex, gameData.m_playerMap[i].indexLocation);
        if (distanceToCurrPlayer < distanceToClosestPlayer)
        {
          distanceToClosestPlayer = distanceToCurrPlayer;
          closestPlayerIndex      = i;
        }
      }
    }

    if (closestPlayerIndex != 0 && distanceToClosestPlayer < 3 && gameData.m_playerMap[closestPlayerIndex].health < gameData.m_playerHealth && gameData.m_playerMap[closestPlayerIndex].mineCount > 0)
    {
      return(cartographer.setDestinationAndGetMove(gameData, gameData.m_playerMap[closestPlayerIndex].indexLocation));
    }
    else if (closestPlayerIndex != 0 && distanceToClosestPlayer < 3 && gameData.m_playerMap[closestPlayerIndex].health > gameData.m_playerHealth)
    {
      return(goToClosestTavern(gameData));
    }


    return(goToClosetMine(gameData));
  }
  else
  {
    m_isHealing = true;
    return(goToClosestTavern(gameData));
  }

  return(nextMove);

  return(nextMove);
}
