package br.univali.concatto.banco;

import java.util.ArrayList;
import java.util.List;

public class Banco {
	private List<Cliente> clientes = new ArrayList<>();
	private List<Conta> contas = new ArrayList<>();
	
	public Banco() {
		
	}
	
	public static void main(String[] args) {
		new Banco();

		
	}

}
