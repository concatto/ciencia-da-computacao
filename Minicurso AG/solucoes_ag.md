## Geração de população inicial

```cpp
// Para cada i em tamanhoPopulacao
Solucao individuo;

for (int j = 0; j < problema.importancias.size(); i++) {
    individuo.bits[j] = std::rand() % 2;
//  individuo.bits[j] = std::round(gerarAleatorio());
//  individuo.bits[j] = (gerarAleatorio() < 0.5) ? 0 : 1;
}

individuo.aptidao = avaliar(individuo);
populacao.push_back(individuo);
```

## Seleção por torneio

```cpp
std::vector<int> selecionar() {
    std::vector<int> resultado;

    // ===================

    double p = 0.8;

    int a = torneio(p);
    int b;

    do {
        b = torneio(p);
    } while (a == b);

    // ===================

    resultado.push_back(a);
    resultado.push_back(b);

    return resultado;
}

int torneio(double p) {
    int a = std::rand() % populacao.size();
    int b = std::rand() % populacao.size();

    if (gerarAleatorio() < p) {
        // Retornar o mais forte
        if (populacao[a].aptidao > populacao[b].aptidao) {
            return a;
        } else {
            return b;
        }
    } else {
        // Retornar o mais fraco
        if (populacao[a].aptidao > populacao[b].aptidao) {
            return b;
        } else {
            return a;
        }
    }
}
```

## Cruzamento

```cpp
Solucao filhoA = a;
Solucao filhoB = b;

double chance = 0.9;

if (gerarAleatorio() < chance) {
    int ponto = std::rand() % a.bits.size();

    for (int i = 0; i < ponto; i++) {
//      int alelo = filhoA.bits[i];
//      filhoA.bits[i] = filhoB.bits[i];
//      filhoB.bits[i] = alelo;

        std::swap(filhoA.bits[i], filhoB.bits[i]);
    }
}

resultado.push_back(filhoA);
resultado.push_back(filhoB);
```

## Mutação

```cpp
// Para cada i em individuo.bits.size()

if (gerarAleatorio() < 0.01) {
    if (individuo.bits[i] == 0) {
        individuo.bits[i] = 1;
    } else {
        individuo.bits[i] = 0;
    }
}
```
