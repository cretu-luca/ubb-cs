<%@ page import="java.util.List" %>
<%@ page import="com.example.demo3.Models.Article" %><%--
  Created by IntelliJ IDEA.
  User: cretuluca
  Date: 15.06.2025
  Time: 11:19
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>my articles</title>
</head>
<body>
    <h2>Search Articles</h2>
    <p>Current user: <%= session.getAttribute("username") %></p>
    
    <form method="get" action="articles">
        <p>Journal: <input type="text" name="journalName"> </p>
        <p><input type="submit" value="Search"></p>
    </form>

    <%
        List<Article> articles = (List<Article>) request.getAttribute("articles");

        if (articles != null && !articles.isEmpty()) {
    %>
        <h3>Articles found:</h3>
    <%
            for (Article article: articles) {
    %>
            <div>
                <p> User: <%= article.User %> </p>
                <p> JournalId: <%= article.JournalId %> </p>
                <p> Summary: <%= article.Summary %> </p>
                <p> Date: <%= article.Date %> </p>
            </div>
    <%
            }
        } else if (request.getParameter("journalName") != null && !request.getParameter("journalName").isEmpty()) {
    %>
        <p>No articles found for the specified journal.</p>
    <%
        }
    %>
</body>
</html>
