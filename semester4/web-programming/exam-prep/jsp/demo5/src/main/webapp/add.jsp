<%--
  Created by IntelliJ IDEA.
  User: cretuluca
  Date: 17.06.2025
  Time: 20:03
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>add</title>
</head>
<body>
    
    <div id="notification-container" style="display: none; padding: 10px; background-color: lightgreen;">
        <span id="notification-text"></span>
        <button onclick="document.getElementById('notification-container').style.display='none'">X</button>
    </div>

    <form method="post" action="add">
        <p> journal: <input type="text" name="journal"> </p>
        <p> summary: <input type="text" name="summary"> </p>
        <button type="submit"> add </button>
    </form>
    
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
