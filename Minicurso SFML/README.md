# Minicurso SFML

## Seção 1: Objetos

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

## Seção 2: Entidades gráficas

A biblioteca SFML oferece diversos tipos de formas geométricas para serem desenhadas. Todas elas compartilham certos aspectos, como cor, textura e transformação. Este último é essencial para qualquer aplicação gráfica.

Transformações representam modificações na estrutura geométrica da entidade. As três transformações principais são: translação, escala e rotação. A primeira e provavelmente a mais importante especifica a localização do elemento no espaço, com o ponto (0, 0) indicando o canto superior esquerdo da janela. A posição dos objetos do SFML pode ser modificada através das funções membro `setPosition(x, y)` (absoluta) e `move(x, y)` (relativa).

> Mostrar a utilização de ambas as funções na prática.

### Exercício: fazer com que o objeto apareça no canto inferior direito e mova-se em uma diagonal para cima e para a esquerda.

Solução:
```c++
int main() {
  sf::RenderWindow janela(sf::VideoMode(800, 600), "");
  janela.setFramerateLimit(60); // Fazer sem primeiro e depois adicionar.
  sf::CircleShape circulo(30);
  circulo.setPosition(800, 600);
  
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
  circulo.setPosition(0, 600);
  
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

## Seção 3: Interação

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

Vamos agora adicionar projéteis ao nosso jogo. Para simplificar, vamos considerar que nosso projétil é simplesmente um pequeno círculo que se move em velocidade constante. Declare um círculo chamado `projetil` com raio 7 e origem no centro. Em todo quadro, desenhe-o e mova-o um pouco para a direita e para baixo. Com este protótipo de projétil pronto, vamos tratar do evento de pressionamento da barra de espaço:

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

Vector é
