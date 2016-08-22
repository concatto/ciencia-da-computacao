package persistencia;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import model.Bug;

public class GerenciadorDeDados {
    private Connection conn;
    
    public GerenciadorDeDados() {
        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://127.0.0.1/bug_tracker?user=root");
        } catch (SQLException ex) {
            Logger.getLogger(GerenciadorDeDados.class.getName()).log(Level.SEVERE, null, ex);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(GerenciadorDeDados.class.getName()).log(Level.SEVERE, null, ex);
        }
    }    
    
    public List<Bug> getBugs(String filtro) throws SQLException {
        List<Bug> bugs = new ArrayList<>();
        if (filtro == null) filtro = "";
        
        ResultSet rs = conn.createStatement().executeQuery("SELECT * FROM bugs" + filtro);
        while (rs.next()) {
            bugs.add(new Bug(rs.getInt(1), rs.getString(2), rs.getBoolean(3)));
        }
        
        return bugs;//retorna a lista de bugs
    }

    public void cadastraNovoBug(String titulo, String descricao) throws SQLException {
        PreparedStatement ps = conn.prepareStatement("INSERT INTO bugs (titulo, status, descricao) VALUES (?, 0, ?)");
        ps.setString(1, titulo);
        ps.setString(2, descricao);
        
        ps.execute();
    }

    public void alterarStatusDoBug(int idDoBug, boolean resolvido) throws SQLException {
        conn.createStatement().executeUpdate("UPDATE bugs SET status = " + (resolvido ? 1 : 0) + " WHERE id = " + idDoBug);
    }

    public List<Bug> getBugsResolvidos() throws SQLException {
        String filtro = " WHERE bugs.status=true";
        return getBugs(filtro);
    }

    public List<Bug> getBugsNaoResolvidos() throws SQLException {
        String filtro = " WHERE bugs.status=false";
        return getBugs(filtro);
    }

    /**
     * *
     * Este é um metodo de conveniência que apenas chama o método getBugs(String
     * filtro) sem passar nenhum filtro. Este método vai retornar todos os bugs
     * cadastrados.
     */
    public List<Bug> getBugs() throws SQLException {
        return getBugs(null);
    }

}
