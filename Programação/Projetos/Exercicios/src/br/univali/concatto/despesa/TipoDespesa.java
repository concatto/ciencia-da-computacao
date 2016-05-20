package br.univali.concatto.despesa;

public class TipoDespesa {
	private String descricao;
	
	public TipoDespesa(String descricao) {
		this.descricao = descricao;
	}

	public String getDescricao() {
		return descricao;
	}
	
	public void setDescricao(String descricao) {
		this.descricao = descricao;
	}
}
