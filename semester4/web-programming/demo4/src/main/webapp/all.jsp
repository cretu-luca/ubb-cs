<%@ page import="com.example.demo4.Model.Movie" %>
<%@ page import="java.util.List" %>
<%@ page import="com.example.demo4.Model.Document" %><%--
  Created by IntelliJ IDEA.
  User: cretuluca
  Date: 16.06.2025
  Time: 21:41
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>all</title>
</head>
<body>
    <a href="login"> login </a>
    <a href="add"> add </a>
    <a href="all"> all </a>
    <a href="most"> most </a>

  <%
      List<Movie> movies = (List<Movie>) request.getSession().getAttribute("movies");
      List<Document> documents = (List<Document>) request.getSession().getAttribute("documents");

      int moviesIndex = 0, documentsIndex = 0;
      while (moviesIndex < movies.size() || documentsIndex < documents.size()) {
          if (moviesIndex < movies.size()) {
  %>
        <form method="post" action="all?action=movie">
            <input type="hidden" name="id" value=<%= movies.get(moviesIndex).Id %>>
            <p> title: <%= movies.get(moviesIndex).Title %> </p>
            <p> duration: <%= movies.get(moviesIndex).Duration %> </p>
            <button type="submit"> delete </button>
        </form>
  <%
          moviesIndex++;
       }

          if (documentsIndex < documents.size()) {
  %>
          <form method="post" action="all?action=document">
              <input type="hidden" name="id" value=<%= documents.get(documentsIndex).Id %>>
              <p> name: <%= documents.get(documentsIndex).Name %> </p>
              <p> contents: <%= documents.get(documentsIndex).Contents %> </p>
              <button type="submit"> delete </button>
          </form>
  <%
          documentsIndex++;
       }
      }
  %>
</body>
</html>
