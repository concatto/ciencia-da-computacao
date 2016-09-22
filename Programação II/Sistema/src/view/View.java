package view;

import control.MenuFactory;
import java.awt.event.WindowFocusListener;
import java.util.List;
import model.Produto;

public interface View {

    /**
     * Constantes com opções disponíveis na tela do menu principal
     */
    public static final int CADASTRAR_PRODUTO = 0;
    public static final int VISUALIZAR_PRODUTOS_DISPONIVEIS = 2;
    public static final int BUSCAR_PRODUTO = 4;

    void adicionaListenerNoFormDeLogin(WindowFocusListener l);

    void exibeFormularioDeLogin();

    void buscaNaoEncontrada();

    String buscarProduto();

    /**
     * Tela que exibe uma mensagem de Erro occorido na busca
     */
    void erroBusca();

    /**
     * Tela do menu principal
     * @return Um inteiro contendo a opção escolhida pelo usuário na tela,
     * ou -1 caso o usuário cancele a execução do programa, tanto no botão
     * cancelar, quanto no botão fechar.
     */
    /**
     * Tela que exibe uma listagem vinda numa String formatada por parâmetro
     * 
     */
    void exibirProdutos(List<Produto> produtos);

    /**
     * Tela que exibe uma mensagem avisando que não há produtos cadastrados,
     * e uma possibilidade do erro que pode ter ocorrido
     */
    void semProdutosCadastrados();

    void recriaInterface();
    void setMenuFactory(MenuFactory menuFactory);
}
