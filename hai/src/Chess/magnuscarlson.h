#ifndef MAGNUSCARLSON_H
#define MAGNUSCARLSON_H

#include <QObject>

#include "src/MegaBlocks/megablocks.h"

class MagnusCarlson : public QObject
{
  Q_OBJECT
public:
  explicit MagnusCarlson(QObject *parent = nullptr);

signals:
};

#endif // MAGNUSCARLSON_H
