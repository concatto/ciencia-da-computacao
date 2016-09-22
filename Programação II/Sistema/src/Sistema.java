
import control.Controlador;
import java.awt.Color;
import java.awt.Dimension;
import javax.swing.UIDefaults;
import javax.swing.UIManager;
import javax.swing.plaf.nimbus.NimbusLookAndFeel;
import model.Loja;
import view.FormPrincipal;

public class Sistema {

    public static void main(String[] args) {
        instalaLookAndFeel();
        Loja loja = new Loja();
        FormPrincipal view = new FormPrincipal();
        Controlador controle = new Controlador(view, loja);
        view.setControlador(controle);
        controle.iniciarApp();

    }

    private static void instalaLookAndFeel() {
        try {
            UIManager.setLookAndFeel(new NimbusLookAndFeel());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
