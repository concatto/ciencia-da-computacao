
package br.univali.view.processadores;

import java.awt.image.BufferedImage;

public class ProcessadorNulo implements Processador{

    @Override
    public BufferedImage processa(BufferedImage imagemOriginal) throws Exception {
        return imagemOriginal; //retorna a imagem original sem modificá-la
    }
    
}
