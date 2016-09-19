package asteroids.core;


public class SpriteInfos {

    public int numeroDeQuadrosPorLinha;
    public int numeroDeQuadros;
    public double fps;
    public int larguraDosQuadros;
    public int alturaDosQuadros;
    
    private int numeroDeLinhas;
    private long tempoDeCadaQuadro; //em milisegundos

    public SpriteInfos(int larguraDoQuadro, int alturaDoQuadro) {
        this.fps = 15;
        this.numeroDeQuadros = 1;
        this.numeroDeQuadrosPorLinha = 1;
        this.numeroDeLinhas = 1;//numeroDeQuadrosPorLinha / numeroDeQuadros;
        this.tempoDeCadaQuadro = 0;//(long)(1000/fps);
        this.alturaDosQuadros = alturaDoQuadro;
        this.larguraDosQuadros = larguraDoQuadro;
        
    }

    public SpriteInfos(int larguraDosQuadros, int alturaDosQuadros, int numeroDeQuadrosPorLinha, int numeroDeQuadros, double fps) {
        this(larguraDosQuadros, alturaDosQuadros);
        this.numeroDeQuadrosPorLinha = numeroDeQuadrosPorLinha;
        this.numeroDeQuadros = numeroDeQuadros;
        this.fps = fps;
        this.numeroDeLinhas = numeroDeQuadrosPorLinha / numeroDeQuadros;
        this.tempoDeCadaQuadro = (long)(1000/fps);
    }

    public int getNumeroDeLinhas() {
        return numeroDeLinhas;
    }

    public long getTempoDeCadaQuadro() {
        return tempoDeCadaQuadro;
    }

    
    
}
