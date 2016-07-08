package br.univali.computacao.locadora;

import br.univali.computacao.locadora.dominio.Locadora;

public class Programa {
	private Locadora locadora;
	private InterfaceUsuario ui;
	
	public Programa() {
		locadora = new Locadora();
		ui = new InterfaceUsuario(locadora);

		int opcao;
		do {
			System.out.println("1 - Cadastrar veículo");
			System.out.println("2 - Cadastrar cliente");
			System.out.println("3 - Cadastrar modelo");
			System.out.println("4 - Cadastrar marca");
			System.out.println("5 - Realizar locação");
			System.out.println("6 - Finalizar locação");
			System.out.println("7 - Listar locações");
			System.out.println("8 - Listar veículos");
			System.out.println("9 - Listar clientes");
			System.out.println("10 - Listar modelos");
			System.out.println("11 - Listar marcas");
			System.out.println("0 - Sair");
			opcao = Entrada.lerInt("Digite uma ação: ");
			
			executarAcao(opcao);
			Entrada.aguardarEntrada("Pressione enter para continuar...");
		} while (opcao != 0);
	}
	
	private void executarAcao(int opcao) {
		switch (opcao) {
		case 1:
			ui.cadastrarVeiculo();
			break;
		case 2:
			ui.cadastrarCliente();
			break;
		case 3:
			ui.cadastrarModelo();
			break;
		case 4:
			ui.cadastrarMarca();
			break;
		case 5:
			ui.realizarLocacao();
			break;
		case 6:
			ui.finalizarLocacao();
			break;
		case 7:
			ui.listarLocacoes();
			break;
		case 8:
			ui.listarVeiculos();
			break;
		case 9:
			ui.listarClientes();
			break;
		case 10:
			ui.listarModelos();
			break;
		case 11:
			ui.listarMarcas();
			break;
		}
	}

	public static void main(String[] args) {
		new Programa();
	}
}