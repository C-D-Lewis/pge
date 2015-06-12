// Require
var WebSocketServer = require('ws').Server;

// Config
var DEBUG = true;
var PORT = 5000;

/********************************* Helper *************************************/

function Log(message) {
  if(DEBUG) console.log(message);
}

/********************************* Server *************************************/

var server = new WebSocketServer({ 'port': PORT });

server.on('connection', function (socket) {
  onClientConnected(socket);
  socket.on('message', onClientMessage);
});
Log('Server ready on port ' + PORT);

/******************************* Developer Implementation *********************/

var clients = [];

/**
 * Set up new client
 */
function onClientConnected(socket) {
  // Send client ID and remember
  var client = { 'id': Math.random() * 10000 };
  clients.push(client);
  socket.send(JSON.stringify(client));

  Log('Client ' + client.id + ' connected. Total clients: ' + clients.length);
}

/**
 * React to message from client
 */
function onClientMessage(data) {

}