#include "cartographer.h"
#include <QDebug>

Cartographer::Cartographer(QObject *parent)
  : QObject{parent}
{
}

void Cartographer::parseMap(const int&size, const QString&inputMap)
{
  QString ezMapView;

  qDebug().noquote() << inputMap;

  for (int row = 0; row < size; row++)
  {
    for (int index = 0; index < size * 2; index += 2)
    {
      qDebug() << "Row: " << row;
      int pointStart = (row * size) + index;
      if (inputMap[pointStart] == "#")
      {
        ezMapView.append("#");
      }
      else if (inputMap[pointStart] == "@")
      {
        qDebug() << "Player: " << inputMap[pointStart] << inputMap[pointStart + 1];
        ezMapView.append(inputMap[pointStart + 1]);
      }
      else if (inputMap[pointStart] == "[")
      {
        ezMapView.append("T");
      }
      else if (inputMap[pointStart] == "$")
      {
        if (inputMap[pointStart + 1] == "-")
        {
          ezMapView.append("M");
        }
        else
        {
          int playerMine = QString(inputMap[pointStart + 1]).toInt();
          switch (playerMine)
          {
          case 1:
            ezMapView.append("A");
            break;

          case 2:
            ezMapView.append("B");
            break;

          case 3:
            ezMapView.append("C");
            break;

          case 4:
            ezMapView.append("D");
            break;
          }
        }
      }
      else
      {
        ezMapView.append(" ");
      }
    }
    ezMapView.append("\n");
  }

  qDebug().noquote() << ezMapView;
}
