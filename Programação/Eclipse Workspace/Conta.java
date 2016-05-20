package br.univali.concatto.banco;

public class Conta {
	private double saldo;
	private double limite;
	private int numeroConta;
	private static int contadorConta = 0;
	
	public Conta(double saldo, double limite) {
		this.saldo = saldo;
		this.limite = limite;
		this.numeroConta = contadorConta++;
	}

	public double getSaldo() {
		return saldo;
	}

	public double getLimite() {
		return limite;
	}

	public int getNumeroConta() {
		return numeroConta;
	}
	
	public void depositar(double valor) {
		this.saldo += valor;
	}
	
	public boolean sacar(double valor) {
		if (valor < getValorDisponivel()) {
			this.saldo -= valor;
			return true;
		}
		return false;
	}
	
	public double getValorDisponivel() {
		return saldo + limite;
	}
}
