#ifndef SAVERSCALLY_H
#define SAVERSCALLY_H

#include <QObject>
#include "ibotmodel.h"

class SaverScally : public IBotModel
{
  Q_OBJECT
public:
  explicit SaverScally(QObject *parent = nullptr);
  virtual QString getNextMove(MegaBlocks::GameData&gameData);

signals:

private:
  bool m_isHealing;
};

#endif // SAVERSCALLY_H
