var socket = io("http://localhost:9079/utility");
var dataSmartphone = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var deltaData = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var storedDataSmartphone = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var highVal = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var lowVal = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var sensor = [];
var triggerMoving = 0;
var lastFixedPositions = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var comparePositions = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var faceUp = ["Screen", "Back", "Right", "Left", "Top", "Bottom"];

for (var i = 0; i < 10; i++) {
  let item = {
    value: 0,
    min: 0,
    max: 0,
    upDown: 0,
  };
  sensor[i] = item;
}

socket.on("connect", function () {
  console.log("Connected…");
});

// Data receiving
socket.on("sendDataToDashboard", receivingData);
function receivingData(data) {
  if (data) {
    for (var i = 0; i < data.data.value.length; i++) {
      //Compute data
      dataSmartphone[i] = data.data.value[i];
      deltaData[i] = storedDataSmartphone[i] - dataSmartphone[i];
      storedDataSmartphone[i] = dataSmartphone[i];

      if (sensor[i].min > deltaData[i]) {
        sensor[i].min = deltaData[i];
      }
      if (sensor[i].max < deltaData[i]) {
        sensor[i].max = deltaData[i];
      }
      // Check motion sense
      if (sensor[i].min < -3 && sensor[i].max > 3) {
        if (Math.abs(sensor[i].min) < Math.abs(sensor[i].max)) {
          sensor[i].upDown = 1;
          console.log(sensor[0].upDown);
        }
        if (Math.abs(sensor[i].min) > Math.abs(sensor[i].max)) {
          sensor[i].upDown = -1;
        }
      }
    }

    // Still Phone
    if (isSmartphoneMoving() == 0 && triggerMoving == 0) {
      triggerMoving = 1;
      smartphoneFace();
      for (var i = 0; i < 10; i++) {
        comparePositions[i] = lastFixedPositions[i] - sensor[i].value;
        console.log("compare : " + i + "  " + comparePositions[i]);
      }
    }
  }
}

// Resetting function after pausing
setInterval(function () {
  for (var i = 0; i < 10; i++) {
    let item = {
      value: dataSmartphone[i],
      min: 0,
      max: 0,
      upDown: 0,
    };
    sensor[i] = item;
    //isMoving = 0;
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
function isSmartphoneMoving() {
  let isMoving;
  if (
    Math.abs(deltaData[0]) > 20 ||
    Math.abs(deltaData[1]) > 20 ||
    Math.abs(deltaData[2]) > 20 ||
    dataSmartphone[3] != 0 ||
    dataSmartphone[4] != 0 ||
    dataSmartphone[5] != 0
  ) {
    triggerMoving = 0;
    isMoving = 1;
  }
  if (
    deltaData[0] == 0 &&
    deltaData[1] == 0 &&
    deltaData[2] == 0 &&
    dataSmartphone[3] == 0 &&
    dataSmartphone[4] == 0 &&
    dataSmartphone[5] == 0
  ) {
    isMoving = 0;
  }
  return isMoving;
}

function storeFixedPositions() {}

function smartphoneFace() {
  let face = "";
  // screen is up
  if (
    -2 < dataSmartphone[6] &&
    dataSmartphone[6] < 2 &&
    -2 < dataSmartphone[7] &&
    dataSmartphone[7] < 2 &&
    7 < dataSmartphone[8] &&
    dataSmartphone[8] < 11
  ) {
    face = faceUp[0];
    console.log("face : " + faceUp[0]);
  }
  // back is up
  if (
    -2 < dataSmartphone[6] &&
    dataSmartphone[6] < 2 &&
    -2 < dataSmartphone[7] &&
    dataSmartphone[7] < 2 &&
    -12 < dataSmartphone[8] &&
    dataSmartphone[8] < -8
  ) {
    face = faceUp[1];
    console.log("face : " + faceUp[1]);
  }
  // right is up ??
  if (
    7 < dataSmartphone[6] &&
    dataSmartphone[6] < 11 &&
    -2 < dataSmartphone[7] &&
    dataSmartphone[7] < 2 &&
    -2 < dataSmartphone[8] &&
    dataSmartphone[8] < 2
  ) {
    face = faceUp[2];
    console.log("face : " + faceUp[2]);
  }
  // left is up ??
  if (
    -11 < dataSmartphone[6] &&
    dataSmartphone[6] < -7 &&
    -2 < dataSmartphone[7] &&
    dataSmartphone[7] < 3 &&
    -2 < dataSmartphone[8] &&
    dataSmartphone[8] < 2
  ) {
    face = faceUp[3];
    console.log("face : " + faceUp[3]);
  }
  // top is up
  if (
    -2 < dataSmartphone[6] &&
    dataSmartphone[6] < 2 &&
    7 < dataSmartphone[7] &&
    dataSmartphone[7] < 11 &&
    -2 < dataSmartphone[8] &&
    dataSmartphone[8] < 2
  ) {
    face = faceUp[4];
    console.log("face : " + faceUp[4]);
  }
  // bottom is up
  if (
    -2 < dataSmartphone[6] &&
    dataSmartphone[6] < 2 &&
    -11 < dataSmartphone[7] &&
    dataSmartphone[7] < -7 &&
    -2 < dataSmartphone[8] &&
    dataSmartphone[8] < 2
  ) {
    face = faceUp[5];
    console.log("face : " + faceUp[5]);
  }
  return face;
}
