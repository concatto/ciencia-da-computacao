package view.menus.admin;

import javax.swing.JMenu;
import javax.swing.JMenuItem;
import view.menus.atendente.BarraDeMenuAtendente;



public class BarraDeMenuAdmin extends BarraDeMenuAtendente{

    public BarraDeMenuAdmin() {
        super();
        //criaItensDoMenu();
    }

    @Override
    protected void criaItensDoMenu() {
        
        JMenu menu = new JMenu("Admin Menu");
        menu.add( new JMenuItem("logoff"));
        menu.add( new JMenuItem("Cadastrar produto"));
        menu.add( new JMenuItem("Cadastrar atendente"));
        add(menu);
        
        super.criaItensDoMenu();//cria o menu de atendente
    }
    
}
