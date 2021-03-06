# Minicurso SFML

# Seção 1: Objetos

A declaração e utilização de classes é essencial para a programação orientada à objetos. Através delas, é possível armazenar e manipular dados heterogêneos facilmente. Em sua forma mais básica, uma classe consiste em uma coleção de variáveis armazenadas sob um identificador.

```c++
struct Nave {
  float velocidade;
  float aceleracao;
  float velMaxima;
};
```

Para materializar esta classe (isto é, *instanciar* a classe), basta criar uma variável do tipo Nave: `Nave nave;`. Suas variáveis (*membros*) podem ser acessadas através da forma `nave.<membro>`. Tipicamente, é necessário instanciar uma classe com seus membros inicializados com algum valor.
Solução: construtor.

```c++
struct Nave {
  float velocidade;
  float aceleracao;
  float velMaxima;
  
  Nave(float velMaxima) {
    this->velMaxima = velMaxima;
    this->aceleracao = 0; // Uso do this é opcional
    this->velocidade = 0;
  }
};
```
> Apresentar invocação do construtor.

Entretanto, classes são mais do que mochilas que guardam variáveis. É possível também declarar funções. Em C++, métodos são conhecidos como funções membro. (Sim, structs também suportam funções membro.)

```c++
struct Nave {
  // Declarações...
  
  void atualizarVelocidade() {
    // Acesso implícito aos membros da instância
    velocidade += aceleracao;
  }
};
```
> Apresentar invocação da função membro.

### Exercício: crie uma função que faça com que a nave pare de acelerar quando atingir a velocidade máxima ou mínima (0).
Solução:
```c++
void verificarVelocidade() {
  if (velocidade > velMaxima) {
    aceleracao = 0;
    velocidade = velMaxima;
  } else if (velocidade < 0) {
    aceleracao = 0;
    velocidade = 0;
  }
}
```

> Apresentar os métodos funcionando dentro do loop.

> O conteúdo a seguir deve ser passado rapidamente e acompanhado de prática! Função void imprimir(Nave).

Naturalmente, podemos construir funções (membro ou não) que aceitam instâncias de variáveis por parâmetro. Ao contrário de outras linguagens, o C++ oferece uma grande variedade de formas de declarar parâmetros, e a decisão de qual caminho seguir pode ter um profundo impacto no resultado do programa. Existem duas variações principais de tipos em C++: diretos e indiretos. Tipos diretos sempre realizarão uma cópia da instância, enquanto tipos indiretos apenas farão referência à instância especificada, sem realizar nenhuma cópia. Logo, é possível modificar o objeto original quando utilizamos tipos indiretos; é possível remover esta capacidade através do modificador `const` (constante).

> Durante a fala, mostrar passagem por valor, construtor de cópia, passagem por referência e const.

Como um bônus, as passagens por valor e const-referência permitem que invoquemos a função com uma *instância temporária*: uma instância anônima da classe que só existe durante o tempo de vida da função. Não é possível fazer o mesmo com referência (sem const), pois não há um objeto para fazer referência!

> Mostrar esse tipo de construção e falar sobre sf::VideoMode. Isto leva ao parágrafo seguinte...

A biblioteca SFML é completamente orientada a objetos; portanto, a criação e manipulação de elementos gráficos se dará
de maneira muito parecida com o que vimos até o momento. As classes da biblioteca, entretanto, estão localizadas no _namespace_ `sf`. Para que possamos acessá-los, podemos utilizar `using namespace sf;` no topo do arquivo ou prefixar as classes com `sf::`. Utilizaremos esta última estratégia, tanto por ser a prática recomendada quanto por facilitar a diferenciação de classes prontas com classes criadas por nós próprios.

> Falar sobre a estrutura do código base e como ele se assemelha ao que já vimos.

Estamos prontos para desenhar nosso primeiro objeto com a biblioteca SFML. Vamos desenhar um círculo.

