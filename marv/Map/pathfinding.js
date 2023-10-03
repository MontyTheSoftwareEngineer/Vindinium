// We will attempt to implement the a star algorithm

const { tileType } = require('./map');

/**
 * @class AStar
 */
class AStar {
  /**
   * @param {Map} grid
   */
  constructor(grid) {
    // we need to take the grid from the map and enhance it with the properties needed for the astar algo
    this.grid = grid;
    for (let x = 0; x < grid.tiles.length; x++) {
      for (let y = 0; y < grid.tiles[x].length; y++) {
        this.grid.tiles[x][y].f = 0;
        this.grid.tiles[x][y].g = 0;
        this.grid.tiles[x][y].h = 0;
        this.grid.tiles[x][y].visited = false;
        this.grid.tiles[x][y].closed = false;
        this.grid.tiles[x][y].parent = null;
      }
    }
  }

  /**
   *
   * @param {Tile} start
   * @param {Tile} end
   */
  findPath = (start, end) => {
    const toProcess = [];

    // lets push the first node into our list to process
    toProcess.push(start);

    // while we have nodes to process
    while (toProcess.length > 0) {
      // first we need to find the lowest f (cost overall with steps and distance to goal) cost node
      let currentNode = toProcess.find((node) => {
        return node.f === Math.min(...toProcess.map((node) => node.f));
      });

      // first of all we need to see if we reached the end
      // end meaning we have a neighbor that is the end
      if (this.getNeighborList(currentNode).includes(end)) {
        // we reached the end so lets return the path
        let path = [end];
        while (currentNode.parent) {
          path.push(currentNode);
          currentNode = currentNode.parent;
        }
        return path.reverse();
      }

      // we didnt reach the end yet so we need to remove the current node from the list to process and set it to closed
      currentNode.closed = true;
      toProcess.splice(toProcess.indexOf(currentNode), 1);

      // fetch a list of neighbors to process
      let neighbors = this.getNeighborList(currentNode);
      // next we need to do our pathfinding for all neighbors to see where we need to go
      for (let neighbor of neighbors) {
        // check if its a non passable tile or already closed and processed
        if (neighbor.closed || neighbor.type !== tileType.free) {
          continue;
        }
        let gScore = currentNode.g + 1;
        let gScoreIsBest = false;

        // check if we have already visited this neighbor and then consider it the best so far
        if (!neighbor.visited) {
          //calculate the manhatten formula first
          neighbor.h = this.manhattan(neighbor.pos, end.pos);
          gScoreIsBest = true;
          neighbor.visited = true;
          // last push it into the q to process as this is now our start kinda sorta
          toProcess.push(neighbor);
        } else if (gScore < neighbor.g) {
          gScoreIsBest = true;
        }

        // if the distance is the best so far we think we have the optimal path so we set the parent and the g score
        if (gScoreIsBest) {
          neighbor.parent = currentNode;
          neighbor.g = gScore;
          neighbor.f = neighbor.g + neighbor.h;
        }
      }
    }
    return [];
  };

  manhattan = (pos0, pos1) => {
    let d1 = Math.abs(pos1.x - pos0.x);
    let d2 = Math.abs(pos1.y - pos0.y);
    return d1 + d2;
  };

  /**
   * Returns a list of neighbors for a given node based on the grid
   * @param {Tile} node
   * @returns {Tile[]}
   */
  getNeighborList = (node) => {
    let neighborList = [];
    // Top
    if (node.x > 0) {
      neighborList.push(this.grid.tiles[node.x - 1][node.y]);
    }
    // bottom
    if (node.x < this.grid.size - 1) {
      neighborList.push(this.grid.tiles[node.x + 1][node.y]);
    }
    // left
    if (node.y > 0) {
      neighborList.push(this.grid.tiles[node.x][node.y - 1]);
    }
    // right
    if (node.y < this.grid.size - 1) {
      neighborList.push(this.grid.tiles[node.x][node.y + 1]);
    }
    return neighborList;
  };
}

exports.AStar = AStar;
