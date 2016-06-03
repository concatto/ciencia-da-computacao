package br.univali.computacao.locadora.dominio;

public class Cliente {
	private String nome;
	private String cpf;
	private double valorPago = 0;
	
	public Cliente(String nome, String cpf) {
		this.nome = nome;
		this.cpf = cpf;
	}
	
	public String getNome() {
		return nome;
	}
	
	public String getCpf() {
		return cpf;
	}
	
	public void incrementarValorPago(double valor) {
		valorPago += valor;
	}
	
	public double getValorPago() {
		return valorPago;
	}
	
	@Override
	public String toString() {
		return String.format("%s (CPF %s). Valor pago: R$%.2f", nome, cpf, valorPago);
	}
}
