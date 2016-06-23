var io = require("socket.io");
var express = require("express");
var http = require("http");

var app = express();
var server = http.createServer(app);
var serverSocket = io(server);

app.use(express.static("pagina"));

serverSocket.on("connection", function(socket) {
	socket.on("mensagem", function(dados) {
		console.log(parseInt(dados[0]) + 10);
	});
});


server.listen(4000);
