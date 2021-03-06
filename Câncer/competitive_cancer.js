	var nDose = 1;
	var url = "http://127.0.0.1:5000/";
	var cancerAlpha = 2;
	var normalAlpha = 3;
	var meanSlider;
	var initialY = 2.5;
	var postData = {};
	var initialX = 5000;
	var t = 0;
	var y = initialY; // Cancerous biomass
	var x = initialX; // Normal biomass*/
	var lambda1 = 0.003; // Impact of cancerous cells in normal biomass
	var lambda2 = 0.00002; // Reduction in cancerous biomass from normal cells
	var r1 = 0.212;
	var prevT = 0;
	var r2 = 0.42;
	var K1 = 5000;
	var K2 = 50;
	var h = 0.1;
	var prevY;
	var negativeXIncrease = 0;
	var negativeYIncrease = 0;
	var accY = initialY;
	var accX = initialX;
	var xOrigin = 400;
	var yOrigin = 400;
	var maxDistance;
	var cells = [];
	var normalCells = [];
	var normalPoints = [];
	var tumorPoints = [];
	var wallSize = 10;
	var currentDistance = 0;
	var scatterCoefficient = 230; // Controls the final radius of the tumor
	var buttonRunPressed = false;
	
	// take a look at
	var wallIncrease = scatterCoefficient * (1 / K2);
	var maxWallDistance = K2 * wallIncrease;
	
	
	var period = 2;
	var dose = 0.2;


	function setup(teste, teste) {
		maxDistance = min([xOrigin, yOrigin]);
		createCanvas(2000, 1000);
		frameRate(120);
		colorMode(HSB, 360, 100, 100, 1);
		noStroke();
		smooth();

		inputInitialY = createInput();
		inputInitialY.position(0, 30);
		
		inputInitialX = createInput();
		inputInitialX.position(200, 30);
		
		inputLambda1 = createInput();
		inputLambda1.position(400, 30);
		
		inputLambda2 = createInput();
		inputLambda2.position(600, 30);

		inputR1 = createInput();
		inputR1.position(800, 30);

		inputR2 = createInput();
		inputR2.position(1000, 30);

		inputK1 = createInput();
		inputK1.position(0, 80);

		inputK2 = createInput();
		inputK2.position(200, 80);

		inputPeriod = createInput();
		inputPeriod.position(400, 80);

		inputDose = createInput();
		inputDose.position(800, 80);

		inputCancerAlpha = createInput();
		inputCancerAlpha.position(1000, 80);

		inputNormalAlpha = createInput();
		inputNormalAlpha.position(1200, 80);

		buttonRun = createButton('Run');
 		buttonRun.position(0, 110);

		buttonStop = createButton('Stop');
 		buttonStop.position(60, 110);

 		putText();
	}

	function putText() {
		textSize(12);
		text("Initial Cancer Cells", 0, 10);
		text("Initial Normal Cells", 200, 10);
		text("Impact of Cancerous Cell", 400, 10);
		text("Reduction in Cancerous", 600, 10);
		text("Normal Cells Growth Rate", 800, 10);
		text("Cancerous Cells Growth Rate", 1000, 10);
		text("Carrying Capacity Normal Cells", 0, 60);
		text("Carrying Capacity Cancerous Cells", 200, 60);
		text("Period", 400, 60);
		text("Dose", 600, 60);
		text("Cancer Alpha", 1000, 60);
		text("Normal Alpha", 1200, 60);
		textSize(32);
	}

	// r is the growth factor of x1. lambda is the impact of x2 on x1. K is the carrying capacity of x1 (i.e. maximum value)
	function competitiveGrowth(r, x1, x2, K, lambda) {
		return r * x1 * (1 - (x1 / K) - lambda * x2);
	}

	function applyChemotherapy(doseAlpha, dose, isNormalCell) {
		var survivalFraction = Math.exp(-doseAlpha * dose);
		var deadCells;
		if(isNormalCell){
			deadCells = x - (x * survivalFraction);
			x -= deadCells;
		}else {
			deadCells = y - (y * survivalFraction);
			
			y -= deadCells;
		}
		return deadCells;
	}

	function killCells(amount, isNormalCell) {
		var integerPortion = Math.floor(amount);
		var fractionalPortion = amount - integerPortion;
		if(isNormalCell){
			accX -= fractionalPortion;
			for (var i = 0; i < integerPortion; i++) {
				var index = Math.floor(random(normalCells.length));
				normalCells.splice(index, 1);
				//currentDistance -= wallIncrease;
				maxWallDistance -= wallIncrease;
			}
		}else {
			accY -= fractionalPortion;

			for (var i = 0; i < integerPortion; i++) {
				var index = Math.floor(random(cells.length));
				cells.splice(index, 1);
				
				//currentDistance -= wallIncrease;
				maxWallDistance -= wallIncrease;
			}
		}
	}
	

	function draw() {

		buttonRun.mousePressed(() => {
 			/*initialY = inputInitialY.value(); // initial cancer biomass
			initialX = inputInitialX.value(); // initial normal cells biomass
			lambda1 = inputLambda1.value(); // Impact of cancerous cells in normal biomass
			lambda2 = inputLambda2.value(); // Reduction in cancerous biomass from normal cells
			r1 = inputR1.value(); // normal cells growth rate
			r2 = inputR2.value(); // cancerous cells growth rate
			K1 = inputK1.value(); // Carrying capacity of normal cells
			K2 = inputK2.value(); // Carrying capacity of cancerous cells
			period = inputPeriod.value();
			dose = inputDose.value();
			nDose = inputNDose.value();
			cancerAlpha = inputCancerAlpha.value();
			normalAlpha = inputNormalAlpha.value();*/
/*
			initialY = 1;
			initialX = 3000;
			lambda1 = 0.003;
			lambda2 = 0.00002;
			r1 = 1.5;
			r2 = 1.5;
			K1 = 3000;
			K2 = 3000;
			period = 2;
			dose = 0.2;
			nDose = 1;
			cancerAlpha = 2;
			normalAlpha = 2;
			*/

			//APLICACAO SEM COMPETICAO
			/*initialY = 2.5;
			initialX = 5000;
			lambda1 = 0;
			lambda2 = 0;
			r1 = 0.000106;
			r2 = 0.00021;
			K1 = 5000;
			K2 = 50;
			period = 5;
			nDose = 0;
			dose = 0;
			cancerAlpha = 0;
			normalAlpha = 0;*/

			//APLICACAO COM COMPETICAO
			/*initialY = 2.5;
			initialX = 5000;
			lambda1 = 0.000356;
			lambda2 = -0.0001875;
			r1 = 0.000106;
			r2 = 0.00021;
			K1 = 5000;
			K2 = 50;
			period = 5;
			nDose = 0;
			dose = 0;
			cancerAlpha = 0;
			normalAlpha = 0;*/
			/*
			initialY = 2.5;
			initialX = 5000;
			lambda1 = 0.000356;
			lambda2 = -0.0001875;
			r1 = 0.000106;
			r2 = 0.00021;
			K1 = 5000;
			K2 = 50;
			period = 5;
			nDose = 0;
			dose = 0;
			cancerAlpha = 0;
			normalAlpha = 0;*/

			/*t = 0;
			y = initialY; // Cancerous biomass
			x = initialX; // Normal biomass
			h = 0.01;
			negativeXIncrease = 0;
			negativeYIncrease = 0;
			accY = initialY;
			accX = initialX;
			xOrigin = 400;
			yOrigin = 400;
			maxDistance;
			cells = [];
			normalCells = [];
			normalPoints = [];
			tumorPoints = [];
			wallSize = 10;
			currentDistance = 0;
			scatterCoefficient = 230; // Controls the final radius of the tumor*/

			buttonRunPressed = true;
		});

 		buttonStop.mousePressed(() => {
 			buttonRunPressed = false;
 			putText();
 		});

 		if (buttonRunPressed) {
 			init();
 		}
	} 

	function init(){
		clear();
		putText();
		var increaseX = (h * competitiveGrowth(r1, x, y, K1, lambda1));
		var increaseY = (h * competitiveGrowth(r2, y, x, K2, lambda2));
		
		if (t > nDose * period) {
			var normalKillCount = applyChemotherapy(normalAlpha, dose, true);
			var cancerKillCount = applyChemotherapy(cancerAlpha, dose, false);
			killCells(normalKillCount, true);
			killCells(cancerKillCount, false);
			nDose++;
		}
		if(increaseX < 0){
			negativeXIncrease += increaseX;

		}else{
			accX += increaseX;
		}
		if(increaseY < 0){
			negativeYIncrease = increaseY;

		}else{
			accY += increaseY;
		}

		if(negativeXIncrease * -1 > 1){
			for (var i = 0; i < negativeXIncrease * -1; i++) {
				var index = Math.floor(random(normalCells.length));
				normalCells.splice(index, 1);
				maxWallDistance -= wallIncrease;
				negativeXIncrease += 1;
			}
			
		}
		
		if(negativeYIncrease * -1 > 1){
			for (var i = 0; i < negativeYIncrease *-1; i++) {
				var index = Math.floor(random(cells.length));
				cells.splice(index, 1);
				maxWallDistance -= wallIncrease;
				negativeYIncrease += 1;
			}
			
		}
		
		x += increaseX;
		y += increaseY;
	
		while (accY > 1) { // Cria c�lulas cangerigenas
			// Create a new cell for each whole number
			var angle = random(TWO_PI);
			var distance = random(currentDistance, currentDistance + wallSize);

			cells.push({
				x: xOrigin + distance * cos(angle),
				y: yOrigin + distance * sin(angle),
				distance: distance,
				hue: random(30)
			});
			accY--;
			maxWallDistance += wallIncrease;
			//currentDistance += wallIncrease;
		}
		
		while (accX > 1) { // Cria c�lulas saud�veis
			// Create a new cell for each whole number
			var angle = random(TWO_PI);
			var distance = random(currentDistance, currentDistance + wallSize);

			normalCells.push({
				x: xOrigin + distance * cos(angle),
				y: yOrigin + distance * sin(angle),
				distance: distance,
				hue: random(30)
			});

			accX--;
			//currentDistance += wallIncrease;
			maxWallDistance += wallIncrease;
		}
		/*
		x = normalCells.length;
		y = cells.length;*/
		var maxY = max([K1, K2]);
		insertPoint(normalPoints, x, initialX, maxY, true);
		insertPoint(tumorPoints, y, initialY, maxY, false);

		drawElements();
		text("Celulas normais " + x , 800, 600);
		text("Celulas cancerigenas " + y, 800, 700);
		
			
		t = t + h;

		if(t - prevT >= 1){
			//postData = {x: x, y: y, t: t, h: h, dose: dose, period: period};
			postData = {y: y*2000};
			prevT = t;
			httpPost(url, 'JSON', postData, function(arg){
				console.log(arg);
			});		
		}
	}

	function insertPoint(points, value, initial, maxValue, isNormal) {
		var xc = map(t, 0, 100, 0, width);
		var yc = map(value, 0, maxValue, 500, 100);

		points.push({
			x: xc + (2 * maxDistance) + 20,
			y: yc,
			hue: isNormal ? 120 : 300
		});
	}

	function drawElements() {
		// Draw chart
		[normalPoints, tumorPoints].forEach(function(points) {
			for (var i = 0; i < points.length; i++) {
				var p = points[i];
				stroke(p.hue, 100, 100, 1);
				if (i == 0) {
					point(p.x, p.y);
				} else {
					var prevP = points[i - 1];
					line(prevP.x, prevP.y, p.x, p.y); 
				}
			}
		});
		
		// Draw normal cells
		
		for (var i = normalCells.length - 1; i >= 0; i--) {	 // Desenha c�lulas normais	
			var cell = normalCells[i];

			var fromWall = currentDistance - cell.distance;
			var hue = 360;
			var brightness = 100;
			// Core starts to turn necrotic when the wall reaches 80% of its size
			var threshold = maxWallDistance * 0.8;

			if (fromWall > threshold) {
				hue = map(fromWall, threshold, maxWallDistance, 360, 270);
				brightness = map(fromWall, threshold, maxWallDistance, 100, 0);
			}

			var radius = map(cell.distance, 0, maxWallDistance, 10, 20);

			noStroke();
			//fill(hue - cell.hue, 100, brightness, 1);
			fill(137, 244, 66);
			ellipse(cell.x, cell.y, 10, 10);

			var movement = map(fromWall, 0, maxWallDistance, 3, 1);
			normalCells[i].x += random(-movement, movement);
			normalCells[i].y += random(-movement, movement);
		}
		
		// Draw cancerous cells
		
		for (var i = cells.length - 1; i >= 0; i--) { // Desenha c�lulas cancerigenas
			var cell = cells[i];

			var fromWall = currentDistance - cell.distance;
			var hue = 360;
			var brightness = 100;
			// Core starts to turn necrotic when the wall reaches 80% of its size
			var threshold = maxWallDistance * 0.8;

			if (fromWall > threshold) {
				hue = map(fromWall, threshold, maxWallDistance, 360, 270);
				brightness = map(fromWall, threshold, maxWallDistance, 100, 0);
			}

			var radius = map(cell.distance, 0, maxWallDistance, 10, 20);

			noStroke();
			//fill(hue - cell.hue, 100, brightness, 1);
			fill(0, 0, 0);
			ellipse(cell.x, cell.y, 10, 10);

			var movement = map(fromWall, 0, maxWallDistance, 3, 1);
			cells[i].x += random(-movement, movement);
			cells[i].y += random(-movement, movement);
		}
		
	}
