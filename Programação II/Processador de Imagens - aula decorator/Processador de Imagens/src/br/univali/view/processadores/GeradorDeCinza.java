package br.univali.view.processadores;

import java.awt.image.BufferedImage;

/**
 *
 * @author Elieser
 */
public class GeradorDeCinza implements Processador {
    private Processador processador = new ProcessadorNulo();

    public GeradorDeCinza(Processador processador) {
        this.processador = processador;
    }

    public GeradorDeCinza() {
    }
    
    
    
    @Override
    public BufferedImage processa(BufferedImage imagemOriginal) throws Exception {
        int largura = imagemOriginal.getWidth();
        int altura = imagemOriginal.getHeight();
        int tipoDeImagem = BufferedImage.TYPE_BYTE_GRAY;
        BufferedImage imagemTonsDeCinza = new BufferedImage(largura, altura, tipoDeImagem);

        imagemTonsDeCinza.getGraphics().drawImage(imagemOriginal, 0, 0, null);
        return processador.processa(imagemTonsDeCinza);
    }

}
