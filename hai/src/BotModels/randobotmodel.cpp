#include "randobotmodel.h"
#include <QTime>

RandoBotModel::RandoBotModel(QObject *parent)
  : IBotModel{parent}
{
}

QString RandoBotModel::getNextMove(MegaBlocks::GameData&gameData)
{
  QStringList directions = { "North", "East", "West", "South", "Stay" };

  qsrand(QTime::currentTime().msec());

  QString randomDirection = directions.at(qrand() % directions.size());
  return(randomDirection);
}
