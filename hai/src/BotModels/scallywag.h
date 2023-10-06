#ifndef SCALLYWAG_H
#define SCALLYWAG_H

#include <QObject>
#include "ibotmodel.h"

class ScallyWag : public IBotModel
{
    Q_OBJECT
public:
    explicit ScallyWag(QObject *parent = nullptr);
    virtual QString getNextMove(MegaBlocks::GameData &gameData );

signals:

private:
    bool m_isHealing;
};

#endif // SCALLYWAG_H
