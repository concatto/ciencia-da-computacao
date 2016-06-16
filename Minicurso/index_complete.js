var http = require("http");
var io = require("socket.io");
var express = require("express");
var serial = require("serialport");
var app = express();
var server = http.createServer(app);
var serverSocket = io(server);

var port = new serial.SerialPort("/dev/ttyUSB0");

app.get("/", function(req, res) {
  res.sendFile(__dirname + "/index_socket.html");
});

var ligado = false;

serverSocket.on("connection", function(socket) {
  socket.on("teste", function() {
    if (ligado) {
      port.write([0]);
    } else {
      port.write([1]);
    }
    ligado = !ligado;
  });
});

server.listen(4000);
