package br.univali.programacao;

import java.util.Scanner;

public class ComunicadorConsole implements Comunicador {
	private Scanner scanner;
	
	public ComunicadorConsole() {
		scanner = new Scanner(System.in);
	}
	
	@Override
	public String ler() {
		return scanner.nextLine();
	}

	@Override
	public void escrever(String mensagem) {
		System.out.println(mensagem);
	}

	@Override
	public String ler(String mensagem) {
		escrever(mensagem);
		return ler();
	}

}
