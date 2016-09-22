package control;

import java.awt.event.WindowEvent;
import java.awt.event.WindowFocusListener;
import java.util.List;
import javax.swing.JOptionPane;
import model.Loja;
import model.Produto;
import model.Usuario;
import view.FormLogin;
import view.View;

public class Controlador {

    private final View view;
    private final Loja loja;

    public Controlador(final View view, final Loja loja) {
        this.view = view;
        this.loja = loja;

        view.adicionaListenerNoFormDeLogin(new WindowFocusListener() {

            @Override
            public void windowGainedFocus(WindowEvent e) {
            }

            @Override
            public void windowLostFocus(WindowEvent e) {

                Usuario user = ((FormLogin) e.getWindow()).getUsuario();
                verificaDadosDeLogin(user.getNomeDeUsuario(), user.getSenha());
                
            }
        });
    }

    public Usuario getUsuario() {
        return this.loja.getUsuario();
    }

    public void iniciarApp() {
        if (!loja.usuarioEstaLogado()) {
            view.exibeFormularioDeLogin();
        }
    }

    //++++++++++++++++++++++++++
    private void cadastrarProduto() {
    }
    //++++++++++++++++++++++++++++++++++

    public void listaProdutosCadastrados() {
        List<Produto> produtos = loja.listarProdutosDisponíveis();
        if (produtos == null || produtos.isEmpty()) {
            view.semProdutosCadastrados();
            return;
        }
        view.exibirProdutos(produtos);
    }

    public void iniciarBuscaDeProduto() {
        String busca = view.buscarProduto();

        List<Produto> produtos = this.loja.getProdutos(busca);

        if (produtos == null) {
            view.erroBusca();
            return;
        }

        if (produtos.isEmpty()) {
            view.buscaNaoEncontrada();
            return;
        }

        view.exibirProdutos(produtos);
    }
    //+++++++++++++++++++++++++++++++++++++++++

    public void verificaDadosDeLogin(String nomeDoUsuario, String senha) {
        Usuario usuario = loja.autenticaUsuario(nomeDoUsuario, senha);
        if (usuario != null) {//está autenticado
            view.setMenuFactory(MenuFactoryGenerator.createMenuFactory(usuario));
            view.recriaInterface();
        } else {
            JOptionPane.showMessageDialog(null, "Senha ou nome de usuário inválido!");
        }

    }
}
