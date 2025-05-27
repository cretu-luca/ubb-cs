<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
<head>
    <title>Login</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 50px; }
        .login-form { max-width: 300px; }
        input { margin: 5px 0; padding: 8px; width: 100%; }
        .btn { background: #f0f0f0; border: 1px solid #ccc; border-radius: 3px; cursor: pointer; }
        .error { color: red; margin: 10px 0; }
    </style>
</head>
<body>
    <h2>Login</h2>
    
    <div class="login-form">
        <% if (request.getAttribute("error") != null) { %>
            <div class="error"><%= request.getAttribute("error") %></div>
        <% } %>
        
        <form method="post" action="login">
            <input type="text" name="username" required>
            <input type="password" name="password" required>
            <input type="submit" value="Login" class="btn">
        </form>
    </div>
    
</body>
</html> 