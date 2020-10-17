var socket = io("http://localhost:9079/utility");

var variableOrientation01 = "";
var variableOrientation02 = "";
var variableOrientation03 = "";

socket.on("sendDataToDashboard", insertText);
function insertText(data) {
  variableOrientation01 = data.data.value[0];
  variableOrientation02 = data.data.value[1];
  variableOrientation03 = data.data.value[2];
  variableOrientation04 = data.data.value[3];
  variableOrientation05 = data.data.value[4];
  variableOrientation06 = data.data.value[5];
  variableOrientation07 = data.data.value[6];
  variableOrientation08 = data.data.value[7];
  variableOrientation09 = data.data.value[8];
  variableOrientation10 = data.data.value[9]; //shake
}

// -------------------------- Functions Library -------------------------- //
// --- Map
function map_range(value, low1, high1, low2, high2) {
  return low2 + ((high2 - low2) * (value - low1)) / (high1 - low1);
}

// --- Timer
function timer() {}

// --- Clockwise sense
function clockwise() {}
