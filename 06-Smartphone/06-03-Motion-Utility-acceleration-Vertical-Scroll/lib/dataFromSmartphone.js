var socket = io("http://localhost:9079/utility");
var dataSmartphone = [];
var deltaData = [];
var storedDataSmartphone = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var highVal = [];
var lowVal = [];
var deltaList = {};

socket.on("connect", function () {
  console.log("Connected…");
});

socket.on("sendDataToDashboard", insertText);
function insertText(data) {
  for (var i = 0; i < data.data.value.length; i++) {
    dataSmartphone[i] = data.data.value[i];
    deltaData[i] = storedDataSmartphone[i] - dataSmartphone[i];
    storedDataSmartphone[i] = dataSmartphone[i];
    if (getMin(deltaData[4]) < 0 && getMax(deltaData[4]) > 0) {
      console.log("min : " + getMin(deltaData[4]));
      // console.log("max : " + getMax(deltaData[4]));
      // console.log("delta : " + deltaData[4]);
    }
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
function getMax(d) {
  if (Math.max(d) > 0) {
    var maxval = Math.max(d);
  }

  return maxval;
}
function getMin(d) {
  if (Math.min(d) < 0) {
    var minval = Math.min(d);
  }
  return minval;
}
