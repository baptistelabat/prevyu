var ws = new WebSocket("ws://"+window.location.host+":8000/websocket");
ws.onmessage = function(evt){
	myOutput.value = evt.data;
}

function sendRain(){
  var msg = {
    type: "message",
    value:  document.getElementById("RainNumber").value,
    id:   "Rain",
    date: Date.now()
  };

  // Send the msg object as a JSON-formatted string.
  ws.send(JSON.stringify(msg));
}
function updateRainRange(){
//get elements
var myRange = document.getElementById("RainRange");
var myNumber = document.getElementById("RainNumber");
//copy the value over
myNumber.value = myRange.value;
sendRain();
} // end function

function updateRainNumber(){
//get elements
var myRange = document.getElementById("RainRange");
var myNumber = document.getElementById("RainNumber");
//copy the value over
myRange.value = myNumber.value;
sendRain();
} // end function


ws.onmessage = function(evt){
	var myOutput = document.getElementById("serverFeedback");
	myOutput.value = evt.data;
}




