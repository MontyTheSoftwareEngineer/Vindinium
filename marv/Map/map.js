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
}

/**
 * @class Tile
 * @property {tileType} type
 * @property {number} owner
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

module.exports = Map;