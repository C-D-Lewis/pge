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

Log('Server ready on port ' + PORT);

/******************************* Developer Implementation *********************/

/**
 * Set up new client
 */
function onClientConnected(socket) {

}

/**
 * React to message from client
 */
function onClientMessage(data) {

}