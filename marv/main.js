const dirs = 'nesw';
const { Map } = require('./Map/map.js');
const vindinium = require('vindinium-client');
const config = require('./config.json');

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

// DEBUG
const express = require('express');
const { createServer } = require('node:http');
const { join } = require('node:path');
const { Server } = require('socket.io');
const { AStar } = require('./Map/pathfinding');

const app = express();
const server = createServer(app);
const io = new Server(server);
app.use(express.static(join(__dirname, 'public')));

app.get('/', (req, res) => {
  res.sendFile(join(__dirname, 'index.html'));
});

io.on('connection', (socket) => {
  console.log('User connected');
  let map;
  let aStar;

  socket.on('requestPath', ({ x, y }) => {
    socket.emit('map', map.toHTML());
    aStar = new AStar(map);
    const path = aStar.findPath(map.tiles[1][3], map.tiles[x][y]);
    socket.emit('map', map.toHTML(path));
  });

  socket.on('startGame', () => {
    console.log('start');
    function bot(state, callback) {
      map = new Map(state.game.board.size, state.game.board.tiles);
      socket.emit('map', map.toHTML());
      socket.emit('gameState', state.game);
      socket.emit('heroState', state.hero);
      socket.emit('viewUrl', state.viewUrl);
      const i = Math.floor(Math.random() * 4);
      const dir = dirs[i];
      callback(null, dir);
    }

    // temp load state from file
    const state = require('./savedState.json');
    bot(state, (err, dir) => {});
    // vindinium(
    //   {
    //     key: config.key,
    //     serverUrl: config.serverUrl,
    //     bot: bot,
    //     mode: 'training',
    //     turns: 10,
    //   },
    //   function (err, lastState) {
    //     let test = '';
    //   }
    // );
  });

  socket.on('disconnect', () => {
    console.log('User disconnected');
  });
});

server.listen(3000, () => {
  console.log('server running at http://localhost:3000');
});
