package br.univali.game.window;

import br.univali.game.graphics.GLGraphics;
import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.system.MemoryUtil.*;

import org.lwjgl.opengl.GL;

public class GLWindow extends GameWindow {
	private long window;
	
	public GLWindow(int width, int height) {
		super(width, height);
		
		glfwInit();
		window = glfwCreateWindow(width, height, "", NULL, NULL);
		graphics = new GLGraphics(window);
		
		glfwMakeContextCurrent(window);
		GL.createCapabilities();
	}

	@Override
	void draw() {
		// TODO Auto-generated method stub
		
	}

}
