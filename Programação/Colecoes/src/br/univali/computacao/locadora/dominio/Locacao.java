/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package br.univali.computacao.locadora.dominio;

import br.univali.computacao.locadora.excecoes.ItemInexistenteException;
import br.univali.computacao.locadora.excecoes.QuilometragemIncorretaException;

/**
 *
 * @author 1978233
 */
public class Locacao {
    private Cliente cliente;
    private Veiculo veiculo;
    private int kmInicial;
    private double valorKm;
    private int kmFinal;
    private boolean ativa;

    public Locacao(Cliente cliente, Veiculo veiculo) throws ItemInexistenteException {
    	if (veiculo == null) throw new ItemInexistenteException("O veículo não existe.");
    	if (cliente == null) throw new ItemInexistenteException("O cliente não existe.");
    	
        this.cliente = cliente;
        this.veiculo = veiculo;
        this.kmInicial = veiculo.getKm();
        this.kmFinal = 0;
        this.valorKm = veiculo.getValorKm();
        this.ativa = true;
    }
    
    public void finalizar(int kmAtual) throws QuilometragemIncorretaException {
    	if (kmAtual < veiculo.getKm()) {
    		throw new QuilometragemIncorretaException("A quilometragem final é menor do que a inicial.");
    	}
    	
        this.veiculo.setKm(kmAtual);
        this.kmFinal = kmAtual;
        this.ativa = false;
    }
    
    public double valorTotal() {
        return (this.kmFinal - this.kmInicial) * this.valorKm;
    }
    
    public boolean estaAtiva() {
        return this.ativa;
    }

    /**
     * @return the cliente
     */
    public Cliente getCliente() {
        return cliente;
    }

    /**
     * @param cliente the cliente to set
     */
    public void setCliente(Cliente cliente) {
        this.cliente = cliente;
    }

    /**
     * @return the veiculo
     */
    public Veiculo getVeiculo() {
        return veiculo;
    }

    /**
     * @param veiculo the veiculo to set
     */
    public void setVeiculo(Veiculo veiculo) {
        this.veiculo = veiculo;
    }
    
    @Override
    public String toString() {
    	return String.format("Veículo %s alugado para %s. %s.", veiculo.getPlaca(), cliente.getNome(), ativa ? "Ativa" : "Terminada");
    } 
    
}
