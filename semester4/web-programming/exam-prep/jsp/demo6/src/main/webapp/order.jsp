<%--
  Created by IntelliJ IDEA.
  User: cretuluca
  Date: 18.06.2025
  Time: 09:11
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>order</title>
</head>
<body>

<% if (request.getSession().getAttribute("username") != null) {
%>
    <form method="post" action="order">
        <p> product (name): <input type="text" name="name"> </p>
        <p> quantity: <input type="text" name="quantity"> </p>
        <button type="submit"> order </button>
    </form>
<%
    }
    else {
%>

    <p> you must <a href="login"> login </a> first </p>

<%
    }
%>

    <a href="${pageContext.request.contextPath}/home"> home </a>
</body>
</html>
