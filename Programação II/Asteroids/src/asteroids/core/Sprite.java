
package asteroids.core;

import java.awt.Image;

import javax.swing.JOptionPane;

public class Sprite {
    
    private Image imagem;
    private SpriteInfos infos;
    private AcumuladorDeTempo temporizadorDaAnimacao;
    private int quadroAtual = 0;
    
    public Sprite(Image imagem, int largura, int altura) {
        this.imagem = imagem;
        if( this.imagem == null )
            JOptionPane.showMessageDialog(null, "Imagem nula!");
        infos = new SpriteInfos(largura, altura);
    }
    
    public Sprite(Image imagem){
        this(imagem, imagem.getWidth(null), imagem.getHeight(null));
    }
    
    public Sprite(Image imagem, SpriteInfos infos){
        this(imagem, 0, 0);
        this.infos = infos;
        try {
            long tempoDeCadaQuadro = infos.getTempoDeCadaQuadro();
            if( tempoDeCadaQuadro > 0 ){
                temporizadorDaAnimacao = new AcumuladorDeTempo( tempoDeCadaQuadro );
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
    
   
    public int getLargura(){
        return infos.larguraDosQuadros;
    }
    
    public int getAltura(){
        return infos.alturaDosQuadros;
    }
    
    public void atualiza(long tempoEntreQuadros){
        if( temporizadorDaAnimacao != null){
            temporizadorDaAnimacao.atualiza(tempoEntreQuadros);
            if( temporizadorDaAnimacao.expirou() ){
                quadroAtual = (quadroAtual + 1) % infos.numeroDeQuadros;
                temporizadorDaAnimacao.reseta();
            }
        }
    }

    public Image getImagem() {
        return imagem;
    }

    public SpriteInfos getInfos() {
        return infos;
    }

    public AcumuladorDeTempo getTemporizadorDaAnimacao() {
        return temporizadorDaAnimacao;
    }

    public int getQuadroAtual() {
        return quadroAtual;
    }

}
