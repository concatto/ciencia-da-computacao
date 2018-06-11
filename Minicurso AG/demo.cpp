#include <iostream>
#include <vector>

// Em structs, todos os membros são públicos por padrão
struct Pagina {
    std::string conteudo;
    double integridade;

    Pagina(const std::string& conteudo, double integridade)
        : conteudo(conteudo), integridade(integridade) {
        // A lista inicializadora acima (após os dois pontos) realiza a atribuição aos membros da classe
    }
};

class LivroAntigo {
private:
    std::vector<Pagina> paginas;

public:
    LivroAntigo() {
        // Vazio
    }

//  void adicionarPagina(Pagina& pagina) {          // ERRO: impossível armazenar referência em um vector
//  void adicionarPagina(Pagina pagina) {           // AVISO: cópía desnecessária
    void adicionarPagina(const Pagina& pagina) {    // CORRETO: uma cópia é adicionada ao vector e o objeto é somente-leitura
        paginas.push_back(pagina);
    }

    void imprimir() {
        // Evita a criação desnecessária de cópias
        for (const Pagina& pagina : paginas) {
            std::cout << pagina.conteudo << "\n";
            std::cout << "Nível de integridade: " << pagina.integridade << "\n";
        }
    }

    std::string conteudoEntre(int inicio, int fim) {
        std::string conteudo = "";

        for (int i = inicio; i < fim; i++) {
            conteudo += paginas[i].conteudo + "\n";
        }

        return conteudo;
    }

    void rasgar() {
        // Referência é necessária pois os objetos serão modificados
        for (Pagina& pagina : paginas) {
            pagina.integridade = 0;
        }
    }
};

int main() {
    LivroAntigo livro;

    Pagina um("Tenores autem memoratarum litterarum sunt, qui sequuntur. Ac primum quidem pro Rituali Romano.", 0.5);
    Pagina dois("Datum Romae apud S. Mariam Majorem sub Annulo Piscatoris, die 17 Junii MDCXIV.", 0.8);

    livro.adicionarPagina(um);
    livro.adicionarPagina(dois);

    livro.imprimir();
}
