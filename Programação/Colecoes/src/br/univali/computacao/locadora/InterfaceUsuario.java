package br.univali.computacao.locadora;

import java.util.List;

import br.univali.computacao.excecoes.ClienteInexistenteException;
import br.univali.computacao.excecoes.ClienteJaExisteException;
import br.univali.computacao.excecoes.LocacaoInexistenteException;
import br.univali.computacao.excecoes.MarcaInexistenteException;
import br.univali.computacao.excecoes.ModeloInexistenteException;
import br.univali.computacao.excecoes.VeiculoInexistenteException;
import br.univali.computacao.excecoes.VeiculoJaExisteException;
import br.univali.computacao.locadora.dominio.Cliente;
import br.univali.computacao.locadora.dominio.Locacao;
import br.univali.computacao.locadora.dominio.Locadora;
import br.univali.computacao.locadora.dominio.Marca;
import br.univali.computacao.locadora.dominio.Modelo;
import br.univali.computacao.locadora.dominio.Veiculo;

public class InterfaceUsuario {
	private Locadora locadora;
	
	public InterfaceUsuario(Locadora locadora) {
		this.locadora = locadora;
	}
	
	public void listarMarcas() {
		List<Marca> marcas = locadora.getMarcas();
		for (int i = 0; i < marcas.size(); i++) {
			System.out.println("N. " + i + ": " + marcas.get(i));
		}
	}

	public void listarModelos() {
		List<Modelo> modelos = locadora.getModelos();
		for (int i = 0; i < modelos.size(); i++) {
			System.out.println("N. " + i + ": " + modelos.get(i));
		}
	}

	public void cadastrarMarca() {
		String nome = Entrada.lerString("Digite o nome da marca: ");
		locadora.adicionarMarca(new Marca(nome));
		System.out.println("Marca " + nome + " registrada.");
	}

	public void cadastrarModelo() {
		String nome = Entrada.lerString("Digite o nome do modelo: ");
		int marca = Entrada.lerInt("Digite o número da marca: ");
		
		try {
			Modelo modelo = new Modelo(nome, locadora.getMarca(marca));
			locadora.adicionarModelo(modelo);
			System.out.println("Modelo " + modelo + " registrado.");
		} catch (MarcaInexistenteException ex) {
			System.out.println("Impossível cadastrar o modelo. A marca não existe.");
		}
	}

	public void listarClientes() {
		for (Cliente cliente : locadora.getClientes().values()) {
			System.out.println(cliente);
		}
	}

	public void listarVeiculos() {
		for (Veiculo cliente : locadora.getVeiculos().values()) {
			System.out.println(cliente);
		}
	}

	public void listarLocacoes() {
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

	public void finalizarLocacao() {
		String placa = Entrada.lerString("Digite a placa do veículo: ");
		int kmFinal = Entrada.lerInt("Digite a quilometragem final: ");
		
		try {
			Locacao l = locadora.finalizarLocacao(placa, kmFinal);
			System.out.printf("Locação do veículo de placa %s finalizada. Custo: R$%.2f\n", placa, l.valorTotal());
		} catch (LocacaoInexistenteException e) {
			System.out.println("Impossível finalizar a locação. A locação não foi encontrada.");
		} catch (VeiculoInexistenteException e) {
			System.out.println("Impossível finalizar a locação. O veículo solicitado não existe.");
		}
	}

	public void realizarLocacao() {
		String cpf = Entrada.lerString("Digite o CPF do cliente: ");
		String placa = Entrada.lerString("Digite a placa do veículo: ");
		
		try {
			locadora.alugarVeiculo(locadora.buscarVeiculo(placa), locadora.buscarCliente(cpf));
			System.out.println("Locação registrada.");
		} catch (VeiculoInexistenteException e) {
			System.out.println("Impossível registrar a locação. O veículo não existe.");
		} catch (ClienteInexistenteException e) {
			System.out.println("Impossível registrar a locação. O cliente não existe.");
		}
	}

	public void cadastrarCliente() {
		String nome = Entrada.lerString("Digite o nome: ");
		String cpf = Entrada.lerString("Digite o CPF: ");
		
		try {
			locadora.adicionarCliente(new Cliente(nome, cpf));
			System.out.println("Cliente " + nome + " cadastrado!");
		} catch (ClienteJaExisteException e) {
			System.out.println("Impossível cadastrar o cliente. Já existe um cliente com este CPF.");
		}
	}

	public void cadastrarVeiculo() {
		int modelo = Entrada.lerInt("Digite o número do modelo: ");		
		String placa = Entrada.lerString("Digite a placa: ");
		int ano = Entrada.lerInt("Digite o ano: ");
		double valorPorKm = Entrada.lerDouble("Digite o valor por quilômetro rodado: ");
		int quilometragem = Entrada.lerInt("Digite a quilometragem: ");
		
		try {
			locadora.adicionarVeiculo(new Veiculo(locadora.getModelo(modelo), quilometragem, ano, placa, valorPorKm));
			System.out.println("Veículo cadastrado!");
		} catch (ModeloInexistenteException e) {
			System.out.println("Impossível cadastrar o veículo. O modelo não existe.");
		} catch (VeiculoJaExisteException e) {
			System.out.println("Impossível cadastrar o veículo. Já existe um veículo com esta placa.");
		}
	}
}
