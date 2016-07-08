/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package br.univali.computacao.locadora.dominio;

/**
 *
 * @author 1978233
 */
public class Cliente {
	private String nome;
	private String cpf;

    public Cliente() {
    }

    public Cliente(String nome, String cpf) {
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
