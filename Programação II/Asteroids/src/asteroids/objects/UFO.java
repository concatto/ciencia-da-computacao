package asteroids.objects;

import asteroids.core.GameObject;
import asteroids.core.SpriteInfos;

public class UFO extends GameObject {

    //+++++++++++++++++++++++++++
    public UFO() {
        super("/resources/TheUfo.png",
                new SpriteInfos(38, 25, 8, 40, 20));
    }
}
