package br.univali.computacao.locadora;

import java.io.IOException;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;

public class Entrada {
	private static Scanner scanner = new Scanner(System.in);
	private static DateFormat formatoData = new SimpleDateFormat("dd/MM/yyyy");
	
	public static int lerInt(String mensagem) {
		System.out.print(mensagem);
		return scanner.nextInt();
	}
	
	public static double lerDouble(String mensagem) {
		System.out.print(mensagem);
		return scanner.nextDouble();
	}
	
	public static String lerString(String mensagem) {
		System.out.print(mensagem);
		String str = "";
		while (str.isEmpty()) {
			str = scanner.nextLine();
		}
		return str;
	}
	
	public static Date lerData(String mensagem) {
		String s = lerString(mensagem);
		try {
			return formatoData.parse(s);
		} catch (ParseException e) {
			e.printStackTrace();
			return null;
		}
	}
	
	public static void aguardarEntrada(String mensagem) {
		System.out.println(mensagem);
		try {
			System.in.read();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			scanner.nextLine();
		}
	}
}