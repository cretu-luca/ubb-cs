<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
  <title>Welcome</title>
</head>
<body>
<h2>Login Successful!</h2>
<p class="success"><%= request.getAttribute("message") %></p>
<p><a href="interleaved">View Your Movies and Documents</a></p>
<p><a href="<%=request.getContextPath()%>/">Go to Home</a></p>
<p><a href="login">Login Again</a></p>

<label> Document with most authors <%= request.getParameter("documentWithMostAuthors")  %></label>

</body>
</html>