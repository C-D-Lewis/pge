# WORK IN PROGRESS

# PGE WebSocket Documentation

This module is aimed at enabling easy communication from a game to an
implementation of the `ws-server` example Node.js server.


## About AppMessage Keys

Due to limitations in PebbleKit JS, AppMessage keys must be declared in
`appinfo.json`. To accomodate for this, 16 intial keys have been declared, named
`PGE_WS_KEY_X`, where `X` is `0` to `15`. You should repurpose these for app-
specific data, as shown in the example of `onClientMessage()` shown below. If
you need more, add them to your own implementation.


## Preparing the Server

Edit `ws-server/app.js` to implement the `onClientConnected()` and
`onClientMessage()` functions to turn client communication into Pebble
AppMessages. For example:

```
function onClientConnected() {
  console.log('New client connected!');
}

// Expected message is 'id:value,x:value,y:value'
function onClientMessage(data) {
  // Decode coords
  var id = data.substring(data.indexOf('id:') + 3);
  data = data.substring(data.indexOf(',') + 1);
  var x = data.substring(data.indexOf('x:') + 2, data.indexOf(','));
  var y = data.substring(data.indexOf('y:') + 2);

  // Use pre-defined keys in appinfo.json to send data
  var dict = {
    'PGE_WS_KEY_0': id
    'PGE_WS_KEY_1': x,
    'PGE_WS_KEY_2': y
  };

  // Update this player with id, x, and y
  Pebble.sendAppMessage(dict);
}
```


## Connecting to a Server

Use the C API...


## Implementing a client

Use the four functions `onOpen()`, `onClose()`, `onMessage()`, and `onError()`
to implement client logic in `pebble-js-app.js`.

Messages can be sent to the server using the global `webSocket` (only available
after `connectToServer()` is called. For example, using the same scheme as the
`onClientMessage()` example above:

```
// Send position
var data = JSON.stringify({
  'id': dict['PGE_WS_KEY_0'],
  'x': dict['PGE_WS_KEY_1'],
  'y': dict['PGE_WS_KEY_2']
});

webSocket.send(data);
```