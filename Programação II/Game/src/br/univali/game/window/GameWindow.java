package br.univali.game.window;

import br.univali.game.graphics.GraphicsAPI;

public abstract class GameWindow {
	protected GraphicsAPI graphics;
	protected int width;
	protected int height;
	
	public GameWindow(int width, int height) {
		this.width = width;
		this.height = height;
	}
	
	abstract void draw();
}
