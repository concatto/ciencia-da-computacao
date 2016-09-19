package asteroids;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import javax.swing.JFrame;

import asteroids.core.AcumuladorDeTempo;
import asteroids.core.GameObject;
import asteroids.core.HUD;
import asteroids.objects.Asteroid;
import asteroids.objects.GameObjectFactory;
import asteroids.objects.GameObjectType;
import asteroids.objects.Explosao;
import asteroids.objects.Nave;
import asteroids.objects.TiroDaNave;
import asteroids.objects.UFO;

@SuppressWarnings("serial")
public class Asteroids extends JFrame {

    public static final int LARGURA_DA_TELA = 800;
    public static final int ALTURA_DA_TELA = 600;
    //+++++++++++++++++++++++++++++++++
    //controles do teclado e gameOver
    private boolean leftPressed = false;
    private boolean rightPressed = false;
    private boolean acelerando = false;
    private boolean shotPressed = false;
    private boolean gameOver = false;
    //+++++++++++++++++++++++++++++++++
    //objetos
    private Nave nave = new Nave();
    private HUD hud = new HUD();
    //+++++++++++++++
    //listas de objetos
    private static final int VELOCIDADE_DOS_TIROS = 400;
    private List<GameObject> tirosDaNave = new ArrayList<>();
    private List<GameObject> inimigos = new ArrayList<>();
    private List<GameObject> explosoes = new ArrayList<>();
    private AcumuladorDeTempo temporizadorDosTiros = new AcumuladorDeTempo(200);//utilizado para controlar o tempo entre tiros consecutivos
    //+++++++++++++++
    private BufferedImage buffer;//back buffer, usado para evitar flickering
    private BufferedImage background;//imagem de background

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    private void inicializaObjetos() {
        nave.setLocalizacao(LARGURA_DA_TELA / 2, ALTURA_DA_TELA / 2);
        nave.setVelocidade(50);

        //cria background (fundo preto e estrelas (pixels brancos) espalhadas aleatoriamente)
        background = new BufferedImage(rootPane.getWidth(), rootPane.getHeight(), BufferedImage.TYPE_INT_RGB);
        Graphics g = background.getGraphics();
        for (int i = 0; i < 100; i++) {
            int x = (int) (Math.random() * getWidth());
            int y = (int) (Math.random() * getHeight());
            Color cor = new Color(255, 255, 255, (int) (Math.random() * 100));//sorteia a transparência de cada estrela
            g.setColor(cor);
            g.drawOval(x - 1, y - 1, 2, 2);//desenha estrela
        }
    }
    //+++++++++++++++++++++++++++

    public void iniciaJogo() {
        inicializaObjetos();
        long frameTime = 0;
        long tempoInicial;
        while (!gameOver) {
            try {
                tempoInicial = System.currentTimeMillis();
                processaEntrada();
                processaLogica((int) frameTime);
                Thread.sleep(10);
                frameTime = System.currentTimeMillis() - tempoInicial;
            } catch (Exception e) {
                e.printStackTrace();
            }
            repaint();
        }
        System.exit(0);
    }
    //+++++++++++++++++++++++++++++++

    private void processaEntrada() {
        if (leftPressed) {
            nave.viraPraEsquerda();
        } else if (rightPressed) {
            nave.viraPraDireita();
        }

        if (shotPressed) {
            disparaTiro();
        }

        nave.setAcelerando(acelerando);
    }
    //+++++++++++++++++++++++++++++++

    private void disparaTiro() {
        if (temporizadorDosTiros.expirou()) {//se já pode dar um novo tiro
            GameObject novoTiro = GameObjectFactory.createObject(GameObjectType.PROJECTILE);
            novoTiro.setAtivado(true);
            novoTiro.setVelocidade(VELOCIDADE_DOS_TIROS);
            novoTiro.setLocalizacao(nave.getBounds().getCenterX(), nave.getBounds().getCenterY());
            novoTiro.setAnguloDoMovimento(nave.getAnguloDaFace() - 90);
            tirosDaNave.add(novoTiro);
            temporizadorDosTiros.reseta();
        }
    }
    //+++++++++++++++++++++++++++++++
    //método de pintura do JFrame

