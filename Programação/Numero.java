public class Numero {
  public static void main(String[] args) {
    int primeiro = Integer.parseInt(args[0]);
    int maior = primeiro;
    int menor = primeiro;
    double media = primeiro;

    for (int i = 1; i < args.length; i++) {
      int valor = Integer.parseInt(args[i]);
      if (valor > maior) {
        maior = valor;
      }
      if (valor < menor) {
        menor = valor;
      }

      media += valor;
    }
    media /= args.length;
    System.out.println("Maior: " + maior + "; Menor: " + menor + "; Media: " + media);
  }
}
