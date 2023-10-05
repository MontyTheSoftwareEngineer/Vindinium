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

QList <MegaBlocks::TILE_TYPE> MarsRover::pathFind(const int mapSize, const int startIndex, const int targetIndex, const QList <MegaBlocks::TILE_TYPE>& gameMap)
{
  m_nextMove = "STAY";
  MegaBlocks::PathFindNode startNode;

  startNode.index    = startIndex;
  startNode.cameFrom = -1;
  startNode.fVal     = roughDistance(mapSize, targetIndex, startIndex);
  startNode.gVal     = 0;
  startNode.visited  = false;

  QMap <int, MegaBlocks::PathFindNode> openQueue;   // index, node
  QMap <int, MegaBlocks::PathFindNode> closedQueue; // index, node
  MegaBlocks::PathFindNode             currentNode = startNode;

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
    QList <MegaBlocks::PathFindNode> nodesToAdd;

    for (int i = 0; i < 4; i++)
    {
      int     modifier = 0;
      QString move;
      qDebug() << "Checking dir: " << i;
      switch (i)
      {
      case 0:      // up
        modifier = -mapSize;
        move     = "NORTH";
        break;

      case 1:      // right
        modifier = 1;
        move     = "EAST";
        break;

      case 2:      // down
        modifier = mapSize;
        move     = "SOUTH";
        break;

      case 3:      // left
        modifier = -1;
        move     = "WEST";
        break;
      }

      int nextIndex = currentNode.index + modifier;
      qDebug() << "Neighbor index: " << nextIndex;
      QPair <int, int> nextIndexCartesian = indexToCartesian(mapSize, nextIndex);
      if (nextIndex == targetIndex)
      {
        qDebug() << "Found Target!";
        foundTarget = true;
        MegaBlocks::PathFindNode finalNode;
        finalNode.index          = nextIndex;
        finalNode.cameFrom       = currentNode.index;
        finalNode.moveToHere     = move;
        closedQueue[targetIndex] = finalNode;
      }
      else if ((nextIndex >= 0) && (nextIndex < maxMapSize) &&                            //within index range
               (nextIndexCartesian.first >= 0 && nextIndexCartesian.first < mapSize) &&   //x valid
               (nextIndexCartesian.second >= 0 && nextIndexCartesian.second < mapSize) && //y valid
               gameMap.at(nextIndex) == MegaBlocks::FREE_SPACE &&                         //space is free space
               !closedQueue.contains(nextIndex))                                          //not in closed queue
      {
        qDebug() << "Valid node!";
        int nextNodeFVal = currentNode.gVal + 1 + roughDistance(mapSize, nextIndex, targetIndex);

        MegaBlocks::PathFindNode newNode;
        newNode.index      = nextIndex;
        newNode.cameFrom   = currentNode.index;
        newNode.fVal       = nextNodeFVal;
        newNode.gVal       = currentNode.gVal + 1;
        newNode.visited    = false;
        newNode.moveToHere = move;
        nodesToAdd.append(newNode);
      }
      else
      {
        qDebug() << "Invalid node...";
      }
    }

    qDebug() << "**Adding nodes**";
    for (int i = 0; i < nodesToAdd.size(); i++)
    {
      qDebug() << "New Node: " << nodesToAdd[i].index << " , FVal: " << nodesToAdd[i].index;
      if (!openQueue.contains(nodesToAdd[i].index) || (openQueue[nodesToAdd[i].index].fVal > nodesToAdd[i].index))
      {
        openQueue[nodesToAdd[i].index] = nodesToAdd[i];
        qDebug() << "Added: " << nodesToAdd[i].index;
      }
      else
      {
        qDebug() << "Decided not to add node!";
        qDebug() << "open queue contains: " << openQueue.contains(nodesToAdd[i].index);
        if (openQueue.contains(nodesToAdd[i].index))
        {
          qDebug() << "New FVal: " << nodesToAdd[i].fVal << " | Old FVal: " << openQueue[nodesToAdd[i].index].fVal;
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

  QList <MegaBlocks::TILE_TYPE> newMap = gameMap;

  if (foundTarget)
  {
    qDebug() << "FOUND!";
    QList <int> path;
    int         currentPathIndex = targetIndex;
    while (currentPathIndex != startIndex)
    {
      path.prepend(currentPathIndex);

      if (closedQueue[currentPathIndex].cameFrom == startIndex)
      {
        m_nextMove = closedQueue[currentPathIndex].moveToHere;
      }

      currentPathIndex = closedQueue[currentPathIndex].cameFrom;
    }
    foreach(int pathIndex, path)
    {
      newMap[pathIndex] = MegaBlocks::PATH;
    }
  }
  else
  {
    qDebug() << "No path to targ";
  }

  return(newMap);
}
