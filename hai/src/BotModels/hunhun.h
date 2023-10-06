#ifndef HUNHUN_H
#define HUNHUN_H

#include <QObject>
#include "ibotmodel.h"

class HunHun : public IBotModel
{
  Q_OBJECT
public:
  explicit HunHun(QObject *parent = nullptr);
  virtual QString getNextMove(MegaBlocks::GameData&gameData);

signals:
private:
  bool m_isHealing;
};

#endif // HUNHUN_H
