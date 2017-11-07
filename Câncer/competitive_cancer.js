
	var nDose = 1;
	var cancerAlpha = 2;
	var normalAlpha = 3;
	var meanSlider;
	var initialY = 1;
	var initialX = 3000;
	var t = 0;
	var y = initialY; // Cancerous biomass
	var x = initialX; // Normal biomass*/
	var lambda1 = 0.003; // Impact of cancerous cells in normal biomass
	var lambda2 = 0.00002; // Reduction in cancerous biomass from normal cells
	var r1 = 1.5;
	var r2 = 1.5;
	var K1 = 3000;
	var K2 = 2000;
	var h = 0.01;
	var prevY;
	//var totalX = initialX;
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
	
	// take a look at
	var wallIncrease = scatterCoefficient * (1 / K2);
	var maxWallDistance = K2 * wallIncrease;
	
	
	var period = 2;
	var dose = 0.2;


	function setup(teste, teste) {
		var input = createInput();
		input.position(20, 65);
		maxDistance = min([xOrigin, yOrigin]);

		createCanvas(2000, 1000);
		frameRate(120);
		colorMode(HSB, 360, 100, 100, 1);
		noStroke();
		smooth();

		meanSlider = createSlider(-100, 100, 0);
		meanSlider.position(width + 30, 30);
		meanSlider.style("width", "100px");

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
			//x = x - deadCells;
		}else {
			deadCells = y - (y * survivalFraction);
			//y = y - deadCells;
		}

		return deadCells;
	}

	// Arthur -- Mata os dois tipos de célula baseado no boolean (segundo parâmetro) isNormalCell
	// Prestar atenção no currentDistance, tem algo errado com ele, não necessáriamente nessa função, pode ser em outra..
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
		clear();

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
			for (var i = 0; i < increaseX*-1; i++) {
				var index = Math.floor(random(normalCells.length));
				normalCells.splice(index, 1);
				currentDistance -= wallIncrease;
			}
		}	
		if(increaseY < 0){
			for (var i = 0; i < increaseY *-1; i++) {
				var index = Math.floor(random(cells.length));
				cells.splice(index, 1);
				currentDistance -= wallIncrease;
			}
		}
		
		accX += increaseX;
		accY += increaseY;
	
	while (accY > 1) { // Cria células cangerigenas
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
	
	while (accX > 1) { // Cria células saudáveis
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
	
	x = normalCells.length;
	y = cells.length;
	
	var maxY = max([K1, K2]);
		insertPoint(normalPoints, x, initialX, maxY, true);
		insertPoint(tumorPoints, y, initialY, maxY, false);

		drawElements();
		text("Celulas normais " + Math.floor(normalCells.length), 800, 600);
		text("Celulas cancerigenas " + Math.floor(cells.length), 800, 700);
			
		t = t + h;
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
		
		for (var i = normalCells.length - 1; i >= 0; i--) {	 // Desenha células normais	
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
		for (var i = cells.length - 1; i >= 0; i--) { // Desenha células cancerigenas
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