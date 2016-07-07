package br.univali.computacao.locadora;

import java.util.List;

import br.univali.computacao.locadora.dominio.Cliente;
import br.univali.computacao.locadora.dominio.Locacao;
import br.univali.computacao.locadora.dominio.Locadora;
import br.univali.computacao.locadora.dominio.Marca;
import br.univali.computacao.locadora.dominio.Modelo;
import br.univali.computacao.locadora.dominio.Veiculo;

public class Programa {
	private Locadora locadora;
	
	public Programa() {
		locadora = new Locadora();
		
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
		} while (opcao != 0);
	}
	
	private void executarAcao(int opcao) {
		switch (opcao) {
		case 1:
			cadastrarVeiculo();
			break;
		case 2:
			cadastrarCliente();
			break;
		case 3:
			cadastrarModelo();
			break;
		case 4:
			cadastrarMarca();
			break;
		case 5:
			realizarLocacao();
			break;
		case 6:
			finalizarLocacao();
			break;
		case 7:
			listarLocacoes();
			break;
		case 8:
			listarVeiculos();
			break;
		case 9:
			listarClientes();
			break;
		case 10:
			listarModelos();
			break;
		case 11:
			listarMarcas();
			break;
		}
	}

	private void listarMarcas() {
		List<Marca> marcas = locadora.getMarcas();
		for (int i = 0; i < marcas.size(); i++) {
			System.out.println("N. " + i + ": " + marcas.get(i));
		}
	}

	private void listarModelos() {
		List<Modelo> modelos = locadora.getModelos();
		for (int i = 0; i < modelos.size(); i++) {
			System.out.println("N. " + i + ": " + modelos.get(i));
		}
	}

	private void cadastrarMarca() {
		String nome = Entrada.lerString("Digite o nome da marca: ");
		locadora.adicionarMarca(new Marca(nome));
		System.out.println("Marca " + nome + " registrada.");
	}

	private void cadastrarModelo() {
		String nome = Entrada.lerString("Digite o nome do modelo: ");
		int marca = Entrada.lerInt("Digite o número da marca: ");
		
		Modelo modelo = new Modelo(nome, locadora.getMarcas().get(marca));
		locadora.adicionarModelo(modelo);
		System.out.println("Modelo " + modelo + " registrado.");
	}

	private void listarClientes() {
		for (Cliente cliente : locadora.getClientes().values()) {
			System.out.println(cliente);
		}
	}

	private void listarVeiculos() {
		for (Veiculo cliente : locadora.getVeiculos().values()) {
			System.out.println(cliente);
		}
	}

	private void listarLocacoes() {
		System.out.println("1 - Todas");
		System.out.println("2 - Ativas");
		System.out.println("3 - Finalizadas");
		int opcao = Entrada.lerInt("Opção: ");
		
		List<Locacao> locacoes = locadora.getLocacoes();
		for (int i = 0; i < locacoes.size(); i++) {
			Locacao locacao = locacoes.get(i);
			
			if (opcao == 1 || (opcao == 2 && locacao.estaAtiva()) || (opcao == 3 && !locacao.estaAtiva())) { 
				System.out.println("N. " + i + ": " + locacao);
			}
		}
	}

	private void finalizarLocacao() {
		String placa = Entrada.lerString("Digite a placa do veículo: ");
		int kmFinal = Entrada.lerInt("Digite a quilometragem final: ");
		
		Locacao l = locadora.finalizarLocacao(locadora.buscarVeiculo(placa), kmFinal);
		System.out.printf("Locação do veículo de placa %s finalizada. Custo: R$%.2f\n", placa, l.valorTotal());
	}

	private void realizarLocacao() {
		String cpf = Entrada.lerString("Digite o CPF do cliente: ");
		String placa = Entrada.lerString("Digite a placa do veículo: ");
		
		locadora.alugarVeiculo(locadora.buscarVeiculo(placa), locadora.buscarCliente(cpf));
		System.out.println("Locação registrada.");
	}

	private void cadastrarCliente() {
		String nome = Entrada.lerString("Digite o nome: ");
		String cpf = Entrada.lerString("Digite o CPF: ");
		
		locadora.adicionarCliente(new Cliente(nome, cpf));
		System.out.println("Cliente " + nome + " cadastrado!");
	}

	private void cadastrarVeiculo() {
		int modelo = Entrada.lerInt("Digite o número do modelo: ");		
		String placa = Entrada.lerString("Digite a placa: ");
		int ano = Entrada.lerInt("Digite o ano: ");
		double valorPorKm = Entrada.lerDouble("Digite o valor por quilômetro rodado: ");
		int quilometragem = Entrada.lerInt("Digite a quilometragem: ");
		
		locadora.adicionarVeiculo(new Veiculo(locadora.getModelos().get(modelo), quilometragem, ano, placa, valorPorKm));
		
		System.out.println("Veículo cadastrado!");
	}

	public static void main(String[] args) {
		new Programa();
	}
}