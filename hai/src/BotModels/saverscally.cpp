#include "saverscally.h"
#include "src/Cartographer/cartographer.h"
#include "src/Cartographer/marsrover.h"

SaverScally::SaverScally(QObject *parent)
  : IBotModel{parent}
  , m_isHealing(false)
{
}

QString SaverScally::getNextMove(MegaBlocks::GameData&gameData)
{
  QString      nextMove;
  Cartographer cartographer;

  int  turnsLeft   = gameData.m_totalTurns - gameData.m_currentTurnCount;
  int  goldOutlook = (turnsLeft * gameData.m_playerMap[gameData.m_ownPlayerID].mineCount) + gameData.m_playerMap[gameData.m_ownPlayerID].gold;
  bool slatedToWin = true;

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
      int otherGoldOutlook = (turnsLeft * gameData.m_playerMap[i].mineCount) + gameData.m_playerMap[i].gold;
      if (otherGoldOutlook > goldOutlook)
      {
        slatedToWin = false;
      }
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

    if (slatedToWin)
    {
      return(goToClosestTavern(gameData));
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
}
