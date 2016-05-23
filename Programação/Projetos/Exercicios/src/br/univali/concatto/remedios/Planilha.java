package br.univali.concatto.remedios;

import java.util.Arrays;
import java.util.Date;

public class Planilha {
	private Receita receita;
	private Date dataFim;
	private int[] horas = new int[24];
	
	public Planilha(Receita receita, Date dataFim, int[] horas) {
		this.receita = receita;
		this.dataFim = dataFim;
		setHoras(horas);
	}
	
	public Receita getReceita() {
		return receita;
	}
	
	public void setHoras(int[] horas) {
		Arrays.fill(this.horas, -1);
		for (int i = 0; i < horas.length; i++) {
			this.horas[i] = horas[i];
		}
	}
}
