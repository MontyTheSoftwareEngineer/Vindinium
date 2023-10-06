#ifndef IBOTMODEL_H
#define IBOTMODEL_H

#include <QObject>
#include "src/MegaBlocks/megablocks.h"

class IBotModel : public QObject
{
  Q_OBJECT
public:
  explicit IBotModel(QObject *parent = nullptr);

  virtual QString getNextMove(MegaBlocks::GameData& gameData) = 0;

  QString goToClosetMine(MegaBlocks::GameData& gameData);
  QString goToClosestTavern(MegaBlocks::GameData& gameData);

signals:
};

#endif // IBOTMODEL_H
