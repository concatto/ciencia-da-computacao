package model;

import java.util.ArrayList;
import java.util.List;
import javax.swing.JOptionPane;

public class Loja {

    private Usuario usuario;
    private static List<Produto> produtos = new ArrayList<Produto>();

    public Loja() {
        produtos.add(new Produto("Note book", "HD 500 GB, 4 GB RAM", 2200, 1));
        produtos.add(new Produto("PC", "HD 1 TB, 4 GB RAM", 1800, 2));
        produtos.add(new Produto("MOUSE sem fio", "USB", 35, 3));
    }

    public Usuario getUsuario() {
        return usuario;
    }

//    public void setUsuario(Usuario novoUsuario) {
//        this.usuario = novoUsuario;
//    }
    public boolean usuarioEstaLogado() {
        return usuario != null;
    }

    public List<Produto> listarProdutosDisponíveis() {
        return produtos;
    }

    public boolean adicionarNovoProduto(Produto novoProduto) {
        if (novoProduto != null && !produtos.contains(novoProduto)) {
            produtos.add(novoProduto);
            return true;
        } else {
            JOptionPane.showMessageDialog(null, "Problema na inserção de produto!");
        }
        return false;
    }

    public Produto buscarProdutoPorCodigo(int codigoProduto) {
        List<Produto> produtos = this.listarProdutosDisponíveis();

        if (produtos.isEmpty()) {
            return null;
        }

        for (Produto produto : produtos) {
            if (produto.getCodigoProduto() == codigoProduto) {
                return produto;
            }
        }
        return null;
    }

    public List<Produto> getProdutos(String termoDeBusca) {
        String termo = termoDeBusca.toLowerCase();
        List<Produto> produtosEncontrados = new ArrayList<Produto>();
        for (Produto produto : produtos) {
            String descricao = produto.getDescricao().toLowerCase();
            String nome = produto.getNome();
            if (descricao.contains(termo) || nome.contains(termo)) {
                produtosEncontrados.add(produto);
            }
        }
        return produtosEncontrados;
    }

    public Usuario autenticaUsuario(String nomeDoUsuario, String senhaDoUsuario) {
        boolean autenticou = false;
        if ("admin".equals(nomeDoUsuario) && "admin".equals(senhaDoUsuario)) {
            this.usuario = new Usuario(nomeDoUsuario, senhaDoUsuario, true);
            autenticou = true;
        } else if ("atendente".equals(nomeDoUsuario) && "atendente".equals(senhaDoUsuario)) {
            this.usuario = new Usuario(nomeDoUsuario, senhaDoUsuario, false);
            autenticou = true;
        }
        if (autenticou) {
            return this.usuario;
        }
        return null;
    }
}
