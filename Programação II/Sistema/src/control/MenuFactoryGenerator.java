/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package control;

import model.Usuario;

/**
 *
 * @author 5928036
 */
public class MenuFactoryGenerator {
    public static MenuFactory createMenuFactory(Usuario user) {
        return user.isAdmin() ? new AdminMenuFactory() : new WorkerMenuFactory();
    }
}
