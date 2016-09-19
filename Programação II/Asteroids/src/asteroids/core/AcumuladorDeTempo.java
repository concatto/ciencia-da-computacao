package asteroids.core;

public class AcumuladorDeTempo {

    private long tempoAcumulado;
    private long tempoLimite;

    public AcumuladorDeTempo(long tempoLimite) {
        this.tempoAcumulado = 0;
        this.tempoLimite = tempoLimite;
    }

    public void atualiza(long tempoDoQuadro){
        tempoAcumulado += tempoDoQuadro;
    }
    
    public boolean expirou(){
        return tempoAcumulado >= tempoLimite;
    }
    
    public void reseta(){
        tempoAcumulado = tempoAcumulado % tempoLimite;
    }
    
}
