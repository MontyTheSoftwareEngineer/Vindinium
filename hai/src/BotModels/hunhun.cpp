#include "hunhun.h"
#include <QDebug>

#include "src/Cartographer/cartographer.h"

HunHun::HunHun(QObject *parent)
  : IBotModel{parent}
{
}

QString HunHun::getNextMove(MegaBlocks::GameData&gameData)
{
  QString      nextMove = "STAY";
  Cartographer cartographer;

  if (gameData.m_playerHealth >= 80)
  {
    m_isHealing = false;
  }

  if (gameData.m_playerHealth > 60 && !m_isHealing)
  {
    int ownMineCount = gameData.m_playerMap[gameData.m_ownPlayerID].mineCount;

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
    if (ownMineCount < 1 || mostMines == 0)
    {
      return(goToClosetMine(gameData));
    }
    else
    {
      //qDebug() << "Looking for player!";
      nextMove = cartographer.setDestinationAndGetMove(gameData, gameData.m_playerMap[playerWithMostMines].indexLocation);
    }
  }
  else
  {
    m_isHealing = true;
    return(goToClosestTavern(gameData));
  }


  return(nextMove);
}