### Exercício: crie uma instância da classe `sf::CircleShape`. O construtor espera um parâmetro: o raio do círculo. Desenhe-o com `janela.draw(...);`

Solução:
```c++
int main() {
  // Criação da janela
  sf::CircleShape circulo(30);
  
  while (janela.isOpen()) {
    janela.clear();
    janela.draw(circulo);
    janela.display();
  }
}
```

> Apresentar o objeto sendo desenhado.

# Seção 2: Entidades gráficas

A biblioteca SFML oferece diversos tipos de formas geométricas para serem desenhadas. Todas elas compartilham certos aspectos, como cor, textura e transformação. Este último é essencial para qualquer aplicação gráfica.

Transformações representam modificações na estrutura geométrica da entidade. As três transformações principais são: translação, escala e rotação. A primeira e provavelmente a mais importante especifica a localização do elemento no espaço, com o ponto (0, 0) indicando o canto superior esquerdo da janela. A posição dos objetos do SFML pode ser modificada através das funções membro `setPosition(x, y)` (absoluta) e `move(x, y)` (relativa).

> Mostrar a utilização de ambas as funções na prática.

### Exercício: fazer com que o objeto apareça no canto inferior direito e mova-se em uma diagonal para cima e para a esquerda.

Solução:
```c++
int main() {
  sf::RenderWindow janela(sf::VideoMode(1100, 900), "");
  janela.setFramerateLimit(60); // Fazer sem primeiro e depois adicionar.
  sf::CircleShape circulo(30);
  circulo.setPosition(1100, 900);
  
  while (janela.isOpen()) {
    janela.clear();
    circulo.move(-0.1, -0.1);
    janela.draw(circulo);
    janela.display();
  }
}
```

A rotação se comporta de maneira similar, com o par de funções `setRotation(graus)` e `rotate(graus)`. Entretanto, ambas utilizam graus ao invés de radianos (ao contrário da biblioteca padrão de matemática do C++). Lembre-se que 180 graus equivalem a π radianos.

> Mostrar rotação funcionando das duas maneiras. Não dá pra perceber porque é um círculo. `setPointCount(3);`

Perceba que a rotação está sendo aplicada com base no canto superior esquerdo do objeto. Esta é a sua _origem_. Podemos modificar esta característica definindo a origem como o centro do nosso círculo: `setOrigin(30, 30)`.

_Spiel sobre coordenadas polares_

### Exercício: mova o triângulo para o canto inferior esquerdo da tela e faça com que ele se mova constantemente com um ângulo de 320 graus (1 grau = π / 180 radianos).

Solução:
```c++
int main() {
  // Criação da janela
  sf::CircleShape circulo(30);
  circulo.setOrigin(30, 30);
  circulo.setScale(0.6, 1); // Durante a explicação
  circulo.setPointCount(3);
  circulo.setPosition(0, 900);
  
  float angulo = 320;
  float rad = angulo * (M_PI / 180);
  
  while (janela.isOpen()) {
    janela.clear();
    circulo.setRotation(angulo + 90); // Ponta estreita fica na direção da forma
    circulo.move(1.5 * cos(rad), 1.5 * sin(rad)); //Multiplicação representa a "velocidade"
    janela.draw(circulo);
    janela.display();
  }
}
```

Vamos aplicar estes passos na classe Nave que criamos anteriormente. Criaremos duas funções: `atualizar()`, que invoca as duas funções de atualização de velocidade e move a nave, e `orientar(graus)`, que define a direção da nave. Precisaremos adicionar dois campos: a entidade gráfica `sf::CircleShape forma` e a direção atual em graus `float direcao`.

### Exercício sustenido: realizar as mudanças necessárias para efetivar a proposta acima.

Solução:

