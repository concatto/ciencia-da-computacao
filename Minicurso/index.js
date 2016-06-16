var express = require("express");
var SerialPort = require("serialport").SerialPort;
var http = require("http");
var io = require("socket.io");

var app = express();
var server = http.createServer(app);
var socketServer = io(server);

app.get("/", function(req, res) {
  res.sendFile(__dirname + "/index.html");
});

server.listen(4000);