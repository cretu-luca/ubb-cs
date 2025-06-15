<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
  <title>Login - Document Management</title>
</head>
<body>
<h1>Document Management System</h1>

<h3>Available Authors:</h3>
<ul>
  <li>John Smith</li>
  <li>Jane Doe</li>
  <li>Bob Wilson</li>
</ul>

<form method="post" action="login">
  <p>
    <label>Enter your name:</label><br>
    <input type="text" name="name" placeholder="e.g. John Smith" required>
  </p>
  <p>
    <button type="submit">Login</button>
  </p>
</form>

<% if (request.getAttribute("error") != null) { %>
<p><strong>Error:</strong> <%= request.getAttribute("error") %></p>
<% } %>
</body>
</html>