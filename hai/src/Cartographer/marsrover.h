/******************************************************************************
 *
 * @file marsrover.h
 *
 * @brief MarsRover - Class for handling pathfinding.
 *
 * @author              Hai Pham
 *
 */

#ifndef MARSROVER_H
#define MARSROVER_H

#include <QObject>

#include "cartographer.h"

class MarsRover : public QObject
{
  Q_OBJECT
public:


  /**
   * @enum DIR_MOVE
   * @brief The DIR_MOVE enum defines possible moves from a node.
   */
  enum DIR_MOVE
  {
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
  };
  Q_ENUM(DIR_MOVE)


  /**
   * @struct PathFindNode
   * @brief The PathFindNode struct defines Node for usage in path finding.
   * @param index location of node in 1d array map.
   * @param cameFrom parent node of this node in path finding.
   * @param fVal distance from start node + distance from end node.
   */
  struct PathFindNode
  {
    int index;
    int cameFrom;
    int fVal;
  };

  /**
   * @brief Default constructor.
   * @param parent The parent QObject for the Cartographer.
   */
  explicit MarsRover(QObject *parent = nullptr);

  /**
   * @brief Convert a 1D index to (x,y) coordinate.
   * @param size size of the game map.
   * @param index 1D array int index.
   * @return QPair containing x,y cartesian coordinate representation of the 1D array.
   */
  static QPair <int, int> indexToCartesian(const int size, const int index);

  /**
   * @brief Convert a cartesian (x,y) coord to 1d index.
   * @param size size of the game map.
   * @param inputCoord QPair containing (x,y) coordinate.
   * @return integer index.
   */
  static int cartesianToIndex(const int size, QPair <int, int> inputCoord);

  /**
   * @brief Provides a rough distance from one point to another.
   * @param mapSize size of the game map.
   * @param pos1 first position.
   * @param pos2 second position position.
   * @return integer rough distance between pos1 and pos 2.
   */
  int roughDistance(const int mapSize, const int pos1, const int pos2);

  /**
   * @brief Provides a rough distance from one point to another.
   * @param mapSize size of the game map.
   * @param startIndex start position.
   * @param targetIndex end position position.
   * @param gameMap 1d representation of game map.
   * @return TBD
   */
  void pathFind(const int mapSize, const int startIndex, const int targetIndex, const QList <Cartographer::TILE_TYPE>& gameMap);

signals:

private:
};

#endif // MARSROVER_H
