var socket = io("http://localhost:9079/utility");
var dataSmartphone = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var deltaData = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var storedDataSmartphone = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var sensor = [];
var triggerMoving = 0;
var lastFixedPositions = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var comparePositions = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var listFaceUp = ["Screen", "Back", "Right", "Left", "Top", "Bottom"];
var lastFaceUp = "";
let currentFaceUp = "";

for (var i = 0; i < 10; i++) {
  let item = {
    value: 0,
    delta: 0,
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
  if (data.data != undefined) {
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
        comparePositions[i] = sensor[i].value - lastFixedPositions[i];
        // sensor = deltaFixedPosition;
        lastFixedPositions[i] = sensor[i].value;
        // sensor[i].delta = comparePositions[i];
        // console.log("compare : " + i + "  " + comparePositions[i]);
      }
      validate();
      console.log(sensor);
    }
  }
}

// Resetting function after pausing
setInterval(function () {
  for (var i = 0; i < 10; i++) {
    let item = {
      value: dataSmartphone[i],
      delta: comparePositions[i],
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
    Math.abs(deltaData[0]) > 5 ||
    Math.abs(deltaData[1]) > 5 ||
    Math.abs(deltaData[2]) > 5 ||
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

function smartphoneFace() {
  if (currentFaceUp != undefined) {
    lastFaceUp = currentFaceUp;
  }

  // screen is up
  if (
    -2 < dataSmartphone[6] &&
    dataSmartphone[6] < 2 &&
    -2 < dataSmartphone[7] &&
    dataSmartphone[7] < 2 &&
    7 < dataSmartphone[8] &&
    dataSmartphone[8] < 11
  ) {
    currentFaceUp = listFaceUp[0];
    console.log("last currentFaceUp : " + lastFaceUp);
    console.log("currentFaceUp : " + listFaceUp[0]);
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
    currentFaceUp = listFaceUp[1];
    console.log("last currentFaceUp : " + lastFaceUp);
    console.log("currentFaceUp : " + listFaceUp[1]);
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
    currentFaceUp = listFaceUp[2];
    console.log("last currentFaceUp : " + lastFaceUp);
    console.log("currentFaceUp : " + listFaceUp[2]);
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
    currentFaceUp = listFaceUp[3];
    console.log("last currentFaceUp : " + lastFaceUp);
    console.log("currentFaceUp : " + listFaceUp[3]);
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
    currentFaceUp = listFaceUp[4];
    console.log("last currentFaceUp : " + lastFaceUp);
    console.log("currentFaceUp : " + listFaceUp[4]);
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
    currentFaceUp = listFaceUp[5];
    console.log("last currentFaceUp : " + lastFaceUp);
    console.log("currentFaceUp : " + listFaceUp[5]);
  }
  return currentFaceUp;
}

function compareFixedPositions() {}

function validate() {
  console.log("->  :  " + Math.abs(comparePositions[0]));
  let val0, val1, val2;
  val1 = Math.abs(comparePositions[0]);
  val2 = Math.abs(comparePositions[1]);
  val3 = Math.abs(comparePositions[2]);
  if ((val1 + val2 + val3) / 3 >= 50) {
    console.log("validate");
  }
  // if (
  //   lastFaceUp == currentFaceUp &&
  //   (Math.abs(deltaData[0]) + Math.abs(deltaData[1]) + Math.abs(deltaData[2])) *
  //     0.3 >
  //     5
  // ) {
  //   alert("validate");
  // }
}
