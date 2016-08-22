package model;

public class Bug {
 
    private final int id;
    private final String titulo;
    private boolean status;//bug já foi resolvido ou não?

    public Bug(int id, String titulo, boolean status) {
        this.id = id;
        this.titulo = titulo;
        this.status = status;
    }

    public int getId() {
        return id;
    }

    public String getTitulo() {
        return titulo;
    }

    public boolean isResolvido() {
        return status;
    }

    public void setStatus(boolean resolvido) {
        this.status = resolvido;
    }
}
