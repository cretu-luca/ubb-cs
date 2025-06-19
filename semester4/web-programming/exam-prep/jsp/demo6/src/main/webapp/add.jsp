<%--
  Created by IntelliJ IDEA.
  User: cretuluca
  Date: 18.06.2025
  Time: 08:46
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>add</title>
</head>
<body>
    <form method="post" action="add">
        <p> name: <input type="text" name="name"/> </p>
        <p> description: <input type="text" name="description"/> </p>
        <button type="submit"> add </button>
    </form>

    <a href="${pageContext.request.contextPath}/home"> home </a>
</body>
</html>
