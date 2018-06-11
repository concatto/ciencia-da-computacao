import java.util.List;
import java.util.ArrayList;

public class Demo {
    static class Pagina {
        public String conteudo;
        public double integridade;

        public Pagina(String conteudo, double integridade) {
            this.conteudo = conteudo;
            this.integridade = integridade;
        }
    }

    static class LivroAntigo {
        // Ao contrário do C++, é necessário inicializar a lista explicitamente
        private List<Pagina> paginas = new ArrayList<>();

        // No Java deve-se prefixar todos os campos e funções com a visibilidade
        public LivroAntigo() {
            // Vazio
        }

        // No Java não há opção de passar por somente-leitura ou por cópia.
        // Por padrão, a passagem é por referência (exceto para primitivos, que são passados por valor)
        public void adicionarPagina(Pagina pagina) {
            paginas.add(pagina);
        }

        public void imprimir() {
            // Novamente não há opção de controle de acesso
            for (Pagina pagina : paginas) {
                System.out.println(pagina.conteudo);
                System.out.println("Nível de integridade: " + pagina.integridade);
            }
        }

        public String conteudoEntre(int inicio, int fim) {
            String conteudo = "";

            for (int i = inicio; i < fim; i++) {
                conteudo += paginas.get(i).conteudo + "\n";
            }

            return conteudo;
        }

        public void rasgar() {
            // Objetos são referências por padrão
            for (Pagina pagina: paginas) {
                pagina.integridade = 0;
            }
        }
    }

    public static void main(String[] args) {
        LivroAntigo livro = new LivroAntigo();

        Pagina um = new Pagina("Tenores autem memoratarum litterarum sunt, qui sequuntur. Ac primum quidem pro Rituali Romano.", 0.5);
        Pagina dois = new Pagina("Datum Romae apud S. Mariam Majorem sub Annulo Piscatoris, die 17 Junii MDCXIV", 0.8);

        livro.adicionarPagina(um);
        livro.adicionarPagina(dois);
        
        livro.imprimir();
    }
}
