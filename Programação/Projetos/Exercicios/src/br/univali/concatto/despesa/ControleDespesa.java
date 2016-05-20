package br.univali.concatto.despesa;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class ControleDespesa {
	private List<Despesa> despesas = new ArrayList<>();
	private FormaPagamento[] formasPagamento = new FormaPagamento[100];
	private int indiceForma = 0;
	private TipoDespesa[] tiposDespesa = new TipoDespesa[100];
	private int indiceTipo = 0;
	
	public Despesa adicionarDespesa(String descricao, Date data, double valor, TipoDespesa tipo, FormaPagamento forma) {
		Despesa nova = new Despesa(descricao, data, valor, tipo, forma);
		despesas.add(nova);
		return nova;
	}
	
	public int adicionarFormaPagamento(String descricao) {
		FormaPagamento nova = new FormaPagamento(descricao);
		formasPagamento[indiceForma] = nova;
		return indiceForma++;
	}
	
	public int adicionarTipoDespesa(String descricao) {
		TipoDespesa novo = new TipoDespesa(descricao);
		tiposDespesa[indiceTipo] = novo;
		return indiceTipo++;
	}
	
	public FormaPagamento[] getFormasPagamento() {
		return formasPagamento;
	}
	
	public TipoDespesa[] getTiposDespesa() {
		return tiposDespesa;
	}
	
	public Despesa[] listarGastosMes(int mes, int ano) {
		Despesa[] despesasFiltradas = new Despesa[100];
		int i = 0;
		
		for (Despesa d : despesas) {
			System.out.println(d);
			if (d != null && d.getData().getMonth() == (mes - 1) && d.getData().getYear() == ano) {
				despesasFiltradas[i++] = d;
			}
		}
		
		return despesasFiltradas;
	}

	public int getQuantidadeFormas() {
		return indiceForma;
	}
	
	public int getQuantidadeTipos() {
		return indiceTipo;
	}
}
