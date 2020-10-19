var socket = io("http://localhost:9079/utility");
var dataSmartphone = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var deltaData = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var storedDataSmartphone = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var highVal = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var lowVal = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var mouvement = [];
// var monter = 0;
// var descendre = 0;

for (var i = 0; i < 10; i++) {
  let item = {
    min: 0,
    max: 0,
    upDown: 0,
  };
  mouvement[i] = item;
}

socket.on("connect", function () {
  console.log("Connected…");
});

socket.on("sendDataToDashboard", insertText);

function insertText(data) {
  for (var i = 0; i < data.data.value.length; i++) {
    dataSmartphone[i] = data.data.value[i];
    deltaData[i] = storedDataSmartphone[i] - dataSmartphone[i];
    storedDataSmartphone[i] = dataSmartphone[i];

    if (mouvement[i].min > deltaData[i]) {
      mouvement[i].min = deltaData[i];
    }
    if (mouvement[i].max < deltaData[i]) {
      mouvement[i].max = deltaData[i];
    }

    // Monter // Descendre

    if (mouvement[i].min < -3 && mouvement[i].max > 3) {
      if (Math.abs(mouvement[i].min) < Math.abs(mouvement[i].max)) {
        mouvement[i].upDown = 1;
      }
      if (Math.abs(mouvement[i].min) > Math.abs(mouvement[i].max)) {
        mouvement[i].upDown = -1;
      }
    }
  }
  if (mouvement[4].upDown == -1) {
    console.log("Descend");
  }
  if (mouvement[4].upDown == 1) {
    console.log("Monte");
  }
}

setInterval(function () {
  for (var i = 0; i < 10; i++) {
    let item = {
      min: 0,
      max: 0,
      upDown: 0,
    };
    mouvement[i] = item;
  }
}, 500);

// -------------------------- Functions Library -------------------------- //
// --- Map
function mapData(value, a, b, c, d) {
  // first map value from (a..b) to (0..1)
  value = (value - a) / (b - a);
  // then map it from (0..1) to (c..d) and return it
  return c + value * (d - c);
}
function getMax(d) {
  var maxval = Math.max(d);

  return maxval;
}
function getMin(d) {
  var minval = Math.min(d);

  return minval;
}