```c++
struct Nave {
  sf::CircleShape forma;
  float direcao;
  // Outros membros
  
  Nave(float velMaxima) {
    this->velMaxima = velMaxima;
    forma.setRadius(30); // Alternativa ao construtor de CircleShape
    forma.setPointCount(3);
    forma.setOrigin(30, 30);
    forma.setScale(0.6, 1);
  }
  
  void orientar(float graus) {
    forma.setRotation(graus + 90);
    direcao = graus;
  }
  
  void atualizar() {
    atualizarVelocidade();
    verificarVelocidade();
    
    float rad = direcao * (M_PI / 180);
    forma.move(velocidade * cos(rad), velocidade * sin(rad));
  }
  
  // Declarações de atualizarVelocidade() e verificarVelocidade()
};
```

> Brincar um pouco com uma instância. Definir aceleração inicial.

Para deixar nossa vida significativamente mais fácil, podemos definir que a nave *é* um `sf::CircleShape`, ao invés de conter um membro que define sua forma. Basta usar herança! Para herdar uma classe em C++, basta complementar a declaração com dois pontos e a classe base, desta maneira: `struct Nave : sf::CircleShape`. Assim, podemos remover todas as menções da variável membro e substituir com `this->` (ou nada).

# Seção 3: Interação

Um jogo não seria um jogo se o jogador ficasse apenas observando as coisas acontecerem. Portanto, o SFML oferece maneiras de detectar entradas de um usuário tanto pelo mouse quanto pelo teclado, e até mesmo por joysticks.

A primeira maneira é a consulta do estado do dispositivo de interesse em tempo real. Essencialmente, são perguntas do tipo "este botão está pressionado?". Naturalmente, este tipo de expressão se transforma em funções que retornam `bool`. As principais são: `sf::Keyboard::isKeyPressed(tecla)`, onde tecla possui a forma `sf::Keyboard::<tecla>`, e `sf::Mouse::isButtonPressed(botão)`, onde botão é `sf::Mouse::Left`, `::Right` ou `::Middle`.

> Mostrar a detecção de um botão do teclado com `cout`.

### Exercício: faça com que o jogador possa controlar a direção da nave através das teclas A e D.

Solução:

```c++
// Dentro do while
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    nave.orientar(nave.direcao + 4);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    nave.orientar(nave.direcao - 4);
  }
```

### Exercício bemol: faça com que a nave possua aceleração positiva enquanto a tecla W estiver pressionada e negativa caso contrário.

Solução:

```c++
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    nave.aceleracao = 0.1;
  } else {
    nave.aceleracao = -0.1;
  }
```

A segunda maneira é através de um sistema completo de eventos, capaz de detectar cliques, pressionamentos de teclas e movimentos do mouse. Antes de qualquer outro tipo de evento, veremos um tratador para fechar a janela quando o botão "X" é clicado (finalmente!)

```c++
while (janela.isOpen()) {
  sf::Event evento;                           // Variável que armazena as informações do evento
  while (janela.pollEvent(evento)) {          // Caso um ou mais eventos ocorram, captura os dados em "evento"
    if (evento.type == sf::Event::Closed) {   // Se for um clique no botão "X"
      janela.close();                         // Fecha a janela
    }
  }
  
  // Resto
}
```

Vamos agora adicionar projéteis ao nosso jogo. Para simplificar, vamos considerar que nosso projétil é simplesmente um pequeno retângulo que se move em velocidade constante. Declare um retângulo chamado `projetil` com tamanho 10x4 e origem no centro. Em todo quadro, desenhe-o e mova-o um pouco para a direita e para baixo. Com este protótipo de projétil pronto, vamos tratar do evento de pressionamento da barra de espaço:

```c++
if (evento.type == sf::Event::KeyPressed) {
  if (evento.key.code == sf::Keyboard::Space) {
    projetil.setPosition(nave.getPosition());
  }
}
```

Porém, entre os diversos problemas que temos, o mais gritante é que o projétil sempre se move para a mesma direção.

### Exercício: corrija o comportamento supracitado. Utilize o poder da trigonometria.

Solução:

