const jsdom = require('jsdom');
/**
 * @enum {string}
 * @readonly
 */
const tileType = {
  free: '  ',
  wall: '##',
  tavern: '[]',
  mineN: '$-',
  mineH1: '$1',
  mineH2: '$2',
  mineH3: '$3',
  mineH4: '$4',
  hero1: '@1',
  hero2: '@2',
  hero3: '@3',
  hero4: '@4',
};

/**
 * @class Map
 * @property {number} size
 * @property {Tile[][]} tiles
 */
class Map {
  constructor(size, mapString) {
    this.size = size;
    this.tiles = Array.from({ length: size }, () => []);
    let index = 0;
    for (let x = 0; x < size; x++) {
      for (let y = 0; y < size; y++) {
        switch (mapString[index] + mapString[index + 1]) {
          case tileType.free:
            this.tiles[x].push(new Tile(tileType.free, null, x, y, 'Free'));
            break;
          case tileType.wall:
            this.tiles[x].push(new Tile(tileType.wall, null, x, y, 'Wall'));
            break;
          case tileType.tavern:
            this.tiles[x].push(new Tile(tileType.tavern, null, x, y, 'Tavern'));
            break;
          case tileType.mineH1:
            this.tiles[x].push(new Tile(tileType.mineH1, 1, x, y, 'Mine 1'));
            break;
          case tileType.mineH2:
            this.tiles[x].push(new Tile(tileType.mineH2, 2, x, y, 'Mine 2'));
            break;
          case tileType.mineH3:
            this.tiles[x].push(new Tile(tileType.mineH3, 3, x, y, 'Mine 3'));
            break;
          case tileType.mineH4:
            this.tiles[x].push(new Tile(tileType.mineH4, 4, x, y, 'Mine 4'));
            break;
          case tileType.mineN:
            this.tiles[x].push(
              new Tile(tileType.mineN, null, x, y, 'Neutral Mine')
            );
            break;
          case tileType.hero1:
            this.tiles[x].push(new Tile(tileType.hero1, 1, x, y, 'Hero 1'));
            break;
          case tileType.hero2:
            this.tiles[x].push(new Tile(tileType.hero2, 2, x, y, 'Hero 2'));
            break;
          case tileType.hero3:
            this.tiles[x].push(new Tile(tileType.hero3, 3, x, y, 'Hero 3'));
            break;
          case tileType.hero4:
            this.tiles[x].push(new Tile(tileType.hero4, 4, x, y, 'Hero 4'));
            break;
        }
        index += 2;
      }
    }
  }

  /**
   *
   * @param {Tile[]} path
   */
  toHTML = (path = []) => {
    const jsdom = require('jsdom');
    const { JSDOM } = jsdom;
    const dom = new JSDOM();
    const document = dom.window.document;
    let element = document.createElement('table');
    for (let i = 0; i < this.size; i++) {
      const row = document.createElement('tr');
      for (let j = 0; j < this.size; j++) {
        const cell = document.createElement('td');
        const tile = this.tiles[i][j];
        if (path.length > 0) {
          // Check if we passed a path and if so, check if the current tile is in the path
          if (path.find((p) => p.x === tile.x && p.y === tile.y)) {
            cell.classList.add('path');
          }
        }
        switch (tile.type) {
          case tileType.free:
            // no additional styling needed
            break;
          case tileType.wall:
            cell.classList.add('wall');
            break;
          case tileType.tavern:
            cell.classList.add('tavern');
            break;
          case tileType.mineH1:
          case tileType.mineH2:
          case tileType.mineH3:
          case tileType.mineH4:
          case tileType.mineN:
            cell.classList.add('mine');
            cell.textContent = tile.owner;
            break;
          case tileType.hero1:
          case tileType.hero2:
          case tileType.hero3:
          case tileType.hero4:
            cell.classList.add('hero');
            cell.textContent = tile.owner;
            break;
        }
        row.appendChild(cell);
      }
      element.appendChild(row);
    }
    document.body.appendChild(element);
    return dom.serialize();
  };
}

/**
 * @class Tile
 * @property {tileType} type
 * @property {number} owner
 * @property {number} x
 * @property {number} y
 * @property {string} title
 * @property {Position} pos
 * @property {number} f
 * @property {number} g
 * @property {number} h
 * @property {boolean} visited
 * @property {boolean} closed
 * @property {?Tile} parent
 */
class Tile {
  get title() {
    return this._title;
  }

  set title(value) {
    this._title = value;
  }
  get x() {
    return this._x;
  }

  set x(value) {
    this._x = value;
  }

  get type() {
    return this._type;
  }

  set type(value) {
    this._type = value;
  }

  get owner() {
    return this._owner;
  }

  get y() {
    return this._y;
  }

  set y(value) {
    this._y = value;
  }

  set owner(value) {
    this._owner = value;
  }

  get pos() {
    return { x: this._x, y: this._y };
  }

  constructor(type, owner, x, y, title = '') {
    this._type = type;
    this._owner = owner;
    this._x = x;
    this._y = y;
    this._title = title;
  }
}

exports.Map = Map;
exports.tileType = tileType;
