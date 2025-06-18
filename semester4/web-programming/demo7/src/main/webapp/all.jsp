<%@ page import="com.example.demo7.Model.MyProduct" %>
<%@ page import="java.util.List" %><%--
  Created by IntelliJ IDEA.
  User: cretuluca
  Date: 18.06.2025
  Time: 16:48
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>all products</title>
</head>
<body>

<p> select items: </p>

    <table>
        <tr> <th> Name </th> <th> Price </th> </tr>
        <%
            List<MyProduct> products = (List<MyProduct>) request.getSession().getAttribute("products");

            if (products != null) {
            for (MyProduct myProduct: products) {
        %>
        <form method="post" action="all?action=addToOrder">
            <tr>
                <input type="hidden" value='<%= myProduct.Id %>' name="productId" />
                <td> <%= myProduct.Name %> </td>
                <td> <%= myProduct.Price %> </td>
                <td> <button type="submit"> add </button> </td>
            </tr>
        </form>
        <%
            }
          }
        %>
    </table>


<p> current order: </p>
    <table>
        <tr> <th> Name </th> <th> Price </th> </tr>
        <%
            List<MyProduct> orderProducts = (List<MyProduct>) request.getSession().getAttribute("orderProducts");
            if (orderProducts != null) {
            for (MyProduct myProduct: orderProducts) {
        %>
            <tr>
                <td> <%= myProduct.Name %> </td>
                <td> <%= myProduct.Price %> </td>
            </tr>
        <%
            }
            }
        %>
    </table>

<form method="post" action="all?action=confirmOrder">
    <button method="submit"> confirm </button>
</form>

<% if (request.getSession().getAttribute("finalPrice") != null) {
%>
<p> Total price: <%= request.getSession().getAttribute("finalPrice") %> </p>
<%
    }
%>

</body>
</html>
