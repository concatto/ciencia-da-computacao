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

import br.univali.computacao.locadora.excecoes.ItemInexistenteException;
import br.univali.computacao.locadora.excecoes.ItemJaExisteException;
import br.univali.computacao.locadora.excecoes.QuilometragemIncorretaException;
import br.univali.computacao.locadora.excecoes.VeiculoAlugadoException;

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
        
        try {
	        adicionarModelo(new Modelo("Aircross", this.marcas.get(3)));
	        adicionarModelo(new Modelo("C4 Grand Picasso", this.marcas.get(3)));
	        adicionarModelo(new Modelo("147", this.marcas.get(0)));
	        adicionarModelo(new Modelo("Fusca", this.marcas.get(1)));
	        adicionarModelo(new Modelo("Uno", this.marcas.get(0)));
	        adicionarModelo(new Modelo("M3", this.marcas.get(2)));
	        adicionarModelo(new Modelo("X2", this.marcas.get(2)));
	        adicionarModelo(new Modelo("Brasília", this.marcas.get(1)));
	        adicionarModelo(new Modelo("C3", this.marcas.get(3)));
        } catch (ItemInexistenteException ex) {
        	//Ambiente controlado
        }
        
        this.veiculos = new TreeMap<>();
        this.clientes = new HashMap<>();
        this.locacoes = new ArrayList<>();
    }
    
    public void adicionarCliente(Cliente cliente) throws ItemJaExisteException {
    	if (clientes.containsKey(cliente.getCpf())) {
    		throw new ItemJaExisteException("Já existe um cliente com este CPF.");
    	}
    	
        this.clientes.put(cliente.getCpf(), cliente);
    }

    public void adicionarVeiculo(Veiculo veiculo) throws ItemJaExisteException {
    	if (veiculos.containsKey(veiculo.getPlaca())) {
    		throw new ItemJaExisteException("Já existe um veículo com esta placa.");
    	}
    	
        this.veiculos.put(veiculo.getPlaca(), veiculo);
    }
    
    public void adicionarMarca(Marca marca) {
    	this.marcas.add(marca);
    }
    
    public void adicionarModelo(Modelo modelo) {
    	this.modelos.add(modelo);
    }
    
    public Locacao alugarVeiculo(Veiculo veiculo, Cliente cliente) throws ItemInexistenteException, VeiculoAlugadoException {
    	for (Locacao l : locacoes) {
    		if (l.estaAtiva() && l.getVeiculo().getPlaca().equals(veiculo.getPlaca())) {
    			throw new VeiculoAlugadoException("O veículo já está alugado.");
    		}
    	}
        Locacao locacao = new Locacao(cliente, veiculo);
        this.locacoes.add(locacao);
        return locacao;
    }
    
    public Locacao finalizarLocacao(Veiculo veiculo, int kmAtual) throws ItemInexistenteException, QuilometragemIncorretaException {
    	if (!veiculos.containsKey(veiculo.getPlaca())) {
    		throw new ItemInexistenteException("O veículo não existe.");
    	}
    	
        for (Locacao locacao : locacoes) {
            if (locacao != null && locacao.getVeiculo().getPlaca().equals(veiculo.getPlaca()) && locacao.estaAtiva()) {
                locacao.finalizar(kmAtual);
                return locacao;
            }
        }
        
        throw new ItemInexistenteException("O veículo não está alugado.");
    }
    
    public Locacao finalizarLocacao(String placa, int kmAtual) throws ItemInexistenteException, QuilometragemIncorretaException {
    	return finalizarLocacao(buscarVeiculo(placa), kmAtual);
    }

    public List<Modelo> getModelos() {
		return modelos;
	}
    
    public SortedMap<String, Veiculo> getVeiculos() {
		return veiculos;
	}
     
    public Cliente buscarCliente(String cpf) throws ItemInexistenteException {
    	Cliente c = clientes.get(cpf);
    	if (c == null) throw new ItemInexistenteException("O cliente não existe.");
    	
		return c;
    }
    
    public Veiculo buscarVeiculo(String placa) throws ItemInexistenteException {
    	Veiculo v = veiculos.get(placa);
    	if (v == null) throw new ItemInexistenteException("O veículo não existe.");
    	
    	return v;
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

	public Modelo getModelo(int modelo) throws ItemInexistenteException {
		if (modelo < 0 || modelo > modelos.size()) throw new ItemInexistenteException("O modelo não existe");
		return modelos.get(modelo);
	}
	
	public Marca getMarca(int marca) throws ItemInexistenteException {
		if (marca < 0 || marca > marcas.size()) throw new ItemInexistenteException("A marca não existe.");
		return marcas.get(marca);
	}
}
