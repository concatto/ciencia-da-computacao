#include "queue.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

struct Cliente {
	int tempo;
	
	Cliente() {}
	Cliente(int tempo) : tempo(tempo) {}
};

int buscarMenorFila(Queue<Cliente> filas[], int quantidadeFilas) {
	int menor = filas[0].getSize();
	int menorIndice = 0;
	for (int i = 1; i < quantidadeFilas; i++) {
		if (filas[i].getSize() < menor) {
			menor = filas[i].getSize();
			menorIndice = i;
		}
	}
	
	return menorIndice;
}

int main() {
	std::srand(std::time(nullptr));
	
	int caixas;
	int iteracoes;
	int otimizarBusca;
	int unidadesTempo;
	int clientesNovos = 3;
	
	std::cout << "Caixas: ";
	std::cin >> caixas;
	std::cout << "Iteracoes: ";
	std::cin >> iteracoes;
	std::cout << "Unidades de tempo: ";
	std::cin >> unidadesTempo;
	std::cout << "Buscar menor fila? (0: nao; 1: sim): ";
	std::cin >> otimizarBusca;
	
	Queue<Cliente> filas[caixas];
	
	bool V = false;
	
	double mediaGeral = 0;
	std::cout << "\n\nInicio da simulacao.\n\n";
	for (int it = 0; it < iteracoes; it++) {
		std::cout << "Inicio da iteracao " << it << ".\n";
		//Reinicialização das filas
		for (int i = 0; i < caixas; i++) {
			filas[i] = Queue<Cliente>();
		}
		
		for (int t = 0; t < unidadesTempo; t++) {
			if (V) std::cout << "Inicio do tempo " << t << ".\n";
			
			//Inserção de novos clientes
			for (int c = 0; c < clientesNovos; c++) {
				double valor = std::rand() / double(RAND_MAX);
				Cliente novo(valor < 0.3 ? 3 : 2);
				
				int indiceFila;
				if (otimizarBusca == 0) {
					indiceFila = std::rand() % caixas;
				} else {
					indiceFila = buscarMenorFila(filas, caixas);
				}
				
				filas[indiceFila].enqueue(novo);
				if (V) std::cout << "Cliente de tempo " << novo.tempo << " adicionado no caixa " << indiceFila << ", totalizando " << filas[indiceFila].getSize() << ".\n";
			}
			
			//Atendimento de clientes
			for (int a = 0; a < caixas; a++) {
				if (filas[a].getSize() > 0) {
					Cliente& cliente = filas[a].getHead();
					cliente.tempo--;
					
					if (V) std::cout << "Caixa " << a << ": atendido. Tempo restante: " << cliente.tempo << ".";
					if (cliente.tempo == 0) {
						filas[a].dequeue();
						if (V) std::cout << " Cliente removido.";
					}
					if (V) std::cout << "\n";
				} else {
					if (V) std::cout << "Caixa " << a << " esta vazio.\n";
				}
			}
			
			if (V) std::cout << "Termino do tempo " << t << ".\n\n";
		}
		
		//Clientes por fila
		double media = 0;
		for (int i = 0; i < caixas; i++) {
			std::cout << "Clientes na fila " << i << ": " << filas[i].getSize() << "\n";
			media += filas[i].getSize();
		}
		media /= caixas;
		mediaGeral += media;
		std::cout << "Media de clientes: " << media << ".\n";
		std::cout << "Termino da iteracao " << it << ".\n\n\n";
	}
	
	mediaGeral /= iteracoes;
	std::cout << "\n\nTermino da simulacao. Media geral de clientes por fila: " << mediaGeral << ".\n";
}
