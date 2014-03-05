var Datas = require('dataviz-tangible');

var datas = new Datas({
    forecast: 'myAPIKey',//Replace with user API key from https://developer.forecast.io/
});

// définir comment gérer la réponse du service météo

datas.on('weather', function(data) {
	var unix_time=Date.now()/1000.0;
	var interp = (unix_time -data.hourly.data[0].time)/( data.hourly.data[1].time - data.hourly.data[0].time)*(data.hourly.data[1].precipIntensity-data.hourly.data[0].precipIntensity) + data.hourly.data[0].precipIntensity
    console.log("Send" + interp + "in./hr");
    serialPort.write(interp/0.4*255 +"\n");//Normalised to 0-255
});

datas.weather('Nantes');

var openFlag;

// ouvrir un port série
var SerialPort = require("serialport").SerialPort
var serialPort = new SerialPort("/dev/ttyACM0", {
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

 }, 120000)//120seconds





