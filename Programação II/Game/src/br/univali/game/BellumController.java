package br.univali.game;

import br.univali.game.graphics.GraphicsAPI;
import br.univali.game.window.GameWindow;

public class BellumController {
	private GameWindow window;
	private GraphicsAPI api;

	public BellumController(GameWindow window) {
		this.window = window;
		this.api = window.getGraphics();
	}
	
	public void drawGame() {
		drawBackground();
		
		window.draw();
	}
	
	private void drawBackground() {
		api.setColor(0.5, 0.5, 1);
		api.clear();
		api.setColor(0.2, 13, 0.6);
		api.drawRectangle(window.getHeight() - 100, 0, window.getWidth(), 100);
	}
}
