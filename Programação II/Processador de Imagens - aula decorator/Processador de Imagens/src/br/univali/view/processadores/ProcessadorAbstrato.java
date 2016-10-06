/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package br.univali.view.processadores;

/**
 *
 * @author 5928036
 */
public abstract class ProcessadorAbstrato implements Processador {
    protected Processador p;
    
    public ProcessadorAbstrato(Processador p) {
        this.p = p;
    }
}
