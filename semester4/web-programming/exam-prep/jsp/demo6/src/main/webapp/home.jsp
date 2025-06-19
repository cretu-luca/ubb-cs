<%@ page import="com.sun.net.httpserver.HttpContext" %><%--
  Created by IntelliJ IDEA.
  User: cretuluca
  Date: 18.06.2025
  Time: 08:42
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>home</title>
</head>
<body>
  <% if (request.getSession().getAttribute("username") != "") {
  %>
    <p> hei, <%= request.getSession().getAttribute("username") %> </p>
  <%
  }
    else
  {
  %>
    <p> not logged in.</p>
<%
  }
%>

<a href="add"> add </a>
<a href="all"> all </a>
<a href="order"> order </a>
<a href="finalize"> orders </a>

</body>
</html>
