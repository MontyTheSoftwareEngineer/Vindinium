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
  int yDelta = abs(cartPos2.second - cartPos1.second);

  return(xDelta + yDelta);
}

QList <Cartographer::TILE_TYPE> MarsRover::pathFind(const int mapSize, const int startIndex, const int targetIndex, const QList <Cartographer::TILE_TYPE>& gameMap)
{
  PathFindNode startNode;

  startNode.index    = startIndex;
  startNode.cameFrom = -1;
  startNode.fVal     = roughDistance(mapSize, targetIndex, startIndex);
  startNode.gVal     = 0;
  startNode.visited  = false;           // Changed from true

  //qDebug() << "Rough Distance " << roughDistance(mapSize, targetIndex, startIndex);;

  QMap <int, PathFindNode> openQueue;   // index, node
  QMap <int, PathFindNode> closedQueue; // index, node
  PathFindNode             currentNode = startNode;

  int  maxMapSize  = mapSize * mapSize;
  bool foundTarget = false;
  openQueue[startIndex] = startNode;

  while (!foundTarget && !openQueue.isEmpty())
  {
    qDebug() << "OpenQueue size: " << openQueue.size();

    int lowestFValIndex = -1;
    int lowestFVal      = INT_MAX;

    foreach(int index, openQueue.keys())
    {
      if (openQueue[index].fVal < lowestFVal)
      {
        lowestFVal      = openQueue[index].fVal;
        lowestFValIndex = index;
      }
    }

    currentNode = openQueue[lowestFValIndex];
    openQueue.remove(lowestFValIndex);
    closedQueue[lowestFValIndex] = currentNode;
    qDebug() << "Current node: " << currentNode.index << ", fVal: " << currentNode.fVal;
    QList <QPair <int, int> > nodesToAdd;

    for (int i = 0; i < 4; i++)
    {
      int modifier = 0;
      qDebug() << "Checking dir: " << i;
      switch (i)
      {
      case 0:      // up
        modifier = -mapSize;
        break;

      case 1:      // right
        modifier = 1;
        break;

      case 2:      // down
        modifier = mapSize;
        break;

      case 3:      // left
        modifier = -1;
        break;
      }

      int nextIndex = currentNode.index + modifier;
      qDebug() << "Neighbor index: " << nextIndex;
      QPair <int, int> nextIndexCartesian = indexToCartesian(mapSize, nextIndex);
      if (nextIndex == targetIndex)
      {
        qDebug() << "Found Target!";
        foundTarget = true;
        PathFindNode finalNode;
        finalNode.index          = nextIndex;
        finalNode.cameFrom       = currentNode.index;
        closedQueue[targetIndex] = finalNode;
      }
      if ((nextIndex >= 0) && (nextIndex < maxMapSize) &&
          (nextIndexCartesian.first >= 0 && nextIndexCartesian.first < mapSize) &&
          (nextIndexCartesian.second >= 0 && nextIndexCartesian.second < mapSize) &&
          gameMap.at(nextIndex) == Cartographer::FREE_SPACE &&
          !closedQueue.contains(nextIndex))
      {
        qDebug() << "Valid node!";
        int nextNodeFVal = currentNode.gVal + 1 + roughDistance(mapSize, nextIndex, targetIndex);
        nodesToAdd.append(QPair <int, int>(nextIndex, nextNodeFVal));
      }
      else
      {
        qDebug() << "Invalid node...";
      }
    }

    qDebug() << "Adding nodes";
    for (int i = 0; i < nodesToAdd.size(); i++)
    {
      qDebug() << "New Node: " << nodesToAdd[i].first << " , FVal: " << nodesToAdd[i].second;
      if (!openQueue.contains(nodesToAdd[i].first) || (openQueue[nodesToAdd[i].first].fVal > nodesToAdd[i].second))
      {
        PathFindNode newNode;
        newNode.index    = nodesToAdd[i].first;
        newNode.cameFrom = currentNode.index;
        newNode.fVal     = nodesToAdd[i].second;
        newNode.gVal     = currentNode.gVal + 1;
        newNode.visited  = false;
        openQueue[nodesToAdd[i].first] = newNode;
        qDebug() << "Added: " << newNode.index;
      }
      else
      {
        qDebug() << "Decided not to add node!";
        qDebug() << "open queue contains: " << openQueue.contains(nodesToAdd[i].first);
        if (openQueue.contains(nodesToAdd[i].first))
        {
          qDebug() << "New FVal: " << nodesToAdd[i].second << " | Old FVal: " << openQueue[nodesToAdd[i].first].fVal;
        }
      }
    }

    qDebug() << "Moving node to finished: " << currentNode.index;
    openQueue.remove(currentNode.index);
    closedQueue[currentNode.index] = currentNode;



    if (currentNode.index == targetIndex)
    {
      qDebug() << "TARGET FOUND!";
      foundTarget = true;
      break;
    }
  }

  QList <Cartographer::TILE_TYPE> newMap = gameMap;

  if (foundTarget)
  {
    qDebug() << "FOUND!";
    QList <int> path;
    int         currentPathIndex = targetIndex;
    while (currentPathIndex != startIndex)
    {
      path.prepend(currentPathIndex);
      currentPathIndex = closedQueue[currentPathIndex].cameFrom;
    }
    foreach(int pathIndex, path)
    {
      newMap[pathIndex] = Cartographer::PATH;
    }
  }
  else
  {
    qDebug() << "No path to targ";
  }

  return(newMap);
}
