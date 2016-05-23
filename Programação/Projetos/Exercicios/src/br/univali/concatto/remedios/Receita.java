package br.univali.concatto.remedios;

import java.util.Date;

public class Receita {
	private Remedio remedio;
	private Paciente paciente;
	private Medico medico;
	private Date dataInicio;
	private int dosagem;
	private int quantidadeDias;
	private int quantidadeVezes;
	
	public Receita(Remedio remedio, Paciente paciente, Medico medico, Date dataInicio, int dosagem, int quantidadeDias, int quantidadeVezes) {
		this.remedio = remedio;
		this.paciente = paciente;
		this.medico = medico;
		this.dataInicio = dataInicio;
		this.dosagem = dosagem;
		this.quantidadeDias = quantidadeDias;
		this.quantidadeVezes = quantidadeVezes;
	}
	
	public int getQuantidadeVezes() {
		return quantidadeVezes;
	}
	
	public int getQuantidadeDias() {
		return quantidadeDias;
	}
	
	public Date getDataInicio() {
		return dataInicio;
	}
	
	public Remedio getRemedio() {
		return remedio;
	}
}
