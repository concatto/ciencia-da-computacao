package br.univali.view.processadores;

import java.awt.image.BufferedImage;

public interface Processador {
    BufferedImage processa(BufferedImage imagemOriginal) throws Exception;
   
}
