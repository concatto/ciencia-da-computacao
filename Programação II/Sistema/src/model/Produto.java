/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

/**
 *
 * @author Eduardo
 */
public class Produto {
    
    public static final String TABELA_PRODUTOS = "produtos";
    
    private String detalhes;
    private float preco;
    private int id;
    private String nome;

    /**
     * Construtor que preenche todos os atributos
     * @param descricao Descrição do produto
     * @param distribuicaoLinux Distribuição linux ao qual o produto pertence
     * @param preco Preço do produto
     * @param codigoProduto Código do produto
     */
    public Produto(String nome, String descricao, float preco, int codigoProduto) {
        this.detalhes = descricao;
        this.preco = preco;
        this.id = codigoProduto;
        this.nome = nome;
    }

    /**
     * Obter o código do produto
     * @return O código do produto
     */
    public int getCodigoProduto() {
        return getId();
    }

    /**
     * Obter a descrição do produto
     * @return A descrição do produto
     */
    public String getDescricao() {
        return getDetalhes();
    }

  
    /**
     * Obter o preço do produto
     * @return O preço do produto
     */
    public float getPreco() {
        return preco;
    }
    
    

    public String getDetalhes() {
        return detalhes;
    }

    public void setDetalhes(String detalhes) {
        this.detalhes = detalhes;
    }

    public void setPreco(float preco) {
        this.preco = preco;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

}
