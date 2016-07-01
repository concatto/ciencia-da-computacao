/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package br.univali.computacao.locadora.dominio;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.SortedMap;
import java.util.TreeMap;

/**
 *
 * @author 1978233
 */
public class Locadora {
    SortedMap<String, Veiculo> veiculos;
    Map<String, Cliente> clientes;
    List<Locacao> locacoes;
    List<Marca> marcas;
    List<Modelo> modelos;

    public Locadora() {
        this.marcas = new ArrayList<>();
        this.marcas.add(new Marca("Fiat"));
        this.marcas.add(new Marca("Volkswagen"));
        this.marcas.add(new Marca("BMW"));
        this.marcas.add(new Marca("Citroën"));
        
        this.modelos = new ArrayList<>();
        this.modelos.add(new Modelo("Aircross", this.marcas.get(3)));
        this.modelos.add(new Modelo("C4 Grand Picasso", this.marcas.get(3)));
        this.modelos.add(new Modelo("147", this.marcas.get(0)));
        this.modelos.add(new Modelo("Fusca", this.marcas.get(1)));
        this.modelos.add(new Modelo("Uno", this.marcas.get(0)));
        this.modelos.add(new Modelo("M3", this.marcas.get(2)));
        this.modelos.add(new Modelo("X2", this.marcas.get(2)));
        this.modelos.add(new Modelo("Brasília", this.marcas.get(1)));
        this.modelos.add(new Modelo("C3", this.marcas.get(3)));
        
        this.veiculos = new TreeMap<>();
        this.clientes = new HashMap<>();
        this.locacoes = new ArrayList<>();
    }
    
    public void adicionarCliente(Cliente cliente) {
        this.clientes.put(cliente.getCpf(), cliente);
    }

    public void adicionarVeiculo(Veiculo veiculo) {
        this.veiculos.put(veiculo.getPlaca(), veiculo);
    }
    
    public Locacao alugarVeiculo(Veiculo veiculo, Cliente cliente) {
        Locacao locacao = new Locacao(cliente, veiculo);
        this.locacoes.add(locacao);
        return locacao;
    }
    
    public void finalizarLocacao(Veiculo veiculo, int kmAtual) {
        for (Locacao locacao : locacoes) {
            if (locacao != null && locacao.getVeiculo().equals(veiculo) && locacao.estaAtiva()) {
                locacao.finalizar(kmAtual);
                break;
            }
        }
    }
    
    public void finalizarLocacao(String placa, int kmAtual) {
    	finalizarLocacao(veiculos.get(placa), kmAtual);
    }

    public List<Modelo> getModelos() {
		return modelos;
	}
    
    public SortedMap<String, Veiculo> getVeiculos() {
		return veiculos;
	}
     
    public Cliente buscarCliente(String cpf) {
    	return clientes.get(cpf);
    }
    
    public Veiculo buscarVeiculo(String placa) {
    	return veiculos.get(placa);
    }
    
    public Map<String, Cliente> getClientes() {
		return clientes;
	}
}
