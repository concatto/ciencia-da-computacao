package br.univali.computacao.locadora.dominio;

public class Veiculo {
	private String modelo;
	private String marca;
	private String placa;
	private int ano;
	private double valorPorKm;
	private double quilometragem;
	private boolean alugado = false;
	
	public Veiculo(String modelo, String marca, String placa, int ano, double valorPorKm, double quilometragem) {
		this.modelo = modelo;
		this.marca = marca;
		this.placa = placa;
		this.ano = ano;
		this.valorPorKm = valorPorKm;
		this.quilometragem = quilometragem;
	}
	
	public void setQuilometragem(double quilometragem) {
		this.quilometragem = quilometragem;
	}
	
	public double getQuilometragem() {
		return quilometragem;
	}
	
	public double getValorPorKm() {
		return valorPorKm;
	}
	
	@Override
	public String toString() {
		return String.format("%s %s %d, de placa %s. Quilometragem: %.2f; Valor por km: %.2f. %s",
				marca, modelo, ano, placa, quilometragem, valorPorKm, (alugado ? "Alugado" : "Disponível"));
	}
	
	public String getModelo() {
		return modelo;
	}
	
	public String getMarca() {
		return marca;
	}
	
	public int getAno() {
		return ano;
	}
	
	public String getPlaca() {
		return placa;
	}
	
	public boolean isAlugado() {
		return alugado;
	}
	
	public void setAlugado(boolean alugado) {
		this.alugado = alugado;
	}
}
