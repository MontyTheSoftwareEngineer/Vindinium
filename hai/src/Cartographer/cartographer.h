#ifndef CARTOGRAPHER_H
#define CARTOGRAPHER_H

#include <QObject>
#include <QMap>

class Cartographer : public QObject
{
  Q_OBJECT
public:
  enum TILE_TYPE
  {
    PLAYER_ONE = 0,
    PLAYER_TWO,
    PLAYER_THREE,
    PLAYER_FOUR,
    MINE_FREE,
    MINE_ONE,
    MINE_TWO,
    MINE_THREE,
    MINE_FOUR,
    TAVERN,
    FREE_SPACE,
    IMPASSABLE
  };
  Q_ENUM(TILE_TYPE)
  explicit Cartographer(QObject *parent = nullptr);

  void parseMap(const int& size, const QString& map);

  void printOneDMap(const int& size, const QList <TILE_TYPE> oneDMap);

  QString tileTypeToString(TILE_TYPE tile);
  TILE_TYPE stringToTileType(const QString tileString);

signals:

private:
  QMap <QString, TILE_TYPE> m_tileLegend;
};

#endif // CARTOGRAPHER_H
