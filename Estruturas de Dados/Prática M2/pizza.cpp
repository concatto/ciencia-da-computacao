#include <iostream>
#include "queue.h"
#include <Windows.h>

struct Pedido {
	int tempoAtendimento;
	Pedido() : tempoAtendimento(0) {}
};

void realizarAtendimento(Queue<Pedido>& a, Queue<Pedido>& j, Queue<Pedido>& d) {
	std::cout << "Atendendo!\n";
	Queue<Pedido>* filas[] = {&a, &j, &d};
	int limites[] = {2, 4, 3};
	
	for (int i = 0; i < 3; i++) {
		if (filas[i]->getSize() == 0) continue;
		
		Pedido& p = filas[i]->head->value;
		p.tempoAtendimento++;
		std::cout << i << " tem " << p.tempoAtendimento << " tempos.\n";
		
		if (p.tempoAtendimento == limites[i]) {
			filas[i]->dequeue();
			std::cout << "Removido elemento de " << i << "\n";
		}
	}
}

int main() {
	Queue<Pedido> a, b, c;
	
	for (int i = 0; i < 10; i++) {
		a.enqueue(Pedido());
		b.enqueue(Pedido());
		c.enqueue(Pedido());
	}
	
	while (true) {
		realizarAtendimento(a, b, c);
	}
}