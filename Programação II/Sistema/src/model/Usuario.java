package model;


public class Usuario {
    
    private String nomeDeUsuario;
    private String senha;
    private boolean admin;

    public Usuario(String nomeDeUsuario, String senha, boolean isAdmin) {
        this.nomeDeUsuario = nomeDeUsuario;
        this.senha = senha;
        admin = isAdmin;
    }

    public String getNomeDeUsuario() {
        return nomeDeUsuario;
    }

    public void setNomeDeUsuario(String nomeDeUsuario) {
        this.nomeDeUsuario = nomeDeUsuario;
    }

    public String getSenha() {
        return senha;
    }

    public void setSenha(String senha) {
        this.senha = senha;
    }

    public boolean isAdmin() {
        return admin;
    }
}