    @Override
    public void paint(Graphics gr) {
        if (buffer != null) {
            Graphics2D g = (Graphics2D) buffer.getGraphics();

            g.setTransform(new AffineTransform());//reseta as rotações e translações

            g.drawImage(background, 0, 0, null);//desenha background

            //desenha tiros, explosões e inimigos
            desenhaObjetos(g, tirosDaNave);
            desenhaObjetos(g, inimigos);
            desenhaObjetos(g, explosoes);

            nave.draw(g);
            hud.draw(g);

            gr.drawImage(buffer, 0, 0, this);//desenha todo o frame na tela do jogo
        }
    }
    //+++++++++++++++++++++++++++++++

    private void desenhaObjetos(Graphics2D g, List<GameObject> listaDeObjetos) {
        for (GameObject gameObject : listaDeObjetos) {
            if (gameObject != null && gameObject.estaAtivado()) {
                gameObject.draw(g);
            }
        }
    }
    
    //+++++++++++++++++++++++++++++++
    //o tempo entre o quadro atual e o quadro anterior (frameTime) é utilizado
    //para calcular o quanto cada objeto deve se movimentar com base no
    //tempo decorrido desde o último quadro do jogo que foi processado.

    private void processaLogica(int frameTime) {
        nave.update(frameTime);

        temporizadorDosTiros.atualiza(frameTime);

        hud.update(frameTime);

        if (Math.random() <= 0.02) {//probabilidade de um inimigo ser criado em cada quadro
            inimigos.add(criaNovoInimigo());
        }

        //verifica se os tiros da nave atingiram algum inimigo
        Iterator<GameObject> i = tirosDaNave.iterator();
        while (i.hasNext()) {
            GameObject tiro = i.next();
            GameObject inimigoAtingido = getInimigoAtingido(tiro);
            if (inimigoAtingido != null) {
                inimigoAtingido.setAtivado(false);
                tiro.setAtivado(false);
                Explosao explosao = Explosao.criaExplosao();
                explosoes.add(explosao);
                explosao.setLocalizacao(inimigoAtingido.getX(), inimigoAtingido.getY());
                explosao.setVelocidade(inimigoAtingido.getVelocidade() / 3);
                explosao.setAnguloDoMovimento(inimigoAtingido.getAnguloDoMovimento());
                break;
            }
        }

        atualizaObjetos(frameTime);
    }
    //+++++++++++++++++++++++++++++++

    private GameObject criaNovoInimigo() {
    	//50% de chande de criar um UFO
    	GameObjectType tipo = Math.random() <= 0.5 ? GameObjectType.UFO : GameObjectType.ASTEROID;
        GameObject novoInimigo = GameObjectFactory.createObject(tipo);

        //os inimigos surgem das bordas da tela e se movimentam em direção à nave do jogador
        double anguloDaPosicaoInicialDoInimigo = Math.toRadians((Math.random() * 360));
        double xDoInimigo = getWidth() / 2 + Math.cos(anguloDaPosicaoInicialDoInimigo) * getWidth() / 2;
        double yDoInimigo = getHeight() / 2 + Math.sin(anguloDaPosicaoInicialDoInimigo) * getWidth() / 2;
        novoInimigo.setLocalizacao(xDoInimigo, yDoInimigo);

        double anguloDeMovimentacaoDoInimigo = Math.toDegrees(Math.atan2(nave.getY() - yDoInimigo, nave.getX() - xDoInimigo));
        novoInimigo.setAnguloDoMovimento(anguloDeMovimentacaoDoInimigo);
        novoInimigo.setVelocidade(10 + Math.random() * 100);
        return novoInimigo;
    }
    //+++++++++++++++++++++++++++++++

    private void atualizaObjetos(int frameTime) {
        atualizaObjetos(tirosDaNave, frameTime);
        atualizaObjetos(inimigos, frameTime);
        atualizaObjetos(explosoes, frameTime);

        //remove objetos desativados
        removeObjetosDesativados(inimigos);
        removeObjetosDesativados(explosoes);
        removeObjetosDesativados(tirosDaNave);

        hud.setInimigosAtivos(inimigos.size());
    }
    //+++++++++++++++++++++++++++++++

