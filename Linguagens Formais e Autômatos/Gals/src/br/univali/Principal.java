package br.univali;

public class Principal {
	public static void main(String[] args) {
		Sintatico sintatico = new Sintatico();
		Lexico lexico = new Lexico("4 * -(2 + 3) / 2 - 3");
		Semantico semantico = new Semantico();
		
		try {
			sintatico.parse(lexico, semantico);
			System.out.println(semantico.getResult());
		} catch (LexicalError | SyntaticError | SemanticError e) {
			e.printStackTrace();
		}
	}
}
