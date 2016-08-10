package br.univali.concatto.exercicios;

public class Cliente {
	private String nome;
	private String sobrenome;
	private String cpf;
	private double saldo;
	private double limite;
	private int numeroConta;
	private static int numeroAtual = 0;
	
	public Cliente(String nome, String sobrenome, String cpf, double saldoInicial, double limite) {
		this.nome = nome;
		this.sobrenome = sobrenome;
		this.cpf = cpf;
		this.saldo = saldoInicial;
		this.limite = limite;
		this.numeroConta = gerarNumeroConta();
	}
	
	public String obterNomeCompleto() {
		return nome + " " + sobrenome;
	}
	
	public String obterCpf() {
		return cpf;
	}
	
	public int obterNumeroConta() {
		return numeroConta;
	}
	
	public double obterValorDisponivelParaSaque() {
		return saldo + limite;
	}
	
	public void realizarDeposito(double valor) {
		this.saldo += valor;
	}
	
	public boolean realizarSaque(double valor) {
		if (valor < obterValorDisponivelParaSaque()) {
			saldo -= valor;
			return true;
		}
		
		return false;
	}
	
	private static int gerarNumeroConta() {
		return numeroAtual++;
	}
}
