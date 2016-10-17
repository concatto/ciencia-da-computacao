package br.univali.game;

import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.system.MemoryUtil.*;

import org.lwjgl.glfw.GLFWErrorCallback;
import org.lwjgl.opengl.GL;

import br.univali.game.graphics.GraphicsAPI;
import br.univali.game.window.GLWindow;
import br.univali.game.window.GameWindow;

public class Application {
	public Application() {
		GameWindow window = new GLWindow(640, 480);
		BellumController b = new BellumController(window);
		
		while (true) {
			b.drawGame();
		}
		
		/*
		glfwInit();
		long window = glfwCreateWindow(640, 480, "Teste", NULL, NULL);
		glfwMakeContextCurrent(window);
		glfwShowWindow(window);
		GL.createCapabilities();
		
		while (true) {
			glClearColor(0, 0, 0, 1);
			glColor3f(1, 1, 1);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			
			glClearColor(0, 0, 0, 1);
			glColor3f(1, 1, 1);			
			glRectf(0, 0, 1, 1);
						
			glfwSwapBuffers(window);
		}*/
	}
	
	
	public static void main(String[] args) {
		new Application();
	}

}
