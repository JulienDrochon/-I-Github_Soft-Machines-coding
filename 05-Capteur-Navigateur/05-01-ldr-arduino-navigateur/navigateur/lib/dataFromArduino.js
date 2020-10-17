var dataFromArduino = [];

var socket = io.connect("http://localhost:3000");
socket.on("connect", function () {
  console.log("Connected…");
});

socket.on("data", function (message) {
  for (var i = 0; i < message.arduinodata.length; i++) {
    dataFromArduino[i] = message.arduinodata[i];
  }
});

function mapData(value, a, b, c, d) {
  // first map value from (a..b) to (0..1)
  value = (value - a) / (b - a);
  // then map it from (0..1) to (c..d) and return it
  return c + value * (d - c);
}
