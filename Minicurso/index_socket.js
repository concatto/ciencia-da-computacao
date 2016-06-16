var http = require("http");
var io = require("socket.io");
var express = require("express");

var app = express();
var server = http.createServer(app);
var serverSocket = io(server);

app.get("/", function(req, res) {
  res.sendFile(__dirname + "/index_socket.html");
});

serverSocket.on("connection", function(socket) {
  socket.on("teste", function() {
    console.log("Mensagem recebida");
  });
});

server.listen(4000);
