# Realizar lance

### Pré-condições
O participante deve estar cadastrado e logado no sistema. O leilão do item não pode estar finalizado.

### Pós-condições
Item é atualizado com o lance proposto, e o participante é demarcado como detentor do maior lance.

### Objetivo
Permite que o participante realize um lance sobre um item disponível no leilão.

### Ator principal
Participante

### Fluxo principal
1. Participante escolhe um item disponível.
1. Participante determina o valor do lance.
1. Participante confirma o lance.
1. Sistema anuncia a realização do lance através de uma mensagem.

### Fluxo de exceção
* No passo 3, caso o lance seja inferior ao atual, emitir uma mensagem lembrando que o lance deve ser superior e o lance é rejeitado. Retorna ao passo 2.