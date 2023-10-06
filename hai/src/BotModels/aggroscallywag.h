#ifndef AGGROSCALLYWAG_H
#define AGGROSCALLYWAG_H

#include <QObject>

#include "ibotmodel.h"
class AggroScallyWag : public IBotModel
{
  Q_OBJECT
public:
  explicit AggroScallyWag(QObject *parent = nullptr);
  virtual QString getNextMove(MegaBlocks::GameData&gameData);


signals:

private:
  bool m_isHealing;
};

#endif // AGGROSCALLYWAG_H
