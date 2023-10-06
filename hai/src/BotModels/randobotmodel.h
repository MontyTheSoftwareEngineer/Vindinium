#ifndef RANDOBOTMODEL_H
#define RANDOBOTMODEL_H

#include <QObject>
#include "ibotmodel.h"

class RandoBotModel : public IBotModel
{
  Q_OBJECT
public:
  explicit RandoBotModel(QObject *parent = nullptr);
  virtual QString getNextMove(MegaBlocks::GameData&gameData);

signals:
};

#endif // RANDOBOTMODEL_H
