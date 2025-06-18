<%@ page import="com.example.demo6.Model.Products" %>
<%@ page import="java.util.List" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="com.example.demo6.Model.ProductsOrders" %><%--
  Created by IntelliJ IDEA.
  User: cretuluca
  Date: 18.06.2025
  Time: 09:29
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>your orders</title>
</head>
<body>
    <%
        ArrayList<ProductsOrders> orders = (ArrayList<ProductsOrders>) request.getSession().getAttribute("sessionOrders");
    %>
    <table>
        <tr> <th> name </th> <th> description </th> </tr>
        <%
            if (orders != null) {
                for (ProductsOrders order: orders) {
        %>
        <tr>
            <td> <%= order.user %> </td>
            <td> <%= order.ProductId %> </td>
            <td> <%= order.Quantity %> </td>
        </tr>
        <%
                }
            }
        %>
    </table>

    <form method="post" action="finalize?action=finalize">
        <button type="submit"> finalize all </button>
    </form>

    <form method="post" action="finalize?action=cancel">
        <button type="submit"> cancel all </button>
    </form>

    <a href="${pageContext.request.contextPath}/home"> home </a>
</body>
</html>
