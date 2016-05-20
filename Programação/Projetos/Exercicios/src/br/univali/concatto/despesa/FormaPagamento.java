package br.univali.concatto.despesa;

public class FormaPagamento {
	private String descricao;

	public FormaPagamento(String descricao) {
		this.descricao = descricao;
	}

	public String getDescricao() {
		return descricao;
	}

	public void setDescricao(String descricao) {
		this.descricao = descricao;
	}
}
