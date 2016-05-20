package br.univali.concatto;

public abstract class Sistema {
	private String[] opcoes;

	/**
	 * Contrói um sistema capaz de apresentar um menu de ações
	 * e ler a entrada de opção de um usuário.
	 * @param mensagem a mensagem inicial a ser apresentada
	 * @param opcoes um conjunto de opções a serem mostradas ao usuário.
	 * Não é necessário incluir a opção "Sair", pois será inclusa automaticamente.
	 */
	public Sistema(String mensagem, String[] opcoes) {
		this.opcoes = opcoes;
		
		System.out.println(mensagem);
	}
	
	protected void executar() {
		int acao;
		do {
			acao = solicitarAcao();
			realizarAcao(acao);
		} while (acao != 0);
		
		System.out.println("Até a próxima!");
	}
	
	private int solicitarAcao() {
		for (int i = 0; i < opcoes.length; i++) {
			System.out.println((i + 1) + " - " + opcoes[i]);
		}
		
		System.out.println("0 - Sair");
		return Entrada.lerInt("Ação: ");
	}
	
	protected abstract void realizarAcao(int acao);
}
