#ifndef MARVBOT_H
#define MARVBOT_H

#include <QObject>
#include "ibotmodel.h"

class MarvBot : public IBotModel
{
  Q_OBJECT
public:
  explicit MarvBot(QObject *parent = nullptr);
  virtual QString getNextMove(MegaBlocks::GameData&gameData);

signals:
private:
  bool m_isHealing;
};

#endif // MARVBOT_H
