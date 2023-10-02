const dirs = 'nesw';

const parseTiles = (tiles) => {

}

function bot(state, callback) {
  const i = Math.floor(Math.random() * 4);
  const dir = dirs[i];
  callback(null, dir);
}

module.exports = bot;
if (require.main === module)
  require('vindinium-client').cli(bot);
