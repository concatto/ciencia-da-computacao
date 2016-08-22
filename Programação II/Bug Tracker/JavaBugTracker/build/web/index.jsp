<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Java Bug tracker</title>

        <!-- Latest compiled and minified CSS -->
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css">

        <!-- Optional theme -->
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap-theme.min.css">

        <!-- Latest compiled and minified JavaScript -->
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js"></script>

        <style>
            h3{
                margin-top: 30px;
            }

            table{
                background-color: #fff;
            }
        </style>
    </head>
    <body >

        <div class="container">

            <!-- Main component for a primary marketing message or call to action -->
            <div class="jumbotron">

                <!-- Fixed navbar -->
                <nav class="navbar navbar-default navbar-fixed-top">
                    <div class="container">
                        <div class="navbar-header">
                            <a class="navbar-brand" href="#">Java Bug Tracker</a>
                        </div>
                    </div>
                </nav>


                <!-- lista todas os bugs cadastrados -->
                <h3>Bugs cadastrados 
                    <div class = "btn-group">
                        <a class="btn btn-xs btn-default" href="?acao=listar">Todos</a>
                        <a class="btn btn-xs btn-default" href="?acao=listarResolvidos">Resolvidos</a>
                        <a class="btn btn-xs btn-default" href="?acao=listarNaoResolvidos">Não resolvidos</a>
                    </div>
                </h3>

                <c:if test="${not empty bugs}">
                    <table class="table">
                        <tr> 
                            <th>ID</th>
                            <th>titulo</th> 
                            <th>Resolvido</th>
                            <th> </th> <!-- coluna dos botões de ação -->
                        </tr>
                        <c:forEach items="${bugs}" var="bug">
                            <tr 
                                <c:if test="${bug.resolvido}"> class="success" </c:if>
                                    >
                                    <td>${bug.id}</td>
                                <td>${bug.titulo}</td>
                                <td>${bug.resolvido}</td>
                                <td>
                                    <form action="?" method="post">
                                        <button type="submit" class="btn btn-primary">Mudar status ...</button>
                                        <input type="hidden" name="acao" value="mudarStatusDoBug"/>
                                        <input type="hidden" name="idDoBug" value="${bug.id}"/>
                                        <input type="hidden" name="status" value="${not bug.resolvido}"/>
                                    </form>

                                </td>
                            </tr>
                        </c:forEach> 
                    </table>
                </c:if>


                <!-- formulário de cadastro de bugs -->

                <form class="form-horizontal" action="?" method="post">
                    <h3>Cadastrar novo bug:</h3>
                    <div class="form-group">
                        <label class="control-label col-sm-2" for="titulo">Título:</label>
                        <div class="col-sm-10">
                            <input type="text" class="form-control" name="titulo" id="titulo" placeholder="Título do bug...">
                        </div>
                    </div>
                    <div class="form-group">
                        <label class="control-label col-sm-2" for="descricao">Descrição do bug:</label>
                        <div class="col-sm-10"> 
                            <textarea class="form-control" name="descricao" placeholder="Descrição do bug..."></textarea>
                        </div>
                    </div>
                    <div class="form-group"> 
                        <div class="col-sm-offset-2 col-sm-10">
                            <button type="submit" class="btn btn-default">Cadastrar</button>
                        </div>
                    </div>
                    <input type="hidden" name="acao" value="cadastrarBug">
                </form>

            </div>
        </div>
    </body>
</html>
