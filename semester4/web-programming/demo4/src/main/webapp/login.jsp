<%--
  Created by IntelliJ IDEA.
  User: cretuluca
  Date: 16.06.2025
  Time: 19:58
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>login</title>
</head>
<body>
    <a href="login"> login </a>
    <a href="add"> add </a>
    <a href="all"> all </a>
    <a href="most"> most </a>

    <form method="post" action="login">
        <p> username: <input type="text" name="username"> </p>
        <p> key: <input type="text" name="key"> </p>
        <button type="submit"> login </button>
    </form>

    <%= request.getSession().getAttribute("message") %>
</body>
</html>
