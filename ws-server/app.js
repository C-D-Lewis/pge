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

var server;
var clients = [];

function addClient(socket) {
  // Create new client object
  var client = { 
    'id': Math.floor(Math.random() * 1000000),
    'socket': socket
  };
  clients.push(client);

  // Send back issued ID
  socket.send({ 'id': client.id });
  Log('Client ' + client.id + ' connected. Total clients: ' + clients.length);
}

function handleProtocol(socket, data) {
  var json = JSON.parse(data);

  if(json.close) {
    // Close this client
    var index = clients.indexOf(socket);
    if(index > -1) {
      Log('Client ' + clients.get(index).id + ' disconnected');
      clients = clients.splice(index, 1);
    } else {
      Log('Closing client not found!');
    }
  }
}

function startServer() {
  server = new WebSocketServer({ 'port': PORT });
  server.on('connection', function (socket) {
    addClient(socket);
    onClientConnected(socket);
    socket.on('message', function(data) {
      if(data) {
        handleProtocol(this, data);
        onClientMessage(this, data);
      }
    });
    socket.on('error', function() {
      Log('onerror');
    })
  });

  Log('Server ready on port ' + PORT);
}
startServer();

/******************************* Developer Implementation *********************/

/**
 * Set up new client
 */
function onClientConnected(socket) {

}

/**
 * React to message from client
 */
function onClientMessage(socket, data) {

}