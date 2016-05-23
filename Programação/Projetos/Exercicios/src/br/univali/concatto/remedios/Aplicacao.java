package br.univali.concatto.remedios;

import java.util.Date;

import br.univali.concatto.Entrada;

public class Aplicacao {
	private Receita[] receitas = new Receita[100];
	private Planilha[] planilhas = new Planilha[100];
	private Remedio[] remedios = new Remedio[100];
	private Medico[] medicos = new Medico[100];
	private Paciente[] pacientes = new Paciente[100];
	private int indiceReceita = 0;
	private int indicePlanilha = 0;
	private int indiceRemedio = 0;
	private int indiceMedico = 0;
	private int indicePaciente = 0;
	
	public boolean cadastrarReceita(String remedio, String paciente, Date inicio, int quantidadeDias, int quantidadeVezes, int dosagem, String medico) {
		receitas[indiceReceita++] = new Receita(buscarRemedio(remedio), buscarPaciente(paciente), buscarMedico(medico), inicio, dosagem, quantidadeDias, quantidadeVezes);
		return true;
	}
	
	private Medico buscarMedico(String nome) {
		for (int i = 0; i < indiceMedico; i++) {
			if (medicos[i] != null && medicos[i].getNome().equalsIgnoreCase(nome)) {
				return medicos[i];
			}
		}
		Medico novo = new Medico(nome);
		medicos[indiceMedico++] = novo;
		return novo;
	}

	private Paciente buscarPaciente(String nome) {
		for (int i = 0; i < indicePaciente; i++) {
			if (pacientes[i] != null && pacientes[i].getNome().equalsIgnoreCase(nome)) {
				return pacientes[i];
			}
		}
		Paciente novo = new Paciente(nome);
		pacientes[indicePaciente++] = novo;
		return novo;
	}

	private Remedio buscarRemedio(String nome) {
		for (int i = 0; i < indiceRemedio; i++) {
			if (remedios[i] != null && remedios[i].getNome().equalsIgnoreCase(nome)) {
				return remedios[i];
			}
		}
		Remedio novo = new Remedio(nome);
		remedios[indiceRemedio++] = novo;
		return novo;
	}

	public int[] registrarPlanilha(int hora) {
		Receita alvo = receitas[indiceReceita - 1];

		int[] horas = calcularHoras(hora, alvo.getQuantidadeVezes());
		
		Date fim = new Date(alvo.getDataInicio().getTime());
		fim.setDate(alvo.getDataInicio().getDate() + alvo.getQuantidadeDias());
		
		planilhas[indicePlanilha++] = new Planilha(alvo, fim, horas);
		return horas;
	}
	
	public boolean reorganizarPlanilha(String remedio, int novaHora) {
		Planilha planilha = localizarPlanilha(remedio);
		if (planilha != null) {
			planilha.setHoras(calcularHoras(novaHora, planilha.getReceita().getQuantidadeVezes()));
			return true;
		}
		return false;
	}
	
	private Planilha localizarPlanilha(String nomeRemedio) {
		for (int i = 0; i < indicePlanilha; i++) {
			if (planilhas[i] != null && planilhas[i].getReceita().getRemedio().getNome().equalsIgnoreCase(nomeRemedio)) {
				return planilhas[i];
			}
		}
		return null;
	}

	private int[] calcularHoras(int hora, int vezesPorDia) {
		int intervaloHoras = 24 / vezesPorDia;
		int[] horas = new int[vezesPorDia];
		for (int i = 0; i < horas.length; i++) {
			horas[i] = hora;
			hora += intervaloHoras;
		}
		return horas;
	}
	
	public void cadastrarMedico(String nome, String crm) {
		medicos[indiceMedico++] = new Medico(nome, crm);
	}
}
