#ifndef CARTOGRAPHER_H
#define CARTOGRAPHER_H

#include <QObject>

class Cartographer : public QObject
{
  Q_OBJECT
public:
  explicit Cartographer(QObject *parent = nullptr);

  void parseMap(const int& size, const QString& map);

signals:
};

#endif // CARTOGRAPHER_H
