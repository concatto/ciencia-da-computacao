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
			System.out.println("1 - Cadastrar ve�culo");
			System.out.println("2 - Cadastrar cliente");
			System.out.println("3 - Realizar loca��o");
			System.out.println("4 - Finalizar loca��o");
			System.out.println("5 - Listar loca��es");
			System.out.println("6 - Listar ve�culos");
			System.out.println("7 - Listar clientes");
			System.out.println("0 - Sair");
			opcao = Entrada.lerInt("Digite uma a��o: ");
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
		int opcao = Entrada.lerInt("Op��o: ");
		
		for (int i = 0; i < empresa.getLocacoesCadastradas(); i++) {
			Locacao l = empresa.getLocacao(i);
			if (opcao == 1 || (opcao == 2 && !l.isFinalizada()) || (opcao == 3 && l.isFinalizada())) { 
				System.out.println("N. " + i + ": " + l);
			}
		}
	}

	private void finalizarLocacao() {
		int locacao = Entrada.lerInt("Digite o n�mero da loca��o: ");
		double kmFinal = Entrada.lerDouble("Digite a quilometragem final: ");
		Date dataFim = Entrada.lerData("Digite a data de fim da loca��o (dd/mm/aaaa): ");
		
		double valor = empresa.finalizarLocacao(empresa.getLocacao(locacao), kmFinal, dataFim);
		
		if (valor == -1) {
			System.out.println("Falha na finaliza��o da loca��o.");
		} else {
			//O valor � apresentado com duas casas decimais.
			System.out.printf("Loca��o n. %d finalizada. O valor a ser pago � R$%.2f.\n", locacao, valor);
		}
	}

	private void realizarLocacao() {
		int cliente = Entrada.lerInt("Digite o n�mero do cliente: ");
		int veiculo = Entrada.lerInt("Digite o n�mero do ve�culo: ");
		Date dataInicio = Entrada.lerData("Digite a data inicial (dd/mm/aaaa): ");
		
		int indice = empresa.alugarVeiculo(empresa.getVeiculo(veiculo), empresa.getCliente(cliente), dataInicio);
		if (indice == -1) {
			System.out.println("Falha na loca��o.");
		} else {
			System.out.println("Loca��o de n. " + indice + " registrada.");
		}
	}

	private void cadastrarCliente() {
		String nome = Entrada.lerString("Digite o nome: ");
		String cpf = Entrada.lerString("Digite o CPF: ");
		
		int numero = empresa.cadastrarCliente(nome, cpf);
		if (numero == -1) {
			System.out.println("Falha no registro do cliente. N�o h� mais espa�os.");
		} else {
			System.out.println("Cliente n. " + numero + " cadastrado!");
		}
	}

	private void cadastrarVeiculo() {
		String modelo = Entrada.lerString("Digite o modelo: ");
		String marca = Entrada.lerString("Digite a marca: ");
		String placa = Entrada.lerString("Digite a placa: ");
		int ano = Entrada.lerInt("Digite o ano: ");
		double valorPorKm = Entrada.lerDouble("Digite o valor por quil�metro rodado: ");
		double quilometragem = Entrada.lerDouble("Digite a quilometragem: ");
		
		int numero = empresa.cadastrarVeiculo(modelo, marca, placa, ano, valorPorKm, quilometragem);
		if (numero == -1) {
			System.out.println("Falha no registro do ve�culo. N�o h� mais espa�os.");
		} else {
			System.out.println("Ve�culo n. " + numero + " cadastrado!");
		}
	}

	public static void main(String[] args) {
		new Programa();
	}
}
