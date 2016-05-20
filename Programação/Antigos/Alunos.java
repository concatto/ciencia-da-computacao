public class Alunos {
    public static void main(String[] args) {
        int soma = 0;
        for (int i = 0; i < args.length; i++) {
            int valor = Integer.parseInt(args[i]);
            System.out.print("Aluno " + (i + 1) + ": ");
            for (int j = 0; j < valor; j++) {
                System.out.print("*");
            }
            System.out.println();
            soma += valor;
        }

        System.out.println("Media: " + (soma / (double) args.length));
    }
}
