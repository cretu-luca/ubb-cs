<%--
  Created by IntelliJ IDEA.
  User: cretuluca
  Date: 17.06.2025
  Time: 19:20
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>home</title>
</head>
<body>
    <% if (request.getSession().getAttribute("username") != null) {
    %>
        <p> hei, <%= request.getSession().getAttribute("username") %> </p>
    <%
    }
    %>

<a href="${pageContext.request.contextPath}/articles"> articles </a>
<a href="${pageContext.request.contextPath}/add"> add </a>

</body>
</html>