```c++
float anguloProjetil = 0;
while (janela.isOpen()) {
  // Ao definir a posição do projétil no tratador
    anguloProjetil = nave.direcao;

  float radProjetil = anguloProjetil * (M_PI / 180);
  projetil.move(10 * cos(radProjetil), 10 * sin(radProjetil));

  // Desenhar
}
```

Entretanto, continuamos com apenas um projétil, o que é bastante chato. Vamos resolver este problema com um conjunto de objetos: vector.

# Seção 4: Tópicos avançados

Vectors são equivalentes a ArrayLists em Java ou Lists em C#. Armazenam um conjunto arbitrariamente grande de objetos de tipo genérico (portanto, devem ser usados com _templates_), oferecendo operações de inserção, remoção, e acesso por índice. Antes de qualquer coisa, devemos inserir um `#include <vector>`. Para exemplificar, podemos criar um vector de números inteiros e adicionar alguns números através da função `push_back(valor)`. O argumento desta função é um objeto do mesmo tipo do vector. Agora, se quisermos mostrar o conteúdo do vector, será necessário percorrê-lo, visitando um elemento por vez. A maneira mais básica de realizar esta operação é com um simples `for (int i = 0; i < vec.size(); i++)` e acessar os elementos com `vec[i]`. Porém, quando desejamos visitar todos os elementos e não nos importamos com o índice de cada um deles, podemos utilizar o for-each, presente na linguagem a partir do C++11: `for (int valor : vec)`.

> Ir escrevendo enquanto fala, e mostrar a soma dos elementos no final.

Naturalmente, não estamos limitados a tipos primitivos, como inteiros ou números reais. Podemos criar vectors de qualquer tipo. Inclusive de entidades gráficas como `sf::CircleShape` ou `sf::RectangleShape`. Podemos, por exemplo, criar 10 retângulos com espaçamento uniforme e tamanho crescente, e depois desenhá-los a cada frame.

```c++
vector<sf::RectangleShape> retangulos;
for (int i = 0; i < 10; i++) {
  float tamanho = 10 + i * 5;

  // O construtor de RectangleShape define o tamanho do mesmo
  // Espera um Vector2f, que simplesmente armazena dois floats
  sf::RectangleShape r(sf::Vector2f(tamanho, tamanho));
  r.setPosition(20 + tamanho * i, 100);
  r.setFillColor(sf::Color::Red); // Altera a cor do retângulo

  retangulos.push_back(r);
}

while (...) {
  // Outras operações
  
  for (int i = 0; i < retangulos.size(); i++) {
    janela.draw(retangulos[i]);
  }
}
```

### Exercício sustenido: criar um vector de projéteis. Deve-se adicionar um projétil ao apertar a barra de espaço e, a cada frame, mover e desenhar todos os projéteis. Boa sorte.

Solução:

```c++
vector<sf::CircleShape> projeteis;

while (...) {
  sf::Event evento;
  while (janela.pollEvent(evento)) {
    if (evento.type == sf::Event::KeyPressed) {
      if (evento.key.code == sf::Keyboard::Space) {
        sf::RectangleShape projetil(sf::Vector2f(10, 4));
        projetil.setOrigin(5, 2);
        projetil.setPosition(nave.getPosition());
        projetil.setRotation(nave.direcao); // Serve para armazenar a direção também

        projeteis.push_back(projetil);
      }
    }
  }
    
  // Após janela.clear():
  for (int i = 0; i < projeteis.size(); i++) {
    // Surpresa! Referência não é só em parâmetros
    sf::RectangleShape& projetil = projeteis[i];

    // Translação definida a partir da rotação
    float projetilRad = projetil.getRotation() * (M_PI / 180);
    projetil.move(20 * cos(projetilRad), 20 * sin(projetilRad));

    janela.draw(projetil);
  }
}
```

