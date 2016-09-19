package asteroids.objects;

import asteroids.core.GameObject;
import asteroids.core.SpriteInfos;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.geom.AffineTransform;

public class Nave extends GameObject {

    private static final double VELOCIDADE_MAXIMA = 150;
    private static final double SPEED_FACTOR = 0.3;
    private boolean acelerando = false;
    private double anguloDaFace;

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public Nave() {
        super();
        anguloDaFace = Math.random() * 360;
        SpriteInfos infos = new SpriteInfos(38, 40);
        setSprite("/resources/nave.png", infos);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    @Override
    public void update(int frameTime) {
        super.update(frameTime);
        if (estaAcelerando()) {
            double velocidade = getVelocidade();
            if (velocidade == 0) {//ainda não iniciou o movimento
                velocidade = SPEED_FACTOR * 5;//inicia com uma velocidade bem pequena
            }
            setVelocidade(velocidade + (velocidade * SPEED_FACTOR));
            if (Math.abs(velocidade) > VELOCIDADE_MAXIMA) {
                setVelocidade(VELOCIDADE_MAXIMA);
            }
        } else {
            //vai diminuindo a velocidade gradativamente
            setVelocidade(getVelocidade() * 0.98);
            if (getVelocidade() < SPEED_FACTOR)//arredondar a velocidade para zero
            {
                setVelocidade(0);
            }
        }
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    @Override
    public void draw(Graphics2D g) {
        //desenha linhas dos foguetes da nave
        g.setTransform(new AffineTransform());
        g.rotate(Math.toRadians(anguloDaFace), getBounds().getCenterX(), getBounds().getCenterY());
        
        g.translate( getBounds().getCenterX(), getBounds().getCenterY());
        int numeroDeLinhasDoFoguete = (int) (((getVelocidade() / VELOCIDADE_MAXIMA) * 200) / 5);
        for (int i = 0; i < numeroDeLinhasDoFoguete; i++) {
            double tam = (getAltura()/4  * getVelocidade() / VELOCIDADE_MAXIMA);
            desenhaLinhaAleatoria(g, -getLargura() /12-5, getLargura() /12+5, 2, 2 + (int) tam);
        }
        
        //desenha imagem da nave
        g.translate( -getBounds().getCenterX(), -getBounds().getCenterY());
        super.draw(g);
        
    }
    //++++++++++++++++++++++++++++++++++++++

    private void desenhaLinhaAleatoria(Graphics2D g, int limiteHorizontalInferior, int limiteHorizontalSuperior, int tamanhoMinimoDaLinha, int tamanhoMaximoDaLinha) {
        double x = Math.random() * (limiteHorizontalSuperior - limiteHorizontalInferior) + limiteHorizontalInferior;
        double centro = (limiteHorizontalSuperior - limiteHorizontalInferior)/2 + limiteHorizontalInferior;
        double tamanhoDaLinha = Math.random() * (tamanhoMaximoDaLinha - tamanhoMinimoDaLinha) + tamanhoMaximoDaLinha;
        Color cor = new Color(255, 50 + (int)(Math.random() * 55), 50 + (int)(Math.random() * 55), 10);
        g.setColor(cor);
        
        g.drawLine((int) x, getAltura() / 3, (int) centro , getAltura() / 2 + (int) tamanhoDaLinha);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    public double getAnguloDaFace() {
        return anguloDaFace;
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public void viraPraDireita(){
        setAnguloDaFace(anguloDaFace + 2);
    }
    
    public void viraPraEsquerda(){
        setAnguloDaFace(anguloDaFace - 2);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    public void setAnguloDaFace(double angulo) {
        if (angulo >= 0 && angulo < 360) {
            this.anguloDaFace = angulo;
        } else if (angulo < 0) {
            this.anguloDaFace = 360 + angulo;
        } else if (angulo > 360) {
            this.anguloDaFace = angulo % 360;
        }
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    public boolean estaAcelerando() {
        return acelerando;
    }

    public void setAcelerando(boolean acelerando) {
        this.acelerando = acelerando;
        if (acelerando) {
            setAnguloDoMovimento(anguloDaFace - 90);
        }
    }
}
