<%--
  Created by IntelliJ IDEA.
  User: cretuluca
  Date: 16.06.2025
  Time: 20:54
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>add</title>
</head>
<body>
    <a href="login"> login </a>
    <a href="add"> add </a>
    <a href="all"> all </a>
    <a href="most"> most </a>

    <form method="post" action="add">
        <p> name: <input type="text" name="name"/> </p>
        <p> contents: <input type="text" name="contents"/> </p>
        <button type="submit"> add </button>
    </form>
</body>
</html>
