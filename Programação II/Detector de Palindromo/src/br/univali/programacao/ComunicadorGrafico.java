package br.univali.programacao;

import javax.swing.JOptionPane;

public class ComunicadorGrafico implements Comunicador {

	@Override
	public String ler() {
		return ler("Digite: ");
	}

	@Override
	public String ler(String mensagem) {
		return JOptionPane.showInputDialog(mensagem);
	}

	@Override
	public void escrever(String mensagem) {
		JOptionPane.showMessageDialog(null, mensagem);
	}

}
