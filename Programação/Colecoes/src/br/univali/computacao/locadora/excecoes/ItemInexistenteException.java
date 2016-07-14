package br.univali.computacao.locadora.excecoes;

@SuppressWarnings("serial")
public class ItemInexistenteException extends Exception {
	public ItemInexistenteException(String message) {
		super(message);
	}
}
