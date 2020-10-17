var socket = io("http://localhost:9079/utility");
var dataFromSmartphone = [];

socket.on("connect", function () {
  console.log("Connected…");
});

socket.on("sendDataToDashboard", insertText);
function insertText(data) {
  for (var i = 0; i < data.data.value.length; i++) {
    dataFromSmartphone[i] = data.data.value[i];
  }
}

// -------------------------- Functions Library -------------------------- //
// --- Map
function mapData(value, a, b, c, d) {
  // first map value from (a..b) to (0..1)
  value = (value - a) / (b - a);
  // then map it from (0..1) to (c..d) and return it
  return c + value * (d - c);
}
