<%@ page import="com.example.demo2.Model.Movie" %>
<%@ page import="java.util.List" %>
<%@ page import="com.example.demo2.Model.Document" %>
<%@ page import="com.example.demo2.Model.Author" %>
<%@ page import="java.util.Map" %><%--
  Created by IntelliJ IDEA.
  User: cretuluca
  Date: 14.06.2025
  Time: 19:57
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
    <%
        List<Movie> movies = (List<Movie>) request.getAttribute("movies");
        List<Document> documents = (List<Document>) request.getAttribute("documents");

        Map<String, Object> user = (Map<String, Object>) request.getAttribute("user");
        
        if (movies != null && documents != null && user != null) {
            int userId = ((Number) user.get("Id")).intValue();

            int documentsNo = documents.size(), movieNo = movies.size(), d_index = 0, m_index = 0;

            while (d_index < documentsNo || m_index < movieNo) {
                if (d_index < documentsNo) {
                    Document doc = documents.get(d_index);
    %>
            <div>
                <p> Document: <%= doc.title %> <p>
                <p> Content: <%= doc.contents %> </p>
            </div>

            <form method="post" action="document?action=delete&documentId=<%= (int) doc.Id %>">
                <button type="submit"> delete document </button>
            </form>

            <hr>
    <%
                    d_index++;
                }

                if (m_index < movieNo) {
                    Movie movie = movies.get(m_index);
    %>

            <div>
                <p> Movie: <%= movie.title %> </p>
                <p> Duration <%= movie.duration %> </p>
            </div>

            <hr>
    <%
                    m_index++;
                }
            }
        } else {
    %>
            <p>No data available. Please make sure you're logged in.</p>
    <%
        }
    %>
</body>
</html>
