package asteroids.objects;

import asteroids.core.GameObject;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.geom.AffineTransform;

public class TiroDaNave extends GameObject {

    private static final int TAMANHO = 5;
    private static final Color COR_DOS_TIROS = Color.ORANGE;
    
   
    @Override
    public Rectangle getBounds() {
        return new Rectangle((int)getX(), (int)getY(), TAMANHO, TAMANHO);
    }

    @Override
    public void draw(Graphics2D g) {
        g.setTransform(new AffineTransform());
        g.translate(getX(), getY());
        
        g.setColor(COR_DOS_TIROS);
        g.fillOval(-TAMANHO/2, -TAMANHO/2, TAMANHO, TAMANHO);
        
        g.translate(-getX(), -getY());
    }
}