Entretanto, nunca estamos removendo os projéteis, então nossa memória vai estar clamando por socorro após algum tempo. Logo, precisaremos verificar o retângulo da janela _contém_ o projétil em questão; caso não contenha, podemos removê-lo de nosso vector. Para isso, construiremos uma instância de `sf::FloatRect`, que representa um retângulo em memória, e não um objeto gráfico. Esta classe possui uma função membro `contains(ponto)`, que é perfeita para nosso problema atual. Seu construtor aceita quatro parâmetros: os dois primeiros definem a posição do canto superior esquerdo (x e y), e os dois últimos especificam seu tamanho (largura e altura). Utilizaremos (0, 0, 1100, 900).

```c++
sf::FloatRect retanguloJanela(0, 0, 1100, 900);

for (int i = 0; i < projeteis.size(); i++) {
  sf::CircleShape& projetil = projeteis[i];

  if (retanguloJanela.contains(projetil.getPosition())) {        
    // Desenhar
  } else {
    projeteis.erase(projeteis.begin() + i); // Remover o elemento do vector
  }
}
```

Porém, ao removermos um elemento de um vector, todos os elementos à sua frente dão um passo para trás. Temos duas escolhas para tratar disso: a primeira é realizar uma instrução de `i--;` após a remoção de um elemento, e a segunda é inverter a ordem do nosso loop: `for (int i = projeteis.size() - 1; i >= 0; i--)`. Escolha aquela que preferir.

Para tornar nosso jogo mais divertido, vamos permitir que o jogador mantenha a barra de espaço pressionada para atirar projéteis continuamente. Primeiramente, vamos precisar desacoplar a criação de projéteis do evento KeyPressed, substituindo por uma verificação em tempo real com `sf::Keyboard::isKeyPressed(sf::Keyboard::Space)`. Subsequentemente, precisaremos de algum tipo de relógio para verificar quanto tempo se passou desde o último tiro. A resposta para esta situação é a classe `sf::Clock`, que possui duas funções membro: `restart()`, que reinicia a contagem de tempo, e `getElapsedTime()`, que retorna quanto tempo se passou com uma instância de `sf::Time`, que por sua vez possui as funções membro `asMicroseconds()`, `asMilliseconds()` e `asSeconds()`.

### Exercício: faça com o jogador só possa atirar uma vez a cada 100 milissegundos.

Solução:
```c++
sf::Clock relogio;
while (...) {
  // Outras ações
  
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    if (relogio.getElapsedTime().asMilliseconds() > 100) {
      sf::RectangleShape projetil(sf::Vector2f(10, 4));
      projetil.setOrigin(5, 2);
      projetil.setPosition(nave.getPosition());
      projetil.setRotation(nave.direcao);

      projeteis.push_back(projetil);
      relogio.restart();
    }
  }
}
```

Para adicionar um pouco de dificuldade ao jogo, vamos criar asteroides aleatoriamente de vez em quando. Temos todas as ferramentas necessárias para isso.

### Exercício sustenido: a cada segundo, faça com que um asteroide (retângulo 70x70) apareça em uma posição aleatória na tela.

Solução: 

```c++
vector<sf::RectangleShape> asteroides;
sf::Clock relogioAsteroide;

while (...) {
  if (relogioAsteroide.getElapsedTime().asSeconds() > 0.5) {
    relogioAsteroide.restart();

    sf::RectangleShape asteroide(sf::Vector2f(70, 70));
    asteroide.setPosition(rand() % 1100, rand() % 900);
    asteroide.setFillColor(sf::Color::Red);

    asteroides.push_back(asteroide);
  }
  
  // O uso de referência evita uma cópia desnecessária!
  for (sf::RectangleShape& asteroide : asteroides) {
    janela.draw(asteroide);
  }
}
```

