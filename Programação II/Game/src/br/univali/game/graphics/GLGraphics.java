package br.univali.game.graphics;

import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.system.MemoryUtil.*;

import org.lwjgl.opengl.GL;

public class GLGraphics implements GraphicsAPI {
	private long window;
	
	public GLGraphics(long window) {
		
	}

	@Override
	public void clear() {
		
	}

	@Override
	public void setColor(int red, int green, int blue) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void setColor(float red, float green, float blue) {
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
	public void initialize() {
		glfwInit();
		long window = glfwCreateWindow(640, 480, "Teste", NULL, NULL);
		glfwMakeContextCurrent(window);
		glfwShowWindow(window);
	}
}
