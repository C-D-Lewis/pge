/********************************** Config ************************************/

var DEBUG = true;

/******************************** Helper **************************************/

function Log(message) {
  if(DEBUG) console.log(message);
}

/******************************* ws module ************************************/

var webSocket;

function connectToServer(url) {
  // Url. Example: ws://localhost:5000
  var webSocket = new WebSocket(url);
  webSocket.onopen = function(event) { onOpen(); };
  webSocket.onclose = function(event) { onClose(); };
  webSocket.onmessage = function(event) { onMessage(event.data); };
  webSocket.onerror = function(event) { onError(); };
}

/**************************** Developer Implemented ***************************/

function onOpen() {

}

function onClose() {

}

function onMessage(data) {
  // Mkae Pebble dictionaries and send here

}

function onError() {

}

/****************************** PebbleKit JS **********************************/

Pebble.addEventListener('ready', function() {
  console.log('PebbleKitJS ready');

});

Pebble.addEventListener('appmessage', function(dict) {
  // WS URL from C and connect
  if(dict['PGE_WS_URL']) {
    Log('Got WS URL: ' + dict['PGE_WS_URL']);
    connectToServer(url);
  }
});