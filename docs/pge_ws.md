# WORK IN PROGRESS

# PGE WebSocket Documentation

This module is aimed at enabling easy communication from a game to an
implementation of the `ws-server` example Node.js server.


## About AppMessage Keys

Due to limitations in PebbleKit JS, AppMessage keys must be declared in
`appinfo.json`. To accomodate for this, 16 intial keys have been declared, named
`PGE_WS_KEY_X`, where `X` is `0` to `15`. You should repurpose these for app-
specific data, as shown in the example of `onClientConnected()` shown below. If
you need more, add them to your own implementation. If you do, don't forget to
update the value of `PGE_WS_NUM_KEYS` in `src/pge/modules/pge_ws.h`!


## Preparing the Server

Edit `ws-server/app.js` to implement the `onClientConnected()` and
`onClientMessage()` functions to turn client communication into Pebble
AppMessages. For example:

```
function broadcastTotalPlayers() {
  for(var i = 0; i < clients.length; i += 1) {
    // Send to each, the total number connected
    clients[i].socket.send(JSON.stringify({ 'PGE_WS_KEY_0': clients.length }));
  }
}

function onClientConnected(socket) {
  broadcastTotalPlayers();
}

function onClientDisconnected(client) {
  broadcastTotalPlayers();
}
```


## Connecting to a Server

The client **MUST** wait for the phone to signal PebbleKit JS is ready with the
'ready' event. To accomodate for this, prepare PGE WS in app initialization:

```
void pge_init() {
  // Start engine
  pge_begin(GColorBlack, logic, draw, click);

  // Prepare WS for web communication with local server
  pge_ws_begin("ws://192.168.1.4:5000", ws_connection_handler, ws_received_handler);
}
```

And providing two handlers for when the connection attempt returns, and when
data is received. 


## Receiving Data

This mechanism is designed this way so that multiple key
values can be retrieved at once, useful for retrieving points or vectors. For
example:

```
static void ws_connection_handler(bool successful) {
  APP_LOG(APP_LOG_LEVEL_INFO, "ws_connection_handler");
  APP_LOG(APP_LOG_LEVEL_INFO, "Got ID: %d", pge_ws_get_client_id());
}

static void ws_received_handler() {
  int key_0_value = pge_ws_get_value(PGE_WS_KEY_0);

  // Check this packet contains what we want
  if(key_0_value != PGE_WS_NOT_FOUND) {
    // Get the value
    APP_LOG(APP_LOG_LEVEL_INFO, "Got PGE_WS_KEY_0 value: %d", key_0_value);
  }
}
```

## Sending Data

To send data from the C side, begin a packet, add values, then send it:

```
// If connected to server
if(pge_ws_is_connected()) {
  // If beginning a packet was successful
  if(pge_ws_packet_begin()) {
    // Add some data
    pge_ws_add_int(PGE_WS_KEY_0, 42);

    // Send the data!
    pge_ws_packet_send();
  }
}
```

These values are then automatically sent to the server in
`handlePGEWSAppMessageKeys()`.


## Implementing a JS client

Use the four functions `onOpen()`, `onClose()`, `onMessage()`, and `onError()`
to implement client logic in `pebble-js-app.js`. Any data received from the C
side is automatically forwarded to the server in `handlePGEWSAppMessageKeys()`.

Manual messages can be sent to the server using the global `webSocket` (only
available after `connectToServer()` is called. For example, using the first
three pre-defined keys to send three values, such as an id, x, and y coordinates
to the server:

```
var id = dict['PGE_WS_KEY_0'];
var x = dict['PGE_WS_KEY_1'];
var y = dict['PGE_WS_KEY_2'];

// Send position
var dataString = JSON.stringify({
  'PGE_WS_KEY_0': id,
  'PGE_WS_KEY_1': x,
  'PGE_WS_KEY_2': y
});

webSocket.send(dataString);
```

On the server side, this can be decoded in `onClientMessage()`:

```
function onClientMessage(socket, data) {
  var json = JSON.parse(data);

  // Recover values
  var id = json['PGE_WS_KEY_0'];
  var x = json['PGE_WS_KEY_1'];
  var y = json['PGE_WS_KEY_1'];
}
```