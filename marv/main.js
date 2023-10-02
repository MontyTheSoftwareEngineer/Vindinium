const dirs = 'nesw';
const Map = require('./Map/map.js');

/**
 * @typedef {Object} Position
 * @property {number} x
 * @property {number} y
 */

/**
 * @typedef {Object} Hero
 * @property {number} id
 * @property {string} name
 * @property {string} userId
 * @property {number} elo
 * @property {Position} pos
 * @property {string} [lastDir]
 * @property {number} life
 * @property {number} gold
 * @property {number} mineCount
 * @property {Position} spawnPos
 * @property {boolean} crashed
 */

/**
 * @typedef {Object} Board
 * @property {number} size
 * @property {string} tiles
 */

/**
 * @typedef {Object} Game
 * @property {string} id
 * @property {number} turn
 * @property {number} maxTurns
 * @property {Hero[]} heroes
 * @property {Board} board
 * @property {boolean} finished
 */

/**
 * @typedef {Object} State
 * @property {Game} game
 * @property {Hero} hero
 * @property {string} token
 * @property {string} viewUrl
 * @property {string} playUrl
 */

/**
 * @param {State} state
 */
function bot(state, callback) {
  const map = new Map(state.game.board.size, state.game.board.tiles);
  const i = Math.floor(Math.random() * 4);
  const dir = dirs[i];
  callback(null, dir);
}

module.exports = bot;
if (require.main === module) require('vindinium-client').cli(bot);
