/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package br.univali.computacao.locadora.dominio;

import br.univali.computacao.locadora.excecoes.NomeNuloException;

/**
 *
 * @author 1978233
 */
public class Cliente {
	private String nome;
	private String cpf;

    public Cliente() {
    }

    public Cliente(String nome, String cpf) throws NomeNuloException {
    	if (nome == null) throw new NomeNuloException("O nome do cliente não pode ser nulo.");
		this.nome = nome;
		this.cpf = cpf;
    }

    public String getCpf() {
		return cpf;
	}
    
    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }
  
    @Override
    public String toString() {
    	return nome + " (CPF: " + cpf + ")";
    }
}
