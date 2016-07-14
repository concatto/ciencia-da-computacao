var http = require("http");
var express = require("express");

var app = express();
var server = http.createServer(app);

//app.use(express.static("pagina"));
app.get("/", function(req, res) {
  res.sendFile(__dirname + "/index_basic.html");
});

server.listen(4000);
