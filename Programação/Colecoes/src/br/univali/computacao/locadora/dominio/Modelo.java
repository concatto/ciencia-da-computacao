/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package br.univali.computacao.locadora.dominio;

import br.univali.computacao.excecoes.MarcaInexistenteException;

/**
 *
 * @author 1978233
 */
public class Modelo {
    private String nome;
    private Marca marca;

    public Modelo() {
    }

    public Modelo(String nome, Marca marca) throws MarcaInexistenteException {
    	if (marca == null) throw new MarcaInexistenteException();
    	
        this.nome = nome;
        this.marca = marca;
    }

    /**
     * @return the nome
     */
    public String getNome() {
        return nome;
    }

    /**
     * @param nome the nome to set
     */
    public void setNome(String nome) {
        this.nome = nome;
    }

    /**
     * @return the marca
     */
    public Marca getMarca() {
        return marca;
    }

    /**
     * @param marca the marca to set
     */
    public void setMarca(Marca marca) {
        this.marca = marca;
    }
    
    @Override
    public String toString() {
    	return marca.getNome() + " " + nome;
    }
}
