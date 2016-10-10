package br.univali.game.window;

import javax.swing.JFrame;

import br.univali.game.graphics.SwingGraphics;

public class SwingWindow extends GameWindow {
	private JFrame window;

	public SwingWindow(int width, int height) {
		super(width, height);
		
		window = new JFrame();
		window.setSize(width, height);
		graphics = new SwingGraphics(window);
	}

	@Override
	void draw() {
		// TODO Auto-generated method stub
		
	}
}
