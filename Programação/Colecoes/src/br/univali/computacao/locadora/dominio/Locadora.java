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
    private SortedMap<String, Veiculo> veiculos;
    private Map<String, Cliente> clientes;
    private List<Locacao> locacoes;
    private List<Marca> marcas;
    private List<Modelo> modelos;

    public Locadora() {
        this.marcas = new ArrayList<>();
        adicionarMarca(new Marca("Fiat"));
        adicionarMarca(new Marca("Volkswagen"));
        adicionarMarca(new Marca("BMW"));
        adicionarMarca(new Marca("Citroën"));
        
        this.modelos = new ArrayList<>();
        adicionarModelo(new Modelo("Aircross", this.marcas.get(3)));
        adicionarModelo(new Modelo("C4 Grand Picasso", this.marcas.get(3)));
        adicionarModelo(new Modelo("147", this.marcas.get(0)));
        adicionarModelo(new Modelo("Fusca", this.marcas.get(1)));
        adicionarModelo(new Modelo("Uno", this.marcas.get(0)));
        adicionarModelo(new Modelo("M3", this.marcas.get(2)));
        adicionarModelo(new Modelo("X2", this.marcas.get(2)));
        adicionarModelo(new Modelo("Brasília", this.marcas.get(1)));
        adicionarModelo(new Modelo("C3", this.marcas.get(3)));
        
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
    
    public void adicionarMarca(Marca marca) {
    	this.marcas.add(marca);
    }
    
    public void adicionarModelo(Modelo modelo) {
    	this.modelos.add(modelo);
    }
    
    public Locacao alugarVeiculo(Veiculo veiculo, Cliente cliente) {
        Locacao locacao = new Locacao(cliente, veiculo);
        this.locacoes.add(locacao);
        return locacao;
    }
    
    public Locacao finalizarLocacao(Veiculo veiculo, int kmAtual) {
        for (Locacao locacao : locacoes) {
            if (locacao != null && locacao.getVeiculo().equals(veiculo) && locacao.estaAtiva()) {
                locacao.finalizar(kmAtual);
                return locacao;
            }
        }
        return null;
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
    
    public List<Locacao> getLocacoes() {
		return locacoes;
	}
    
    public List<Marca> getMarcas() {
		return marcas;
	}
}
