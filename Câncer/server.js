const express = require("express");
const bodyParser = require("body-parser");
const json2csv = require("json2csv");
const app = express();
const fs = require("fs");
const fields = ["y", "t"];

var enableCors = function(req, res, next) {
	res.header('Access-Control-Allow-Origin', '*');
	res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE,OPTIONS');
	res.header('Access-Control-Allow-Headers', 'Content-Type, Authorization, Content-Length, X-Requested-With');

	next();
};

app.use(bodyParser.json());
app.use(enableCors);

app.post("/", (req, res) => {
	//console.log(req.body);
	fs.appendFileSync("chemo2.csv", json2csv({data: req.body, fields: fields, hasCSVColumnTitle: false}) + "\n");
	res.status(200).send(true);
});

app.listen(5000);
