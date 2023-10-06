#include "scallywag.h"
#include "src/Cartographer/cartographer.h"

ScallyWag::ScallyWag(QObject *parent)
  : IBotModel{parent}
  , m_isHealing(false)
{
}

QString ScallyWag::getNextMove(MegaBlocks::GameData& gameData)
{
  QString      nextMove;
  Cartographer cartographer;

  if (gameData.m_playerHealth >= 80)
  {
    m_isHealing = false;
  }
  if (gameData.m_playerHealth > 40 && !m_isHealing)
  {
    return(goToClosetMine(gameData));
  }
  else
  {
    m_isHealing = true;
    return(goToClosestTavern(gameData));
  }

  return(nextMove);
}
