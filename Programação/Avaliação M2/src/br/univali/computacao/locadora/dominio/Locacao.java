package br.univali.computacao.locadora.dominio;

import java.util.Date;

public class Locacao {
	private Veiculo veiculo;
	private Cliente cliente;
	private double kmInicial;
	private double kmFinal;
	private Date dataInicio;
	private Date dataFim;
	private boolean finalizada = false;
	
	public Locacao(Veiculo veiculo, Cliente cliente, Date dataInicio) {
		this.cliente = cliente;
		this.veiculo = veiculo;
		this.kmInicial = veiculo.getQuilometragem();
		this.dataInicio = dataInicio;
	}

	public void finalizar(double kmFinal, Date dataFim) {
		this.kmFinal = kmFinal;
		this.dataFim = dataFim;
		finalizada = true; 
	}
	
	public Cliente getCliente() {
		return cliente;
	}
	
	public Veiculo getVeiculo() {
		return veiculo;
	}
	
	public double getKmInicial() {
		return kmInicial;
	}
	
	public double getKmFinal() {
		return kmFinal;
	}
	
	public boolean isFinalizada() {
		return finalizada;
	}
	
	@SuppressWarnings("deprecation")
	@Override
	public String toString() {
		int dia = dataInicio.getDate();
		int mes = dataInicio.getMonth() + 1;
		int ano = dataInicio.getYear() + 1900;
		String s = String.format("Locação do veículo %s %s por %s, iniciada em %d/%d/%d e ", veiculo.getMarca(), veiculo.getModelo(), cliente.getNome(), dia, mes, ano);
		
		if (finalizada) {
			return s + String.format("finalizada em %d/%d/%d.", dataFim.getDate(), dataFim.getMonth() + 1, dataFim.getYear() + 1900);
		} else {
			return s + "ainda ativa.";
		}
	}
}
