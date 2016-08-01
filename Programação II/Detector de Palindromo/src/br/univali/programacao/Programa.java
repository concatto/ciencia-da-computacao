package br.univali.programacao;

public class Programa {

	public static void main(String[] args) {
		Comunicador c = new ComunicadorGrafico();
		DetectorPalindromo detector = new DetectorPalindromo();
		
		if (detector.detectar(c.ler("Digite uma frase: "))) {
			c.escrever("Sim");
		} else {
			c.escrever("Não");
		}
	}

}