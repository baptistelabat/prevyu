var Datas = require('dataviz-tangible');

var datas = new Datas({
    forecast: 'myAPIKey',//Replace with user API key from https://developer.forecast.io/
});


// définir comment gérer la réponse du service météo

datas.on('weather', function(data) {
    console.log("Send" + data.hourly.data[0].precipIntensity + "in./hr");
    serialPort.write(data.hourly.data[0].precipIntensity/0.4*255 +"\n");//Normalised to 0-255
});

datas.weather('Nantes');

var openFlag;
var date = new Date()
//console.log(date.getSeconds());

// ouvrir un port série
var SerialPort = require("serialport").SerialPort
var serialPort = new SerialPort("/dev/ttyACM1", {
  baudrate: 9600
});

serialPort.on("open", function () {
  openFlag = true;
  console.log("Open");
});

serialPort.on('data', function(data){
  console.log("Received "+ data);
});

var timer = setInterval(function() {
	if (openFlag)
	{
		// lancer un appel au service météo
		datas.weather('Nantes');
	}

 }, 1000)//10seconds






