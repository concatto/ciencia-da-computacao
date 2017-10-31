# Minicurso SFML

## Seção 1: Objetos

A declaração e utilização de classes é essencial para a programação orientada à objetos.
Através delas, é possível armazenar e manipular dados heterogêneos facilmente.
Em sua forma mais básica, uma classe consiste em uma coleção de variáveis armazenadas sob um identificador.

```c++
struct Nave {
  float velocidade;
  float aceleracao;
  float velMaxima;
};
```

Para materializar esta classe (isto é, *instanciar* a classe), basta criar uma variável do tipo Nave: `Nave nave;`
Tipicamente, é necessário instanciar uma classe com suas variáveis (*membros*) inicializadas com algum valor.
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

Entretanto, classes são mais do que mochilas que guardam variáveis. É possível também declarar funções.
Em C++, métodos são conhecidos como funções membro. (Sim, structs também suportam funções membro.)

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