    private void removeObjetosDesativados(List<GameObject> listaDeObjetos) {
        Iterator<GameObject> it = listaDeObjetos.iterator();
        while (it.hasNext()) {
            GameObject gameObject = it.next();
            if (!gameObject.estaAtivado()) {
                it.remove();
            }
        }
    }
    //+++++++++++++++++++++++++++++++

    private void atualizaObjetos(List<GameObject> listaDeObjetos, int frameTime) {
        Iterator<GameObject> it = listaDeObjetos.iterator();
        Rectangle limitesDaTela = new Rectangle(-200, -200, getWidth() + 200, getHeight() + 200);
        while (it.hasNext()) {
            GameObject gameObject = it.next();
            if (gameObject.estaAtivado()) {
                gameObject.update(frameTime);
                boolean objetoEstaNaTela = gameObject.getBounds().intersects(limitesDaTela);
                gameObject.setAtivado(objetoEstaNaTela && gameObject.estaAtivado());//quando o objeto sai da tela ele é desativado
            } else {
                it.remove();
            }
        }
    }

    //+++++++++++++++++++++++++++++++
    private GameObject getInimigoAtingido(GameObject tiro) {
        for (GameObject inimigo : inimigos) {
            if (houveColisao(inimigo, tiro)) {
                return inimigo;
            }
        }
        return null;
    }
    //+++++++++++++++++++++++++++++++

    private boolean houveColisao(GameObject a, GameObject b) {
        if (a.estaAtivado() && b.estaAtivado()) {
            return a.getBounds().intersects(b.getBounds());
        }
        return false;
    }
    //+++++++++++++++++++++++++++++++
    //construtor

    public Asteroids() {
        super("Asteroids");
        configuraJanela();
    }

    private void configuraJanela() {
        setSize(LARGURA_DA_TELA, ALTURA_DA_TELA);
        setResizable(false);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        addKeyListener(new InputHandler());
        addWindowListener(new WindowHandler());
    }

    //método principal
    public static void main(String[] args) {
        Asteroids asteroids = new Asteroids();
        asteroids.setVisible(true);
        asteroids.iniciaJogo();
    }

    //+++++++++++++++++++++++++++++++++++++++++++++
    private class WindowHandler extends WindowAdapter {

        @Override
        public void windowActivated(WindowEvent e) {
            //cria uma imagem do tamanho da tela onde o jogo será desenhado
            buffer = new BufferedImage(rootPane.getWidth(), rootPane.getHeight(), BufferedImage.TYPE_INT_ARGB);
        }
    }
    //+++++++++++++++++++++++++++++++++++++++++++++

    private class InputHandler extends KeyAdapter {

        @Override
        public void keyPressed(KeyEvent e) {
            switch (e.getKeyCode()) {
                case KeyEvent.VK_LEFT:
                case KeyEvent.VK_A:
                    leftPressed = true;
                    break;
                case KeyEvent.VK_RIGHT:
                case KeyEvent.VK_D:
                    rightPressed = true;
                    break;
                case KeyEvent.VK_UP:
                case KeyEvent.VK_W:
                    acelerando = true;
                    break;
                case KeyEvent.VK_SPACE:
                case KeyEvent.VK_ENTER:
                    shotPressed = true;
                    break;
                case KeyEvent.VK_ESCAPE:
                    gameOver = true;
                    break;
            }
        }

        @Override
        public void keyReleased(KeyEvent e) {
            switch (e.getKeyCode()) {
                case KeyEvent.VK_LEFT:
                case KeyEvent.VK_A:
                    leftPressed = false;
                    break;
                case KeyEvent.VK_RIGHT:
                case KeyEvent.VK_D:
                    rightPressed = false;
                    break;
                case KeyEvent.VK_SPACE:
                case KeyEvent.VK_ENTER:
                    shotPressed = false;
                    break;
                case KeyEvent.VK_UP:
                case KeyEvent.VK_W:
                    acelerando = false;
                    break;
            }
        }
    }
}
