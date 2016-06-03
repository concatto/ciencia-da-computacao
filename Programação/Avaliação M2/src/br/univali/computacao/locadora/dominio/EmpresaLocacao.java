package br.univali.computacao.locadora.dominio;

import java.util.Date;

public class EmpresaLocacao {
	private static final int TAMANHO = 100;
	private Veiculo[] veiculos = new Veiculo[TAMANHO];
	private Locacao[] locacoes = new Locacao[TAMANHO];
	private Cliente[] clientes = new Cliente[TAMANHO];
	private int veiculosCadastrados = 0;
	private int locacoesCadastradas = 0;
	private int clientesCadastrados = 0;

	public EmpresaLocacao() {

	}

	/**
	 * Cadastra um novo veículo
	 * @param modelo o modelo do veículo
	 * @param marca a marca do veículo
	 * @param placa a placa do veículo
	 * @param ano o ano do veículo
	 * @param valorPorKm o custo em reais por quilômetro rodado
	 * @param quilometragem a quilometragem atual do veículo
	 * @return o número do veículo registrado
	 */
	public int cadastrarVeiculo(String modelo, String marca, String placa, int ano, double valorPorKm, double quilometragem) {
		if (veiculosCadastrados == TAMANHO) return -1;
		
		veiculos[veiculosCadastrados++] = new Veiculo(modelo, marca, placa, ano, valorPorKm, quilometragem);
		return veiculosCadastrados - 1;
	}
	
	/**
	 * Cadastra um novo cliente
	 * @param nome o nome do cliente
	 * @param cpf o cpf do cliente
	 * @return o número do cliente registrado
	 */
	public int cadastrarCliente(String nome, String cpf) {
		if (clientesCadastrados == TAMANHO) return -1;
		
		clientes[clientesCadastrados++] = new Cliente(nome, cpf);
		return clientesCadastrados - 1;
	}
	
	/**
	 * Realiza o aluguel de um veículo
	 * @param veiculo o veículo a ser alugado
	 * @param cliente o cliente que alugou o veículo
	 * @param dataInicio a data de início
	 * @return o número da locação realizada
	 */
	public int alugarVeiculo(Veiculo veiculo, Cliente cliente, Date dataInicio) {
		if (veiculo == null || cliente == null || veiculo.isAlugado()) return -1;
		
		locacoes[locacoesCadastradas++] = new Locacao(veiculo, cliente, dataInicio);
		veiculo.setAlugado(true);
		return locacoesCadastradas - 1;
	}
	
	/**
	 * Finaliza a locação indicada
	 * @param locacao a locação a ser finalizada
	 * @param kmFinal a quilometragem final
	 * @param dataFim a data de término
	 * @return o valor a ser pago pelo cliente
	 */
	public double finalizarLocacao(Locacao locacao, double kmFinal, Date dataFim) {
		if (locacao == null || locacao.isFinalizada()) return -1;
		
		locacao.finalizar(kmFinal, dataFim);
		locacao.getVeiculo().setQuilometragem(kmFinal);
		locacao.getVeiculo().setAlugado(false);
		double custo = (locacao.getKmFinal() - locacao.getKmInicial()) * locacao.getVeiculo().getValorPorKm();
		
		locacao.getCliente().incrementarValorPago(custo);
		return custo;
	}
	
	public int getLocacoesCadastradas() {
		return locacoesCadastradas;
	}
	
	public int getVeiculosCadastrados() {
		return veiculosCadastrados;
	}
	
	public int getClientesCadastrados() {
		return clientesCadastrados;
	}
	
	public Locacao getLocacao(int indice) {
		return locacoes[indice];
	}
	
	public Cliente getCliente(int indice) {
		return clientes[indice];
	}
	
	public Veiculo getVeiculo(int indice) {
		return veiculos[indice];
	}
}
