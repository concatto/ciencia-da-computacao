package br.univali.game.graphics;

import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.system.MemoryUtil.*;

import org.lwjgl.opengl.GL;

public class GLGraphics implements GraphicsAPI {
	private long window;
	private float width;
	private float height;
	
	public GLGraphics(long window, int width, int height) {
		this.window = window;
		this.width = width;
		this.height = height;
	}

	@Override
	public void clear() {
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	}

	@Override
	public void setColor(double red, double green, double blue) {
		glColor3d(red, green, blue);
		glClearColor((float) red, (float) green, (float) blue, 1);
	}

	@Override
	public void drawCircle(int x, int y, float radius) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void drawRectangle(int top, int left, int width, int height) {
		float x0 = ((left / this.width) * 2f) - 1;
		float y0 = ((top / this.height) * -2f) + 1;
		float x1 = (((left + width) / (this.width)) * 2f) - 1;
		float y1 = (((top + height) / (this.height)) * -2f) + 1;
		
		glRectf(x0, y0, x1, y1);
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
		
		return 0;
	}

	@Override
	public void drawImage(long image, int x, int y) {
		// TODO Auto-generated method stub
		
	}
}
