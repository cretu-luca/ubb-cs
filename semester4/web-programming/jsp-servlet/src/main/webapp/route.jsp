<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="java.util.List" %>
<%@ page import="com.example.jspservlet.models.City" %>
<!DOCTYPE html>
<html>
<head>
    <title>Transportation Route</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px; }
        .section { margin: 20px 0; padding: 15px; border: 1px solid #ccc; }
        a { margin-right: 10px; text-decoration: none; color: inherit; }
        a:visited { color: inherit; }
        .btn { padding: 8px 12px; background: #f0f0f0; color: black; border-radius: 3px; border: 1px solid #ccc; }
    </style>
</head>
<body>
    <h1>Transportation Route Planner</h1>

    <%
        String journeyAlert = (String) request.getAttribute("journeyAlert");
        if (journeyAlert != null) {
    %>
        <script>
            alert("<%= journeyAlert %>");
            window.location.href = "route?action=start";
        </script>
    <%
        }
    %>

    <div class="section">
        <h3>Current Journey</h3>
        <%
            List<City> journey = (List<City>) request.getAttribute("journey");
            if (journey == null || journey.isEmpty()) {
        %>
            <p>No cities selected yet. Choose a starting city below.</p>
        <%
            } else {
                for (int i = 0; i < journey.size(); i++) {
                    City city = journey.get(i);
        %>
            <div>
                Step <%= i + 1 %>: 
                <a href="route?action=back&step=<%= i %>"><%= city.getName() %></a>
                <%= i == journey.size() - 1 ? " (Current)" : "" %>
            </div>
        <%
                }
            }
        %>
    </div>

    <div class="section">
        <h3>Current City</h3>
        <%
            City currentCity = (City) request.getAttribute("currentCity");
            if (currentCity == null) {
        %>
            <p>None</p>
        <%
            } else {
        %>
            <p><%= currentCity.getName() %></p>
        <%
            }
        %>
    </div>

    <div class="section">
        <h3>
            <%= currentCity == null ? "All Cities (Choose Starting Point)" : "Neighboring Cities" %>
        </h3>
        <%
            List<City> cities = (List<City>) request.getAttribute("neighbors");
            if (cities == null) {
                cities = (List<City>) request.getAttribute("cities");
            }
            
            if (cities == null || cities.isEmpty()) {
        %>
            <p>No cities available.</p>
        <%
            } else {
                for (City city : cities) {
        %>
            <a href="route?action=move&cityId=<%= city.getId() %>" class="btn">
                <%= city.getName() %>
            </a>
        <%
                }
            }
        %>
    </div>

    <div>
        <%
            if (journey != null && !journey.isEmpty()) {
        %>
            <a href="route?action=finish" class="btn">Finish Journey</a>
        <%
            }
        %>
        <a href="route?action=start" class="btn">Start Over</a>
    </div>

</body>
</html> 