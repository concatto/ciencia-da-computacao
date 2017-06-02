var http = require("http");
var io = require("socket.io");
var express = require("express");
var serial = require("serialport");
var app = express();
var server = http.createServer(app);
var serverSocket = io(server);

var port = new serial.SerialPort("/dev/ttyUSB0");
app.use(express.static("public"));

port.on("data", function(dados) {
  console.log(dados[0]);
  serverSocket.emit("luz", {valor: dados[0]});
});


server.listen(4000);
