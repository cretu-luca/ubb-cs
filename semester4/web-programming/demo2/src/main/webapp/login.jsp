<%--
  Created by IntelliJ IDEA.
  User: cretuluca
  Date: 14.06.2025
  Time: 18:02
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>login</title>
</head>
<body>
<h2>Login Page</h2>

<% if (request.getAttribute("error") != null) { %>
<p class="error"><%= request.getAttribute("error") %></p>
<% } %>

<form method="post" action="login">
    <p>
        <button type="submit">Login</button>
    </p>

    <p> Username: <input type="text" name="username"> </p>
    <p> Authored: <input type="text" name="authored"> </p>
</form>

<p><a href="<%=request.getContextPath()%>/">← Back to Home</a></p>
</body>
</html>
