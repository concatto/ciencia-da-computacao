var input, button, greeting;

function setup() {
	
  // create canvas
  createCanvas(710, 400);


  
  input = createInput();
  input.position(20, 5);
  console.log(input.size());
  
    greeting = createElement('h2', 'Tamanho inicial do tumor');
  greeting.position(20, 5);
  /*
    greeting = createElement('h2', 'Tamanho inicial do tumor');
  greeting.position(20, 25);
  
  input = createInput();
  input.position(20, 105);
  
    greeting = createElement('h2', 'Tamanho inicial do tumor');
  greeting.position(20, 45);
  
  input = createInput();
  input.position(20, 125);
  
    greeting = createElement('h2', 'Tamanho inicial do tumor');
  greeting.position(20, 65);
  
  input = createInput();
  input.position(20, 145);
  
    greeting = createElement('h2', 'Tamanho inicial do tumor');
  greeting.position(20, 85);
  
  input = createInput();
  input.position(20, 165);*/

  button = createButton('submit');
  button.position(input.x + input.width, 65);
  button.mousePressed(greet);



  textAlign(CENTER);
  textSize(50);
}

function greet() {
  var name = input.value();
  greeting.html('hello '+name+'!');
  input.value('');

  for (var i=0; i<200; i++) {
    push();
    fill(random(255), 255, 255);
    translate(random(width), random(height));
    rotate(random(2*PI));
    text(name, 0, 0);
    pop();
  }
}