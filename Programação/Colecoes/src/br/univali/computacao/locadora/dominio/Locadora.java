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

import br.univali.computacao.excecoes.ClienteInexistenteException;
import br.univali.computacao.excecoes.ClienteJaExisteException;
import br.univali.computacao.excecoes.LocacaoInexistenteException;
import br.univali.computacao.excecoes.MarcaInexistenteException;
import br.univali.computacao.excecoes.ModeloInexistenteException;
import br.univali.computacao.excecoes.VeiculoInexistenteException;
import br.univali.computacao.excecoes.VeiculoJaExisteException;

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
        } catch (MarcaInexistenteException ex) {
        	//Ambiente controlado!
        }
        
        this.veiculos = new TreeMap<>();
        this.clientes = new HashMap<>();
        this.locacoes = new ArrayList<>();
    }
    
    public void adicionarCliente(Cliente cliente) throws ClienteJaExisteException {
    	if (clientes.containsKey(cliente.getCpf())) {
    		throw new ClienteJaExisteException();
    	}
    	
        this.clientes.put(cliente.getCpf(), cliente);
    }

    public void adicionarVeiculo(Veiculo veiculo) throws VeiculoJaExisteException {
    	if (veiculos.containsKey(veiculo.getPlaca())) {
    		throw new VeiculoJaExisteException();
    	}
    	
        this.veiculos.put(veiculo.getPlaca(), veiculo);
    }
    
    public void adicionarMarca(Marca marca) {
    	this.marcas.add(marca);
    }
    
    public void adicionarModelo(Modelo modelo) {
    	this.modelos.add(modelo);
    }
    
    public Locacao alugarVeiculo(Veiculo veiculo, Cliente cliente) throws VeiculoInexistenteException, ClienteInexistenteException {    	
        Locacao locacao = new Locacao(cliente, veiculo);
        this.locacoes.add(locacao);
        return locacao;
    }
    
    public Locacao finalizarLocacao(Veiculo veiculo, int kmAtual) throws LocacaoInexistenteException {
        for (Locacao locacao : locacoes) {
            if (locacao != null && locacao.getVeiculo().equals(veiculo) && locacao.estaAtiva()) {
                locacao.finalizar(kmAtual);
                return locacao;
            }
        }
        
        throw new LocacaoInexistenteException();
    }
    
    public Locacao finalizarLocacao(String placa, int kmAtual) throws LocacaoInexistenteException, VeiculoInexistenteException {
    	return finalizarLocacao(buscarVeiculo(placa), kmAtual);
    }

    public List<Modelo> getModelos() {
		return modelos;
	}
    
    public SortedMap<String, Veiculo> getVeiculos() {
		return veiculos;
	}
     
    public Cliente buscarCliente(String cpf) throws ClienteInexistenteException {
    	Cliente c = clientes.get(cpf);
    	if (c == null) throw new ClienteInexistenteException();
    	
		return c;
    }
    
    public Veiculo buscarVeiculo(String placa) throws VeiculoInexistenteException {
    	Veiculo v = veiculos.get(placa);
    	if (v == null) throw new VeiculoInexistenteException();
    	
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

	public Modelo getModelo(int modelo) throws ModeloInexistenteException {
		if (modelo < 0 || modelo > modelos.size()) throw new ModeloInexistenteException();
		return modelos.get(modelo);
	}
	
	public Marca getMarca(int marca) throws MarcaInexistenteException {
		if (marca < 0 || marca > marcas.size()) throw new MarcaInexistenteException();
		return marcas.get(marca);
	}
}
