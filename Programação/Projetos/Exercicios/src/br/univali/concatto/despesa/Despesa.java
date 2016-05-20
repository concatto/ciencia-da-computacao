package br.univali.concatto.despesa;

import java.util.Date;

public class Despesa {
	private Date data;
	private String descricao;
	private double valor;
	private FormaPagamento formaPagamento;
	private TipoDespesa tipoDespesa;
	
	public Despesa(String descricao, Date data, double valor, TipoDespesa tipo, FormaPagamento forma) {
		this.descricao = descricao;
		this.data = data;
		this.valor = valor;
		this.tipoDespesa = tipo;
		this.formaPagamento = forma;
	}
	
	public Date getData() {
		return data;
	}
	
	@Override
	public String toString() {
		String forma = (formaPagamento != null) ? formaPagamento.getDescricao() : "desconhecido";
		String tipo = (tipoDespesa != null) ? tipoDespesa.getDescricao() : "desconhecido";
		return data.toString() + " => " + descricao + ". Valor: " + valor +
				". Forma de pagamento: " + forma + ". Tipo: " + tipo; 
	}
}
