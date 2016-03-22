ListaEstatica buscarRepetidos(ListaEstatica& origem, ListaEstatica& comparadora) {
  ListaEstatica repetidos;
  inicializar(repetidos);
  
  for (int i = 0; i < comparadora.qtd; i++) {
    for (int j = 0; j < origem.qtd; j++) {
      if (origem.dados[j] == comparadora.dados[i]) {
        inserirFim(repetidos, j);
      }
    }
  }
  
  return repetidos;
}

void removerItens(ListaEstatica& itens, ListaEstatica& indices) {
  for (int i = 0; i < indices.qtd; i++) {
    remover(itens, indices.dados[i])
  }
}

void f(ListaEstatica& a, ListaEstatica& b) {
  ListaEstatica remocaoA = buscarRepetidos(a, b);
  ListaEstatica remocaoB = buscarRepetidos(b, a);
  
  removerItens(a, remocaoA);
  removerItens(b, remocaoB);
}

template <class T>
void removerPares(ListaDuplamenteEncadeada<T>& lista) {
  lista.inicio = lista.inicio->proximo;
  delete lista.inicio->anterior;
  lista.inicio->anterior = NULL;
  lista.qtd--;
  
  Elemento<T>* nav = lista.inicio->proximo;
  while (nav != NULL) {
    Elemento<T>* obsoleto = nav;
    
    if (nav->proximo == NULL) { //Último elemento
      lista.ultimo = nav->anterior;
    } else {
      nav->proximo->anterior = nav->anterior;
    }
    
    nav->anterior->proximo = nav->proximo;   

    if (nav->proximo == NULL) {
      nav = NULL; //Força fim do loop
    } else {
      nav = nav->proximo->proximo;
    }
    
    delete obsoleto;
    lista.qtd--;
  }
}


void dividir(ListaEncadeada& a, ListaEncadeada& b, ListaEncadeada&c, int k) {
  b.qtd = k;
  b.inicio = k > 0 ? a.inicio : NULL;
  
  Elemento<T>* meio = b.inicio;
  for (int i = 0; i < k - 1; i++) {
    meio = meio->proximo;
  }
  
  c.qtd = a.qtd - k;
  c.inicio = k > 0 ? meio->proximo : a.inicio;
  
  if (meio != NULL) meio->proximo = NULL;
  
  a.qtd = 0;
  a.inicio = NULL;
}
