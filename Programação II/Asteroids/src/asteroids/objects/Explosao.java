package asteroids.objects;

import asteroids.core.Sprite;
import asteroids.core.GameObject;
import asteroids.core.SpriteInfos;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.geom.AffineTransform;
import javax.swing.ImageIcon;

public class Explosao extends GameObject {

    private static Image imagemDaExplosao;

    private Explosao() {
        super();
    }

    
    public static Explosao criaExplosao() {
        if (imagemDaExplosao == null) {
            imagemDaExplosao = new ImageIcon(Explosao.class.getResource("/resources/explosao.png")).getImage();
        }

        Explosao explosao = new Explosao();
        SpriteInfos infos = new SpriteInfos(36, 46, 6, 18, 15);
        explosao.sprite = new Sprite(imagemDaExplosao, infos);
        return explosao;
    }

    @Override
    public Rectangle getBounds() {
        return new Rectangle((int) getX(), (int) getY(), sprite.getLargura(), sprite.getAltura());
    }

    @Override
    public void update(int frameTime) {
        super.update(frameTime);
        //desativa o objeto quando a animação da explosão chega no último quadro
        if (sprite.getQuadroAtual() == sprite.getInfos().numeroDeQuadros - 1) {
            this.setAtivado(false);
        }
        sprite.atualiza(frameTime);
    }

    @Override
    public void draw(Graphics2D g) {
        //calcula os pixels em que a imagem será desenhada na tela
        int xDest = (int) getX();
        int yDest = (int) getY();
        int rightDest = xDest + (int) sprite.getLargura();
        int bottomDest = yDest + (int) sprite.getAltura();

        int quadroAtual = sprite.getQuadroAtual();
        SpriteInfos infos = sprite.getInfos();

        //calcula os pixels a partir de onde a imagem deve ser copiada
        int xSource = (quadroAtual % infos.numeroDeQuadrosPorLinha) * infos.larguraDosQuadros;
        int ySource = (quadroAtual / infos.numeroDeQuadrosPorLinha) * infos.alturaDosQuadros;
        int rightSource = xSource + sprite.getLargura();
        int bottomSource = ySource + sprite.getAltura();

        g.setTransform(new AffineTransform());
        
        //desenha apenas uma parte da imagem (o quadro atual) na tela 
        g.drawImage(sprite.getImagem(),
                xDest, yDest, rightDest, bottomDest,//coordenadas de destino 
                xSource, ySource, rightSource, bottomSource, null);
        
               
    }
}
