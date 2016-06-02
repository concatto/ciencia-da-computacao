package br.univali.concatto.banco;

import br.univali.concatto.Entrada;
import br.univali.concatto.Sistema;

public class SistemaBanco extends Sistema {
	private Banco banco = new Banco();

	public SistemaBanco() {
		super("Boas vindas ao banco!", new String[] {
			"Criar conta",
			"Remover conta",
			"Sacar",
			"Depositar",
			"Saldo",
			"Extrato",
			"Transferir"
		});
		
		executar();
	}
	
	@Override
	protected void realizarAcao(int acao) {
		switch (acao) {
		case 1:
			criarConta();
			break;
		case 2:
			removerConta();
			break;
		case 3:
			sacar();
			break;
		case 4:
			depositar();
			break;
		case 5:
			consultarSaldo();
			break;
		case 6:
			consultarExtrato();
			break;
		case 7:
			transferir();
			break;
		}
	}

	private void transferir() {
		int contaOrigem = Entrada.lerInt("Digite o número da conta de origem: ");
		int contaDestino = Entrada.lerInt("Digite o número da conta de destino: ");
		double valor = Entrada.lerDouble("Digite a quantidade: ");
		if (banco.transferir(contaOrigem, contaDestino, valor)) {
			System.out.println("Transferência de " + valor + " reais de " + contaOrigem + " para " + contaDestino + " realizada com sucesso!");
		} else {
			System.out.println("Transferência rejeitada");
		}
	}

	private void consultarExtrato() {
		int conta = Entrada.lerInt("Digite o número da conta: ");
		System.out.println("Extrato da conta " + conta + ":");
		for (Movimentacao m : banco.extrato(conta)) {
			if (m != null) {
				System.out.println(m);
			}
		}
	}

	private void consultarSaldo() {
		int conta = Entrada.lerInt("Digite o número da conta: ");
		System.out.println("Saldo da conta " + conta + ": " + banco.saldo(conta));
	}

	private void depositar() {
		int conta = Entrada.lerInt("Digite o número da conta: ");
		double valor = Entrada.lerDouble("Digite a quantidade: ");
		if (banco.depositar(conta, valor)) {
			System.out.println(valor + " reais depositados com sucesso.");
		} else {
			System.out.println("Depúsito rejeitado.");
		}
	}

	private void sacar() {
		int conta = Entrada.lerInt("Digite o número da conta: ");
		double valor = Entrada.lerDouble("Digite a quantidade: ");
		if (banco.sacar(conta, valor)) {
			System.out.println(valor + " reais sacados com sucesso da conta " + conta + ".");
		} else {
			System.out.println("Saque rejeitado.");
		}
	}

	private void removerConta() {
		int conta = Entrada.lerInt("Digite o número da conta: ");
		if (banco.excluirConta(conta)) {
			System.out.println("Conta " + conta + " removida com sucesso.");
		} else {
			System.out.println("Falha na remoção da conta.");
		}
	}

	private void criarConta() {
		double saldoInicial = Entrada.lerDouble("Digite o saldo inicial: ");
		int numero = banco.criarConta(saldoInicial);
		System.out.println("Conta n. " + numero + " criada.");
	}
	
	public static void main(String[] args) {
		new SistemaBanco();
	}

}
