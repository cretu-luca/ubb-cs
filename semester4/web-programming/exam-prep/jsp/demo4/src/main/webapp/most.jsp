<%@ page import="com.example.demo4.Model.Document" %><%--
  Created by IntelliJ IDEA.
  User: cretuluca
  Date: 16.06.2025
  Time: 22:36
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>most authors</title>
</head>
<body>
    <a href="login"> login </a>
    <a href="add"> add </a>
    <a href="all"> all </a>
    <a href="most"> most </a>
    <p> <%= ((Document) request.getAttribute("mostAuthorsDocument")).Name %> </p>
</body>
</html>
