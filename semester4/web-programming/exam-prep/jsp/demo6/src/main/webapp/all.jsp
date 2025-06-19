<%@ page import="com.example.demo6.Model.Products" %>
<%@ page import="java.util.List" %>
<%@ page import="com.example.demo6.Model.Products" %><%--
  Created by IntelliJ IDEA.
  User: cretuluca
  Date: 18.06.2025
  Time: 08:53
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>all</title>
</head>
<body>
    <form method="post" action="all">
        <p> query: <input type="text" name="query" /> </p>
        <button type="submit"> search </button>
    </form>

  <%
    List<Products> products = (List<Products>) request.getAttribute("products");
  %>
    <table>
        <tr> <th> name </th> <th> description </th> </tr>
  <%
      if (products != null) {
        for (Products product: products) {
  %>
        <tr>
            <td> <%= product.Name %> </td>
            <td> <%= product.Description %> </td>
        </tr>
  <%
        }
      }
  %>
    </table>

    <a href="${pageContext.request.contextPath}/home"> home </a>
</body>
</html>
