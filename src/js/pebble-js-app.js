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
  webSocket = new WebSocket(url);
  webSocket.onopen = function(event) { onOpen(event.data); };
  webSocket.onclose = function(event) { onClose(); };
  webSocket.onmessage = function(event) { onMessage(event.data); };
  webSocket.onerror = function(event) { onError(); };
}

/**************************** Developer Implemented ***************************/

function onOpen(data) {
  var json = JSON.parse(data);

  // Inform client
  var dict = {
    'PGE_WS_URL': 1, // success
    'PGE_WS_CLIENT_ID': data.id
  };
  Pebble.sendAppMessage(dict);
}

function onClose() {
  // Inform client
  var dict = {
    'PGE_WS_URL': 0 // no longer connected
  };
  Pebble.sendAppMessage(dict);
}

function onMessage(data) {
  // Make Pebble dictionaries and send here

}

function onError() {
  // Inform client
  var dict = {
    'PGE_WS_URL': 0 // failure
  };
  Pebble.sendAppMessage(dict);
}

/****************************** PebbleKit JS **********************************/

Pebble.addEventListener('ready', function() {
  console.log('PebbleKitJS ready');

});

Pebble.addEventListener('appmessage', function(dict) {
  // WS URL from C and connect
  if(dict.payload['PGE_WS_URL']) {
    var url = dict.payload['PGE_WS_URL'];
    Log('Got WS URL: ' + url);
    connectToServer(url);

    return;
  }

  // Not caught
  Log('AppMessage with unknown key arrived: ' + JSON.stringify(dict.payload));
});