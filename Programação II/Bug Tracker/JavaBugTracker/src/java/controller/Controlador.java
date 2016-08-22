package controller;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import persistencia.GerenciadorDeDados;

public class Controlador extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        try {
            String acao = "listar";//por padrão sempre lista os bugs cadastrados
            if (request.getParameter("acao") != null) {
                acao = request.getParameter("acao");
            }

            GerenciadorDeDados gerenciadorDeDados = new GerenciadorDeDados();
            switch (acao) {
                case "listar":
                    request.setAttribute("bugs", gerenciadorDeDados.getBugs());
                    break;
                case "listarResolvidos":
                    request.setAttribute("bugs", gerenciadorDeDados.getBugsResolvidos());
                    break;
                case "listarNaoResolvidos":
                    request.setAttribute("bugs", gerenciadorDeDados.getBugsNaoResolvidos());
                    break;
            }
            request.getRequestDispatcher("index.jsp").forward(request, response);
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        try {
            GerenciadorDeDados gerenciadorDeDados = new GerenciadorDeDados();
            String acao = request.getParameter("acao");
            switch (acao) {
                case "cadastrarBug":
                    String titulo = request.getParameter("titulo");
                    String descricao = request.getParameter("descricao");
                    gerenciadorDeDados.cadastraNovoBug(titulo, descricao);
                    request.setAttribute("bugs", gerenciadorDeDados.getBugs());//lista todos os bugs depois de cadastrar
                    break;
                case "mudarStatusDoBug":
                    int idDoBug = Integer.parseInt(request.getParameter("idDoBug"));
                    boolean novoStatus = Boolean.parseBoolean(request.getParameter("status"));
                    gerenciadorDeDados.alterarStatusDoBug(idDoBug, novoStatus);
                    request.setAttribute("bugs", gerenciadorDeDados.getBugs());//lista todos os bugs depois de mudar o status
                    break;
            }
            request.getRequestDispatcher("index.jsp").forward(request, response);
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }
}
