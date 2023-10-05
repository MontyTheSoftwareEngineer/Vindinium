#ifndef STATISTICIAN_H
#define STATISTICIAN_H

#include <QObject>

class Statistician : public QObject
{
  Q_OBJECT
public:
  explicit Statistician(QObject *parent = nullptr);
signals:
};

#endif // STATISTICIAN_H
