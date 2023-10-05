#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QObject>
#include "src/MegaBlocks/megablocks.h"
#include "src/GameManager/gamemanager.h"

class JSONParser : public QObject
{
  Q_OBJECT
public:
  explicit JSONParser(QObject *parent = nullptr);

  MegaBlocks::GameData parseJSONString(const QString& jsonString);

signals:
};

#endif // JSONPARSER_H
