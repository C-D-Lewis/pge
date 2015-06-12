/********************************** Config ************************************/

var DEBUG = true;

/******************************** Helper **************************************/

function Log(message) {
  if(DEBUG) console.log(message);
}

function hasKey(dict, key) {
  return typeof dict.payload[key] !== 'undefined';
}

var getKey = function(dict, key) {
  if(hasKey(dict, key)) {
    return dict.payload[key];
  }
}

function sendToPebble(dict) {
  Pebble.sendAppMessage(dict, function() {
    Log('Success: ' + JSON.stringify(dict));
  }, function() {
    Log('Failed: ' + JSON.stringify(dict));
  });
}

/******************************* ws module ************************************/

var webSocket;

function connectToServer(url) {
  // Url. Example: ws://localhost:5000
  webSocket = new WebSocket(url);
  webSocket.onopen = function(event) { onOpen(event.data); };
  webSocket.onclose = function(event) { 
    sendToPebble({ 'PGE_WS_URL': 0 });
    onClose(); 
  };
  webSocket.onmessage = function(event) { 
    handleReceiveClientId(event.data);
    onMessage(event.data);
  };
  webSocket.onerror = function(event) { 
    sendToPebble({ 'PGE_WS_URL': 0 });
    onError(); 
  };
}

function handlePGEWSKeys(dict) {
  Log('handling keys: ' + JSON.stringify(dict.payload));

  // WS URL from C and connect
  if(hasKey(dict, 'PGE_WS_URL')) {
    var url = getKey(dict, 'PGE_WS_URL');
    Log('Got WS URL: ' + url);
    connectToServer(url);
  }

  // Disconnect requested
  if(hasKey(dict, 'PGE_WS_DISCONNECT')) {
    Log('Disconnect requested');
    webSocket.send({ 'close': 1 });
    webSocket.close();
  }
}

function handleReceiveClientId(data) {
  if(data) {
    var json = JSON.parse(data);

    if(json.id) {
      sendToPebble({
        'PGE_WS_URL': 1, // success
        'PGE_WS_CLIENT_ID': parseInt(json.id)
      });
    }
  }
}

/**************************** Developer Implemented ***************************/

function onOpen(data) {

}

function onClose() {

}

function onMessage(data) {

}

function onError() {
  
}

/****************************** PebbleKit JS **********************************/

Pebble.addEventListener('ready', function() {
  console.log('PebbleKitJS ready');
});

Pebble.addEventListener('appmessage', function(dict) {
  handlePGEWSKeys(dict);
});