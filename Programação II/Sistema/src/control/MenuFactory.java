/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package control;

import javax.swing.JMenuBar;
import javax.swing.JPanel;

/**
 *
 * @author 5928036
 */
public interface MenuFactory {    
    public JMenuBar createMenuBar();
    public JPanel createSideMenu(Controlador controlador);
}
