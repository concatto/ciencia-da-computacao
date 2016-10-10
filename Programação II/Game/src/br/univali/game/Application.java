package br.univali.game;

import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.system.MemoryUtil.*;

import org.lwjgl.glfw.GLFWErrorCallback;
import org.lwjgl.opengl.GL;

public class Application {
	public Application() {
		GLFWErrorCallback.createPrint(System.err).set();
		glfwInit();
		long window = glfwCreateWindow(640, 480, "Teste", NULL, NULL);
		glfwMakeContextCurrent(window);
		glfwShowWindow(window);
		
		
		GL.createCapabilities();
		glClearColor(0, 0, 0, 1);
		float red = 0;
		while (true) {
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			
			glColor3f(1, 1, 1);
			glRectf(0, 0, 1, 1);
			
			glClearColor(red, 0, 0, 1);
			
			red += 0.0001;
			if (red > 1) red = 0;
			
			glfwSwapBuffers(window);
		}
	}
	
	
	public static void main(String[] args) {
		new Application();
	}

}
