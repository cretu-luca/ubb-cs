<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="java.util.List" %>
<%@ page import="com.example.jspservlet.models.City" %>
<!DOCTYPE html>
<html>
<head>
    <title>Journey Complete</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px; }
        .section { margin: 20px 0; padding: 15px; border: 1px solid #ccc; }
        a { margin-right: 10px; text-decoration: none; color: inherit; }
        a:visited { color: inherit; }
        .btn { padding: 8px 12px; background: #f0f0f0; color: black; border-radius: 3px; border: 1px solid #ccc; }
        .route-step { margin: 5px 0; }
    </style>
</head>
<body>
    <h1>Journey Complete!</h1>

    <div class="section">
        <h3>Your Complete Route</h3>
        <%
            List<City> finalRoute = (List<City>) request.getAttribute("finalRoute");
            if (finalRoute == null || finalRoute.isEmpty()) {
        %>
            <p>No route to display.</p>
        <%
            } else {
                for (int i = 0; i < finalRoute.size(); i++) {
                    City city = finalRoute.get(i);
        %>
            <div class="route-step">
                <%= i + 1 %>. <%= city.getName() %>
            </div>
        <%
                }
        %>
            <p><strong>Total stops: <%= finalRoute.size() %></strong></p>
        <%
            }
        %>
    </div>

    <div>
        <a href="../route" class="btn">Plan New Journey</a>
    </div>

</body>
</html> 