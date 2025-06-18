<%--
  Created by IntelliJ IDEA.
  User: cretuluca
  Date: 18.06.2025
  Time: 16:46
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
<% if (request.getSession().getAttribute("username") != null) {
%>
<p> hei, <%= request.getSession().getAttribute("username") %> </p>
<%
  }
%>

<a href="${pageContext.request.contextPath}/all"> products </a>

</body>
</html>
