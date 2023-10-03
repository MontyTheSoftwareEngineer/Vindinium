#include "marsrover.h"

#include <QMap>
#include <QDebug>

MarsRover::MarsRover(QObject *parent)
  : QObject{parent}
{
}

QPair <int, int> MarsRover::indexToCartesian(const int size, const int index)
{
  int xCoord = index % size;
  int yCoord = (int)(index / size);

  return(QPair <int, int>(xCoord, yCoord));
}

int MarsRover::cartesianToIndex(const int size, QPair <int, int> inputCoord)
{
  int index = (inputCoord.second * size) + inputCoord.first;

  return(index);
}

int MarsRover::roughDistance(const int mapSize, const int pos1, const int pos2)
{
  QPair <int, int> cartPos1 = MarsRover::indexToCartesian(mapSize, pos1);
  QPair <int, int> cartPos2 = MarsRover::indexToCartesian(mapSize, pos2);

  int xDelta = abs(cartPos2.first - cartPos1.first);
  int yDelta = abs(cartPos2.second - cartPos2.second);

  return(xDelta + yDelta);
}

void MarsRover::pathFind(const int mapSize, const int startIndex, const int targetIndex, const QList <Cartographer::TILE_TYPE>&gameMap)
{
  PathFindNode startNode;

  startNode.index    = startIndex;
  startNode.cameFrom = -1;
  startNode.fVal     = roughDistance(mapSize, targetIndex, startIndex);

  QMap <int, PathFindNode> openQueue;   //index,node
  QMap <int, PathFindNode> closedQueue; //index,node
  PathFindNode             currentNode = startNode;

  bool foundTarget = false;
  openQueue[startIndex] = startNode;

  while (!foundTarget && !openQueue.isEmpty())
  {
    //look up
    int upIndex = currentNode.index - mapSize;
    if (upIndex > 0)   //make sure up is in map
    {
    }
  }
}
