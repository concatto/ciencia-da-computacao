package br.univali.game.graphics;

public interface GraphicsAPI {
	void initialize();
	void clear();
	void setColor(int red, int green, int blue);
	void setColor(float red, float green, float blue);
	void drawCircle(int x, int y, float radius);
	void drawRectangle(int top, int left, int width, int height);
	void drawLine(int x1, int x2, int y1, int y2);
	void drawLine(int x1, int x2, int y1, int y2, int thickness);
}
