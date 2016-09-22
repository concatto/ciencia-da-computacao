
package view.menus.atendente;

import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;


public class BarraDeMenuAtendente extends JMenuBar{

    public static final String BUSCAR_PRODUTOS = "Buscar produtos";
    public static final String LISTAR_PRODUTOS = "Listar todos os produtos cadastrados";
    
    
    public BarraDeMenuAtendente() {
        super();
        criaItensDoMenu();
    }

    
    
    protected void criaItensDoMenu() {
        JMenu menu = new JMenu("Menu Atendente");
        menu.add(new JMenuItem(BUSCAR_PRODUTOS));
        menu.add(new JMenuItem(LISTAR_PRODUTOS));
        add(menu);
    }
    
}
