package br.univali.concatto.despesa;

import java.util.Date;

import br.univali.concatto.Entrada;
import br.univali.concatto.Sistema;

public class SistemaDespesas extends Sistema {
	private ControleDespesa controle = new ControleDespesa();
	
	public SistemaDespesas() {
		super("Boas vindas ao sistema de controle de despesas!", new String[] {
			"Registrar despesa",
			"Adicionar tipo de despesa",
			"Adicionar forma de pagamento",
			"Listar tipos de despesa",
			"Listar formas de pagamento",
			"Listar gastos do mês"
		});
		
		executar();
	}
	
	public static void main(String[] args) {
		new SistemaDespesas();
	}

	@Override
	public void realizarAcao(int acao) {
		switch (acao) {
		case 1:
			registrarDespesa();
			break;
		case 2:
			adicionarTipo();
			break;
		case 3:
			adicionarForma();
			break;
		case 4:
			listarTipos();
			break;
		case 5:
			listarFormas();
			break;
		case 6:
			listarGastos();
			break;
		}
	}

	private void listarGastos() {
		int mes = Entrada.lerInt("Digite o mês: ");
		int ano = Entrada.lerInt("Digite o ano: ");
		for (Despesa d : controle.listarGastosMes(mes, ano)) {
			if (d != null) {
				System.out.println(d);
			}
		}
	}

	private void listarFormas() {
		if (controle.getQuantidadeFormas() == 0) {
			System.out.println("Nenhuma forma de pagamento registrada.");
		} else {
			FormaPagamento[] formas = controle.getFormasPagamento();
			for (int i = 0; i < controle.getQuantidadeFormas(); i++) {
				if (formas[i] != null) {
					System.out.println("Forma n. " + i + ": \"" + formas[i].getDescricao() + "\"");
				}
			}
		}
	}

	private void listarTipos() {
		if (controle.getQuantidadeTipos() == 0) {
			System.out.println("Nenhum tipo de despesa registrado.");
		} else {
			TipoDespesa[] tipos = controle.getTiposDespesa();
			for (int i = 0; i < controle.getQuantidadeTipos(); i++) {
				if (tipos[i] != null) {
					System.out.println("Tipo n. " + i + ": \"" + tipos[i].getDescricao() + "\"");
				}
			}
		}
	}

	private void adicionarForma() {
		String descricao = Entrada.lerString("Entre com a descrição da forma: ");
		System.out.println("Forma de pagamento n. " + controle.adicionarFormaPagamento(descricao) + " adicionada.");
	}

	private void adicionarTipo() {
		String descricao = Entrada.lerString("Entre com a descrição do tipo: ");
		System.out.println("Tipo de despesa n. " + controle.adicionarTipoDespesa(descricao) + " adicionado.");
	}

	private void registrarDespesa() {
		String descricao = Entrada.lerString("Digite a descrição: ");
		Date data = Entrada.lerData("Digite a data (dd/mm/aaaa): ");
		double valor = Entrada.lerDouble("Digite o valor: ");
		int tipo = Entrada.lerInt("Digite o número do tipo de despesa: ");
		int forma = Entrada.lerInt("Digite o número da forma de pagamento: ");
		
		TipoDespesa[] tipos = controle.getTiposDespesa();
		FormaPagamento[] formas = controle.getFormasPagamento();
		controle.adicionarDespesa(descricao, data, valor, tipos[tipo], formas[forma]);
		System.out.println("Despesa dicionada com sucesso.");
	}
}
