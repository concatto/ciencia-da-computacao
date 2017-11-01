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
  float velocidade;
  float aceleracao;
  float velMaxima;
  
  Nave(float velMaxima) {
    this->velMaxima = velMaxima;
    this->aceleracao = 0; // Uso do this é opcional
    this->velocidade = 0;
  }
  
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
