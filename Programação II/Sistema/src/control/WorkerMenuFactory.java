/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package control;

import javax.swing.JMenuBar;
import javax.swing.JPanel;
import view.menus.atendente.BarraDeMenuAtendente;
import view.menus.atendente.PanelMenuAtendente;

/**
 *
 * @author 5928036
 */
public class WorkerMenuFactory implements MenuFactory {
    @Override
    public JMenuBar createMenuBar() {
        return new BarraDeMenuAtendente();
    }

    @Override
    public JPanel createSideMenu(Controlador controlador) {
        return new PanelMenuAtendente(controlador);
    }
    
}
