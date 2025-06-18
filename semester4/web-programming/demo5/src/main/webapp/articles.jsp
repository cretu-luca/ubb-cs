<%@ page import="com.example.demo5.Model.Journal" %>
<%@ page import="java.util.List" %>
<%@ page import="com.example.demo5.Model.Article" %><%--
  Created by IntelliJ IDEA.
  User: cretuluca
  Date: 17.06.2025
  Time: 19:29
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>articles</title>
</head>
<body>
    <div id="notification-container" style="display: none; padding: 10px; background-color: lightgreen;">
        <span id="notification-text"></span>
        <button onclick="document.getElementById('notification-container').style.display='none'">X</button>
    </div>
    
    <form method="post" action="articles">
        <p> journal: <input type="text" name="journal"> </p>
        <button> search </button>
    </form>

    <table>
        <tr> <th> user </th> <th> journalId </th> <th> summary </th> <th> date </th> </tr>
<%
    List<Article> articles = (List<Article>) request.getAttribute("articles");
    for (Article article: articles) {
%>
    <tr>
        <td> <%= article.User %> </td>
        <td> <%= article.JournalId %> </td>
        <td> <%= article.Summary %> </td>
        <td> <%= article.Date %> </td>
    </tr>
<%
    }
%>
    </table>
    
    <script>
        const eventSource = new EventSource("${pageContext.request.contextPath}/notification-stream");
        
        eventSource.onmessage = function(event) {
            const notificationContainer = document.getElementById('notification-container');
            const notificationText = document.getElementById('notification-text');
            
            notificationText.textContent = event.data;
            notificationContainer.style.display = 'block';
            
            setTimeout(() => {
                notificationContainer.style.display = 'none';
            }, 5000);
        };
        
        eventSource.onerror = function() {
            eventSource.close();
        };
    </script>
</body>
</html>
