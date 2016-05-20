package br.univali.concatto.banco;

import java.util.ArrayList;
import java.util.List;

public class Cliente {
	private String nome;
	private String sobrenome;
	private String cpf;
	private List<Conta> contas = new ArrayList<>();

	public Cliente(String nome, String sobrenome, String cpf) {
		this.nome = nome;
		this.sobrenome = sobrenome;
		this.cpf = cpf;
	}

	public String getNome() {
		return nome;
	}

	public String getSobrenome() {
		return sobrenome;
	}

	public String getCpf() {
		return cpf;
	}
	
	public String getNomeCompleto() {
		return getNome() + getSobrenome();
	}
	
	public void adicionarConta(Conta conta) {
		contas.add(conta);
	}
	
	public List<Conta> getContas() {
		return contas;
	}
	
	public Conta getConta(int indice) {
		return contas.get(indice);
	}
}
