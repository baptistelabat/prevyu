var Datas = require('../datas');

var datas = new Datas({
    forecast: 'c5c0d073778e5ab9e79a841b00e55f88',
});


// définir comment gérer la réponse du service météo
datas.on('weather', function(data) {
    console.log("Send" + data.hourly.data[0].precipIntensity + "in./hr");
    serialPort.write(data.hourly.data[0].precipIntensity/0.4*255);//Normalised to 0-255
});

datas.weather('Nantes');

var openFlag;
var date = new Date()
console.log(date.getSeconds());

// ouvrir un port série
var SerialPort = require("serialport").SerialPort
var serialPort = new SerialPort("/dev/ttyACM3", {
  baudrate: 9600
});

serialPort.on("open", function () {
  openFlag = true;
  console.log("Open");
});

serialPort.on('data', function(data){
  console.log("Received"+ data);
});

var timer = setInterval(function() {
	if (openFlag)
	{
		// lancer un appel au service météo
		datas.weather('Nantes');
	}

 }, 120000)//10seconds







