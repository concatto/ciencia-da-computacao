package br.univali.game.graphics;

import javax.swing.JFrame;

public class SwingGraphics implements GraphicsAPI {
	private JFrame window;
	private int width;
	private int height;
	
	public SwingGraphics(JFrame window, int width, int height) {
		this.window = window;
		this.width = width;
		this.height = height;
	}

	@Override
	public void clear() {
		// TODO Auto-generated method stub
	}

	@Override
	public void setColor(double red, double green, double blue) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void drawCircle(int x, int y, float radius) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void drawRectangle(int top, int left, int width, int height) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void drawLine(int x1, int x2, int y1, int y2) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void drawLine(int x1, int x2, int y1, int y2, int thickness) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public long loadImage(String path) {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public void drawImage(long image, int x, int y) {
		// TODO Auto-generated method stub	
	}
}
