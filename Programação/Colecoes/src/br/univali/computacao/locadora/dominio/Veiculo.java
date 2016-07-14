/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package br.univali.computacao.locadora.dominio;

import br.univali.computacao.locadora.excecoes.QuilometragemIncorretaException;

/**
 *
 * @author 1978233
 */
public class Veiculo {
    private Modelo modelo;
    private int km;
    private int ano;
    private String placa;
    private double valorKm;

    public Veiculo() {
    }

    public Veiculo(Modelo modelo, int km, int ano, String placa, double valorKm) throws QuilometragemIncorretaException {
    	if (km <= 0) {
    		throw new QuilometragemIncorretaException("A quilometragem não pode ser menor ou igual a 0");
    	}
    	
        this.modelo = modelo;
        this.km = km;
        this.ano = ano;
        this.placa = placa;
        this.valorKm = valorKm;
    }
    
    

    /**
     * @return the modelo
     */
    public Modelo getModelo() {
        return modelo;
    }

    /**
     * @param modelo the modelo to set
     */
    public void setModelo(Modelo modelo) {
        this.modelo = modelo;
    }

    /**
     * @return the km
     */
    public int getKm() {
        return km;
    }

    /**
     * @param km the km to set
     */
    public void setKm(int km) {
        this.km = km;
    }

    /**
     * @return the ano
     */
    public int getAno() {
        return ano;
    }

    /**
     * @param ano the ano to set
     */
    public void setAno(int ano) {
        this.ano = ano;
    }

    /**
     * @return the placa
     */
    public String getPlaca() {
        return placa;
    }

    /**
     * @param placa the placa to set
     */
    public void setPlaca(String placa) {
        this.placa = placa;
    }

    /**
     * @return the valorKm
     */
    public double getValorKm() {
        return valorKm;
    }

    /**
     * @param valorKm the valorKm to set
     */
    public void setValorKm(double valorKm) {
        this.valorKm = valorKm;
    }
    
    @Override
    public String toString() {
    	return placa + ": " + modelo + " ano " + ano;
    }
}
