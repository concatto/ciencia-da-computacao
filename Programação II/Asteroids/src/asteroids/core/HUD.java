package asteroids.core;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.geom.AffineTransform;

public class HUD extends GameObject {

    private int fps = 0;
    private int quadroAtual = 0;
    private AcumuladorDeTempo acumulador = new AcumuladorDeTempo(1000);
    
    private Color corDoFundo = new Color(255, 255, 255, 127);
    private Color corDaFonte = Color.RED;
    
    private int inimigosAtivos = 0;

    @Override
    public void update(int frameTime) {
        super.update(frameTime);
        acumulador.atualiza(frameTime);
        quadroAtual++;
        if( acumulador.expirou() ){
            acumulador.reseta();
            fps = quadroAtual;
            quadroAtual = 0;
        }
    }
    
    public void setInimigosAtivos(int numeroDeInimigos){
        inimigosAtivos = numeroDeInimigos;
    }
    
    @Override
    public void draw(Graphics2D g) {
        g.setTransform( new AffineTransform());
        g.setColor(corDaFonte);
        g.drawString("FPS: " + fps, 50, 50);
        g.drawString("inimigos: " + inimigosAtivos, 50, 65);
    }

    public void setCorDoFundo(Color corDoFundo) {
        this.corDoFundo = corDoFundo;
    }

    public void setCorDaFonte(Color corDaFonte) {
        this.corDaFonte = corDaFonte;
    }

    @Override
    public Rectangle getBounds() {
        throw new UnsupportedOperationException("Not supported yet.");
    }
    
}
