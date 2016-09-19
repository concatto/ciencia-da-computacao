package asteroids.core;

import java.awt.Graphics2D;
import java.awt.Rectangle;
import javax.swing.ImageIcon;

public abstract class GameObject {

    private double x;
    private double y;
    private double anguloDoMovimento;
    private double velocidade;
    private boolean ativado = true;
    protected Sprite sprite;

    public GameObject() {
        x = y = anguloDoMovimento = velocidade = 0;
    }

    //+++++++++++++++++++++++++++
    public GameObject(String caminhoDaImagem, SpriteInfos infos) {
        this();//chama o construtor acima
        setSprite(caminhoDaImagem, infos);
    }

    public void setSprite(String caminhoDaImagem, SpriteInfos infos) {
        ImageIcon imagem = new ImageIcon(getClass().getResource(caminhoDaImagem));
        sprite = new Sprite(imagem.getImage(), infos);
    }

    //+++++++++++++++++++++++++++++++++++++
    public Rectangle getBounds() {
        return new Rectangle((int) getX(), (int) getY(), getLargura(), getAltura());
    }
    //+++++++++++++++++++++++++++++++++++++

    public void draw(Graphics2D g) {
        if (sprite != null) {
            int xDest = (int) getX();
            int yDest = (int) getY();
            int rightDest = xDest + (int) sprite.getLargura();
            int bottomDest = yDest + (int) sprite.getAltura();

            int quadroAtual = sprite.getQuadroAtual();
            SpriteInfos infos = sprite.getInfos();
            int xSource = (quadroAtual % infos.numeroDeQuadrosPorLinha) * infos.larguraDosQuadros;
            int ySource = (quadroAtual / infos.numeroDeQuadrosPorLinha) * infos.alturaDosQuadros;
            int rightSource = xSource + sprite.getLargura();
            int bottomSource = ySource + sprite.getAltura();

            //g.setTransform(new AffineTransform());
            g.drawImage(sprite.getImagem(),
                    xDest, yDest, rightDest, bottomDest,//coordenadas de destino 
                    xSource, ySource, rightSource, bottomSource, null);
        }
    }

    public void update(int frameTime) {
        double anguloEmRadianos = Math.toRadians(anguloDoMovimento);
        double vel = velocidade * frameTime / 1000.0;
        x += vel * Math.cos(anguloEmRadianos);
        y += vel * Math.sin(anguloEmRadianos);
        if (sprite != null) {
            sprite.atualiza(frameTime);
        }
    }

    public void setLocalizacao(double x, double y) {
        setX(x);
        setY(y);
    }

    public double getAnguloDoMovimento() {
        return anguloDoMovimento;
    }

    //+++++++++++++++++++++++++++
    public double getVelocidade() {
        return velocidade;
    }

    //+++++++++++++++++++++++++++
    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public int getAltura() {
        if (this.sprite != null) {
            return this.sprite.getAltura();
        }
        return 0;
    }

    public int getLargura() {
        if (this.sprite != null) {
            return this.sprite.getLargura();
        }
        return 0;
    }

    public void setAnguloDoMovimento(double anguloDoMovimento) {
        this.anguloDoMovimento = anguloDoMovimento;
    }

    public void setVelocidade(double velocidade) {
        this.velocidade = velocidade;
    }

    //+++++++++++++++++++++++++++
    public void setX(double x) {
        this.x = x;
    }

    public void setY(double y) {
        this.y = y;
    }

    public boolean estaAtivado() {
        return ativado;
    }

    public void setAtivado(boolean ativado) {
        this.ativado = ativado;
    }
}
