#ifndef UIHELPER_H
#define UIHELPER_H

#include <QObject>
#include <QList>

#include "src/Cartographer/cartographer.h"

class UIHelper : public QObject
{
  Q_OBJECT

  Q_PROPERTY(int mapSize READ mapSize WRITE setMapSize NOTIFY mapSizeChanged FINAL)
public:
  explicit UIHelper(QObject *parent = nullptr);

  int mapSize() const;
  void setMapSize(int newMapSize);

  Q_INVOKABLE QString getCellColor(const int cellIndex);
  Q_INVOKABLE QString getCellText(const int cellIndex);

public slots:
  void newMapAvailable(const int mapSize, QList <Cartographer::TILE_TYPE> newMap);
  void setDest(const int index);

signals:
  void mapUpdate();
  void mapSizeChanged();
  void newWayPoint(const int index);

private:
  QString tileTypeToCellColor(const Cartographer::TILE_TYPE tile);
  QString tileTypeToDisplayText(const Cartographer::TILE_TYPE tile);

  int m_mapSize;
  QList <Cartographer::TILE_TYPE> m_currentCachedMap;
};

#endif // UIHELPER_H
