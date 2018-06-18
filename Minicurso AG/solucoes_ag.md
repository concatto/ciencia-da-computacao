## main.cpp

```cpp
AlgoritmoGenetico ag(problema);
ag.gerarPopulacaoInicial(100);

for (int i = 0; i < 200; i++) {
    ag.evoluir();

    Solucao melhor = ag.getMelhorIndividuo();

    std::cout << "Melhor solucao encontrada tem qualidade " << melhor.aptidao << "\n";
}
```

<br>

## Busca exaustiva

```cpp
Solucao melhor;
double melhorQualidade = 0;

int total = std::pow(2, bits);
for (int i = 0; i < total; i++) {
    Solucao solucao;

    for (int j = 0; j < bits; j++) {
        solucao.bits.push_back(obterBit(i, j));
    }

    double qualidade = avaliar(solucao, problema);

    if (qualidade > melhorQualidade) {
        melhorQualidade = qualidade;
        melhor = solucao;
    }

    std::cout << i << "/" << total << " => " << melhorQualidade << "\n";
}

std::cout << "Melhor solucao encontrada tem qualidade " << melhorQualidade << "\n";
std::cout << "Opcoes no maximo:\n";
for (int i = 0; i < bits; i++) {
    if (melhor.bits[i] == 1) {
        imprimirOpcao(problema, i);
    }
}
```

<br>

## Função de avaliação

```cpp
// No AG não precisa receber o problema.
double avaliar(const Solucao& solucao, const Instancia& problema) {
    double custoTotal = 0;
    double qualidade = 0;

    for (int i = 0; i < solucao.bits.size(); i++) {
        if (solucao.bits[i] == 1) {
            custoTotal += problema.custos[i];
            qualidade += problema.importancias[i];
        }
    }

    if (custoTotal > problema.custoMaximo) {
        return 0; // Será?
    }

    return qualidade;
}
```

<br>

## Geração de população inicial

```cpp
// Para cada i em tamanhoPopulacao
Solucao individuo;

for (int j = 0; j < problema.importancias.size(); j++) {
    individuo.bits.push_back(std::rand() % 2);
//  individuo.bits.push_back(std::round(gerarAleatorio()));
//  individuo.bits.push_back((gerarAleatorio() < 0.5) ? 0 : 1);
}

individuo.aptidao = avaliar(individuo);
populacao.push_back(individuo);
```

<br>

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

<br>

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

<br>

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

<br>

# Evolução

```cpp
void evoluir() {
    std::vector<Solucao> novaPopulacao;

    while (novaPopulacao.size() < populacao.size()) {
        std::vector<int> pais = selecionar();

        std::vector<Solucao> filhos = aplicarCruzamento(populacao[pais[0]], populacao[pais[1]]);

        aplicarMutacao(filhos[0]);
        aplicarMutacao(filhos[1]);

        filhos[0].aptidao = avaliar(filhos[0]);
        filhos[1].aptidao = avaliar(filhos[1]);

        novaPopulacao.push_back(filhos[0]);
        novaPopulacao.push_back(filhos[1]);
    }

    // Elitismo (opcional, porém bom)
    int indice = std::rand() % novaPopulacao.size();
    novaPopulacao[indice] = getMelhorIndividuo();

    populacao = novaPopulacao;
}
```

<br>
<br>

## Questões

* #8 O que é possível deduzir sobre a função visualizando apenas a vizinhança de um ponto?
* #21 Quantas soluções existem considerando uma cadeia de n bits?
* #22 Qual a qualidade de uma solução cuja soma dos custos excede F?
* #26 Sendo os "indivíduos" as soluções para o problema, como medir suas "chances de sobreviver"?
* #33 Como gerar uma solução razoavelmente boa rapidamente?
* #36 Qual a consequência de selecionar apenas os melhores indivíduos para cruzar?
* #41 Qual o benefício do cruzamento de ponto duplo sobre ponto único?
* #44 O que aconteceria se a taxa de mutação fosse igual a 50%?
* #46 É possível que a aptidão do melhor indivíduo piore de uma geração para outra?