Agora, a adição de colisões se torna bastante simples. Existem técnicas mais sofisticadas, mas basicamente o procedimento consiste em verificar se, para cada projétil na tela, há uma intersecção com um asteroide (retângulo); caso haja, removemos tanto o projétil quanto o asteroide de seus respectivos vectors. Usaremos a técnica de iteração reversa para a remoção dos elementos, e usaremos as funções `getGlobalBounds()` para obter o retângulo que envolve o elemento e `intersects(retangulo)`, uma função membro de `sf::FloatRect`, para verificar se existe uma intersecção entre dois retângulos.

```c++
for (int i = asteroides.size() - 1; i >= 0; i--) {
  for (int j = projeteis.size() - 1; j >= 0; j--) {
    // Se houver intersecção
    if (asteroides[i].getGlobalBounds().intersects(projeteis[j].getGlobalBounds())) {
      projeteis.erase(projeteis.begin() + j);
      asteroides.erase(asteroides.begin() + i);

      break;
    }
  }
}
```

### Exercício: faça com que o programa termine quando a nave colidir com um asteroide.

Solução:

```c++
for (int i = asteroides.size() - 1; i >= 0; i--) {
  // Testes de colisão com projéteis
  
  if (nave.getGlobalBounds().intersects(asteroides[i].getGlobalBounds())) {
    return;
  }
}
```

Para finalizar, vamos adicionar texturas ao nosso jogo. Para trabalharmos com texturas no SFML, precisamos de dois passos distintos: primeiro, devemos carregar a textura propriamente dita para a GPU, através da classe `sf::Texture` e suas funções membro. Posteriormente, precisamos desenhar a textura; esta parte pode ser realizada pela utilização da classe `sf::Sprite`, que consiste em uma entidade gráfica especializada em desenhar textures, ou pelo emprego das formas geométricas, que já conhecemos, as quais possuem uma função membro para definir textura. Vamos utilizar um Sprite para desenhar o plano de fundo.

```c++
sf::Texture texturaFundo;
texturaFundo.loadFromFile("universe.jpg"); // Lê um arquivo de imagem e transfere para a memória da GPU

sf::Sprite spriteFundo;
spriteFundo.setTexture(texturaFundo);

while (...) {
  // Outras operações
  
  janela.draw(spriteFundo); // Desenhar o sprite, não a textura!
}
```

Com o plano de fundo, vamos partir para nosso último passo: aplicar uma textura nos projéteis. Isso demandará algumas adaptações, pois nossos projéteis atualmente são definidos como `sf::CircleShape`. Entretanto, os sprites suportam grande parte das operações que formas geométricas oferecem, com poucas exceções. Uma delas é a definição do raio (afinal, um sprite não é um círculo!), então a invocação do construtor e consequentemente a definição da origem deverão ser modificadas. Primeiramente, vamos trocar o tipo de nosso vector de projéteis para `vector<sf::Sprite>`, fazendo com que ele passe a armazenar sprites ao invés de círculos. O bloco de código de criação também deverá ser modificado, mudando o tipo de variável para `sf::Sprite` e removendo a chamada do construtor. Remova também o `setOrigin()`; posteriormente iremos utilizá-lo de outra maneira. Por fim, altere o tipo da variável no trecho de código que verifica se os projéteis ainda estão dentro dos limites da tela e desenha-os.

### Exercício final: carregue a textura "shot.png". Faça com que os projéteis usem esta textura. Faça também com que a origem dos projéteis seja automaticamente definida para o centro da textura.

Solução:

```c++
sf::Texture texturaProjetil;
texturaProjetil.loadFromFile("shot.png");

while (...) {
  // Outras coisas
  
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    if (relogio.getElapsedTime().asMilliseconds() > 100) {
      // Carregar a textura nesse ponto abriria as portas para espíritos malignos!!!
    
      sf::Sprite projetil;
      projetil.setTexture(texturaProjetil);
      projetil.setOrigin(texturaProjetil.getSize().x / 2.0, texturaProjetil.getSize().y / 2.0);
      
      // Mais coisas
    }
  }
  
  // Resto das coisas
}
```
