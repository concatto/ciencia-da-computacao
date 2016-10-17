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
		graphics = new GLGraphics(window, width, height);
		
		glfwMakeContextCurrent(window);
		glfwShowWindow(window);
		GL.createCapabilities();
	}

	@Override
	public void draw() {
		glfwSwapBuffers(window);
	}

}
