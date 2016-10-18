package br.univali.game.graphics;

public interface GraphicsAPI {
	void clear();
	void setColor(double red, double green, double blue);
	void drawCircle(int x, int y, float radius);
	void drawRectangle(int top, int left, int width, int height);
	void drawLine(int x1, int x2, int y1, int y2);
	void drawLine(int x1, int x2, int y1, int y2, int thickness);
	long loadImage(String path);
	void drawImage(long image, int x, int y);
}
