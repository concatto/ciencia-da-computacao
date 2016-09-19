package asteroids.objects;

import asteroids.core.GameObject;
import asteroids.core.SpriteInfos;

public class Asteroid extends GameObject {

    //+++++++++++++++++++++++++++
    public Asteroid() {
        super();
        int velocidadeDaAnimacao = 10 + (int) (Math.random() * 20);
        SpriteInfos infos = new SpriteInfos(64, 63, 64, 64, velocidadeDaAnimacao);

        setSprite("/resources/asteroids.png", infos);
    }
}
