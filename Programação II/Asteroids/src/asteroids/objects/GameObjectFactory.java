package asteroids.objects;

import asteroids.core.GameObject;

public class GameObjectFactory {
	public static GameObject createObject(GameObjectType type) {
		switch (type) {
		case ASTEROID:
			return new Asteroid();
		case UFO:
			return new UFO();
		case PROJECTILE:
			return new TiroDaNave();
		}
		
		return null;
	}
}
