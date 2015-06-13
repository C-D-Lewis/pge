/******************************** Config **************************************/

var DEBUG = true;
var NUM_APPINFO_KEYS = 16;  // Number of keys declared in appinfo.json 
                            // with values of 0 -> NUM_APPINFO_KEYS

/********************* PGE WS Module JS - DO NOT MODIFY ***********************/

var webSocket = null;

function Log(message) {
  if(DEBUG) console.log(message);
}

function hasKey(dict, key) {
  return typeof dict.payload[key] !== 'undefined';
}

var getValue = function(dict, key) {
  return hasKey(dict, key) ? dict.payload[key] : null;
}

function sendToPebble(dict) {
  Pebble.sendAppMessage(dict, function() {
    Log('Success: ' + JSON.stringify(dict));
  }, function() {
    Log('Failed: ' + JSON.stringify(dict));
  });
}

function connectToServer(url) {
  // Url. Example: ws://localhost:5000
  webSocket = new WebSocket(url);
  webSocket.onopen = function(event) { 
    Log('Connection opened!');
    if(event.data) {
      onOpen(event.data); 
      handlePGEWSProtocol(event.data);
    }
  };
  webSocket.onclose = function(event) { 
    Log('onclose');
    sendToPebble({ 'PGE_WS_URL': 0 });
    onClose(); 
  };
  webSocket.onmessage = function(event) { 
    Log('onmessage');
    if(event.data) {
      handlePGEWSProtocol(event.data);
      onMessage(event.data);
    } else {
      Log('onmessage with no data!');
    }
  };
  webSocket.onerror = function(event) { 
    Log('onerror');
    sendToPebble({ 'PGE_WS_URL': 0 });
    onError(); 
  };
}

function handlePGEWSAppMessageKeys(dict) {
  Log('handling keys: ' + JSON.stringify(dict.payload));

  // WS URL from C and connect
  if(hasKey(dict, 'PGE_WS_URL')) {
    var url = getValue(dict, 'PGE_WS_URL');
    Log('Got WS URL: ' + url);
    connectToServer(url);
  }

  // Developer dictionary data to send to server
  if(webSocket) {
    var outgoing = {};

    // Check all appinfo.json keys
    for(var i = 0; i < NUM_APPINFO_KEYS; i += 1) {
      var key = '' + i; // String keys
      if(hasKey(dict, key)) {
        outgoing[key] = getValue(dict, key);
        Log('Added key: ' + key + ', value: ' + outgoing[key]);
      }
    }

    var packet = JSON.stringify(outgoing);
    if(packet.length > 4) {
      // Send this data
      webSocket.send(packet);
      Log('Sent developer data');
    }
  } else {
    Log('Data send requested, but webSocket is not ready');
  }
}

function handlePGEWSProtocol(data) {
  var json = JSON.parse(data);

  if(json.id) {
    sendToPebble({
      'PGE_WS_URL': 1, // success
      'PGE_WS_CLIENT_ID': parseInt(json.id)
    });
  }
}

function handlePGEWSReady() {
  sendToPebble({ 'PGE_WS_READY': 1 });
}

/**************************** End PGE WS Module JS ****************************/


/******************* Developer Implemented PGE WS callbacks *******************/

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
  handlePGEWSReady();
});

Pebble.addEventListener('appmessage', function(dict) {
  handlePGEWSAppMessageKeys(dict);
});