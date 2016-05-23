package br.univali.concatto.remedios;

public class Medico {
	private String nome;
	private String numeroCRM;
	
	public Medico(String nome) {
		this.nome = nome;
	}
	
	public Medico(String nome, String numeroCRM) {
		this.nome = nome;
		this.numeroCRM = numeroCRM;
	}
	
	public String getNome() {
		return nome;
	}
}
