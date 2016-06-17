var http = require("http");
var express = require("express");

var app = express();
var server = http.createServer(app);

app.get("/", function(req, res) {
  res.sendFile(__dirname + "/index_socket.html");
});

server.listen(4000);
