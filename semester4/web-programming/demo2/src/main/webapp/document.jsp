<%--
  Created by IntelliJ IDEA.
  User: cretuluca
  Date: 14.06.2025
  Time: 18:56
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Add document</title>
</head>
<body>
    <form method="post" action="document?action=add">
        <p> Name: <input type="text" name="name"> </p>
        <p> Content: <input type="text" name="content"> </p>
        <p> AuthorId: <input type="text" name="authorId"> </p>

        <button type="submit"> Add </button>
    </form>
</body>
</html>
