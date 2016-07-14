package br.univali.computacao.locadora.excecoes;

@SuppressWarnings("serial")
public class ItemJaExisteException extends Exception {

	public ItemJaExisteException(String message) {
		super(message);
	}
	
}
