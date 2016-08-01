package br.univali.programacao;

public class DetectorPalindromo {
	public DetectorPalindromo() {
		// TODO Auto-generated constructor stub
	}
	
	public boolean detectar(String frase) {
		for (int i = 0; i < frase.length() / 2; i++) {
			if (frase.charAt(i) != frase.charAt(frase.length() - 1 - i)) {
				return false;
			}
		}
		
		return true;
	}
}
