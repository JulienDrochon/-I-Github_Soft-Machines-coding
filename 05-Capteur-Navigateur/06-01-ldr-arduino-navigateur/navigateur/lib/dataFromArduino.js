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
