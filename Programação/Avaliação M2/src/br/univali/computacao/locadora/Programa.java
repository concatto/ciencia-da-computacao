package br.univali.computacao.locadora;

import java.util.Date;

import br.univali.computacao.locadora.dominio.EmpresaLocacao;
import br.univali.computacao.locadora.dominio.Locacao;

public class Programa {
	private EmpresaLocacao empresa;
	
	public Programa() {
		empresa = new EmpresaLocacao();
		
		int opcao;
		do {
			System.out.println("1 - Cadastrar veículo");
			System.out.println("2 - Cadastrar cliente");
			System.out.println("3 - Realizar locação");
			System.out.println("4 - Finalizar locação");
			System.out.println("5 - Listar locações");
			System.out.println("6 - Listar veículos");
			System.out.println("7 - Listar clientes");
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
			realizarLocacao();
			break;
		case 4:
			finalizarLocacao();
			break;
		case 5:
			listarLocacoes();
			break;
		case 6:
			listarVeiculos();
			break;
		case 7:
			listarClientes();
			break;
		}
	}

	private void listarClientes() {
		for (int i = 0; i < empresa.getClientesCadastrados(); i++) {
			System.out.println("N. " + i + ": " + empresa.getCliente(i));
		}
	}

	private void listarVeiculos() {
		for (int i = 0; i < empresa.getVeiculosCadastrados(); i++) {
			System.out.println("N. " + i + ": " + empresa.getVeiculo(i));
		}
	}

	private void listarLocacoes() {
		System.out.println("1 - Todas");
		System.out.println("2 - Ativas");
		System.out.println("3 - Finalizadas");
		int opcao = Entrada.lerInt("Opção: ");
		
		for (int i = 0; i < empresa.getLocacoesCadastradas(); i++) {
			Locacao l = empresa.getLocacao(i);
			if (opcao == 1 || (opcao == 2 && !l.isFinalizada()) || (opcao == 3 && l.isFinalizada())) { 
				System.out.println("N. " + i + ": " + l);
			}
		}
	}

	private void finalizarLocacao() {
		int locacao = Entrada.lerInt("Digite o número da locação: ");
		double kmFinal = Entrada.lerDouble("Digite a quilometragem final: ");
		Date dataFim = Entrada.lerData("Digite a data de fim da locação (dd/mm/aaaa): ");
		
		double valor = empresa.finalizarLocacao(empresa.getLocacao(locacao), kmFinal, dataFim);
		
		if (valor == -1) {
			System.out.println("Falha na finalização da locação.");
		} else {
			//O valor é apresentado com duas casas decimais.
			System.out.printf("Locação n. %d finalizada. O valor a ser pago é R$%.2f.\n", locacao, valor);
		}
	}

	private void realizarLocacao() {
		int cliente = Entrada.lerInt("Digite o número do cliente: ");
		int veiculo = Entrada.lerInt("Digite o número do veículo: ");
		Date dataInicio = Entrada.lerData("Digite a data inicial (dd/mm/aaaa): ");
		
		int indice = empresa.alugarVeiculo(empresa.getVeiculo(veiculo), empresa.getCliente(cliente), dataInicio);
		if (indice == -1) {
			System.out.println("Falha na locação.");
		} else {
			System.out.println("Locação de n. " + indice + " registrada.");
		}
	}

	private void cadastrarCliente() {
		String nome = Entrada.lerString("Digite o nome: ");
		String cpf = Entrada.lerString("Digite o CPF: ");
		
		int numero = empresa.cadastrarCliente(nome, cpf);
		if (numero == -1) {
			System.out.println("Falha no registro do cliente. Não há mais espaços.");
		} else {
			System.out.println("Cliente n. " + numero + " cadastrado!");
		}
	}

	private void cadastrarVeiculo() {
		String modelo = Entrada.lerString("Digite o modelo: ");
		String marca = Entrada.lerString("Digite a marca: ");
		String placa = Entrada.lerString("Digite a placa: ");
		int ano = Entrada.lerInt("Digite o ano: ");
		double valorPorKm = Entrada.lerDouble("Digite o valor por quilômetro rodado: ");
		double quilometragem = Entrada.lerDouble("Digite a quilometragem: ");
		
		int numero = empresa.cadastrarVeiculo(modelo, marca, placa, ano, valorPorKm, quilometragem);
		if (numero == -1) {
			System.out.println("Falha no registro do veículo. Não há mais espaços.");
		} else {
			System.out.println("Veículo n. " + numero + " cadastrado!");
		}
	}

	public static void main(String[] args) {
		new Programa();
	}
}
