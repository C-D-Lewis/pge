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

function handlePGEWSKeys(dict) {
  Log('handling keys: ' + JSON.stringify(dict.payload));

  // WS URL from C and connect
  if(dict.payload['PGE_WS_URL']) {
    var url = dict.payload['PGE_WS_URL'];
    Log('Got WS URL: ' + url);
    connectToServer(url);
  }

  // Disconnect requested
  if(dict.payload['PGE_WS_DISCONNECT']) {
    Log('Disconnect requested');
    webSocket.close();
  }
}

function handleReceiveClientId(data) {
  if(data.indexOf('id:') == 0) {
    var dict = {
      'PGE_WS_URL': 1, // success
      'PGE_WS_CLIENT_ID': parseInt(data.substring(data.indexOf('id:') + 3))
    };
    Pebble.sendAppMessage(dict);
  }
}

/**************************** Developer Implemented ***************************/

function onOpen(data) {

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
  Log('onmessage: ' + data);

  // Inform client of successful connection and ID assignment
  handleReceiveClientId(data);

  // Developer-implemented below here

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
  handlePGEWSKeys(dict);
});