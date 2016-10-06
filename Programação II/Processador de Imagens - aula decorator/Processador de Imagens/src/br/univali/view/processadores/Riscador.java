package br.univali.view.processadores;

import java.awt.Graphics;
import java.awt.image.BufferedImage;

/**
 *
 * @author Elieser
 */
public class Riscador implements Processador {
    private Processador processador = new ProcessadorNulo();

    public Riscador(Processador processador) {
        this.processador = processador;
    }    

    public Riscador() {
    }
    
    @Override
    public BufferedImage processa(BufferedImage imagemOriginal) throws Exception {
        for (int i = 0; i < 50 + (Math.random() * 200.0); i++) { //100 riscos/linhas na imagem
            Graphics g = imagemOriginal.getGraphics();
            int x = (int) (Math.random() * imagemOriginal.getWidth());
            int y = (int) (Math.random() * imagemOriginal.getHeight());
            int x2 = (int) (Math.random() * imagemOriginal.getWidth());
            int y2 = (int) (Math.random() * imagemOriginal.getHeight());
            g.drawLine(x, y, x2, y2);
        }
        return processador.processa(imagemOriginal);
    }

}
