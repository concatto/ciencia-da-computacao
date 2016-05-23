package br.univali.concatto.remedios;

import java.util.Date;

import br.univali.concatto.Entrada;
import br.univali.concatto.Sistema;

public class SistemaRemedios extends Sistema {
	private Aplicacao aplicacao = new Aplicacao();
	
	public SistemaRemedios() {
		super("Boas vindas ao sistema de remédios!", new String[] {
			"Adicionar receita",
			"Reorganizar planilha",
			"Registrar médico"
		});
	}
	
	@Override
	protected void realizarAcao(int acao) {
		switch (acao) {
		case 1:
			adicionarReceita();
			break;
		case 2:
			reorganizar();
			break;
		case 3:
			registrarMedico();
			break;
		}
	}

	private void adicionarReceita() {
		String remedio = Entrada.lerString("Digite o nome do remédio: ");
		String paciente = Entrada.lerString("Digite o nome do paciente: ");
		Date inicio = Entrada.lerData("Digite a data de início (dd/mm/aaaa): ");
		int quantidadeDias = Entrada.lerInt("Digite a quantidade de dias: ");
		int quantidadeVezes = Entrada.lerInt("Digite a quantidade de vezes por dia: ");
		int dosagem = Entrada.lerInt("Digite a dosagem: ");
		String medico = Entrada.lerString("Digite o nome do médico: ");
		
		aplicacao.cadastrarReceita(remedio, paciente, inicio, quantidadeDias, quantidadeVezes, dosagem, medico);
		System.out.println("Receita cadastrada com sucesso.");
		int hora = Entrada.lerInt("Digite a hora em que você deseja tomar o remédio " + remedio + ": ");
		int[] horas = aplicacao.registrarPlanilha(hora);
		System.out.println("Planilha criada com sucesso. O remédio deve ser tomado nas seguintes horas:");
		for (int h : horas) {
			System.out.println(h + "h");
		}
	}

	private void reorganizar() {
		String remedio = Entrada.lerString("Digite o nome do remédio: ");
		int hora = Entrada.lerInt("Digite a hora em que o remédio foi tomado: ");
		
		if (aplicacao.reorganizarPlanilha(remedio, hora)) {
			System.out.println("Planilha reorganizada com sucesso");
		} else {
			System.out.println("Nenhuma planilha com este remédio está cadastrada.");
		}
	}

	private void registrarMedico() {
		String nome = Entrada.lerString("Digite o nome do médico: ");
		String crm = Entrada.lerString("Digite o número de CRM do médico: ");
		aplicacao.cadastrarMedico(nome, crm);
		System.out.println("Médico " + nome + " cadastrado com sucesso.");
	}

}
