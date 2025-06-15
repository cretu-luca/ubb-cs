<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="com.example.demo.Author" %>
<html>
<head>
  <title>Dashboard - Document Management</title>
</head>
<body>
<%
  Author currentAuthor = (Author) session.getAttribute("currentAuthor");
  if (currentAuthor == null) {
    response.sendRedirect("login");
    return;
  }
%>

<h1>Welcome, <%= currentAuthor.getName() %>!</h1>

<% if (request.getAttribute("success") != null) { %>
<p><strong>Success:</strong> <%= request.getAttribute("success") %></p>
<% } %>

<% if (request.getAttribute("error") != null) { %>
<p><strong>Error:</strong> <%= request.getAttribute("error") %></p>
<% } %>

<h2>Menu</h2>
<ul>
  <li><a href="documents?action=interleaved">View Documents & Movies (Interleaved)</a></li>
  <li><a href="documents?action=largest">Most Popular Document</a></li>
  <li><a href="movies?action=delete">Delete Movie</a></li>
  <li><a href="login">Logout</a></li>
</ul>

<hr>

<h2>Add New Document</h2>
<form method="post" action="documents">
  <input type="hidden" name="action" value="add">

  <p>
    <label>Document Name:</label><br>
    <input type="text" name="docName" placeholder="e.g. My Research Paper" required>
  </p>

  <p>
    <label>Contents:</label><br>
    <textarea name="contents" rows="4" cols="50" placeholder="Document content here..." required></textarea>
  </p>

  <p>
    <button type="submit">Add Document</button>
  </p>
</form>

<hr>

<h3>Your Current Data:</h3>
<p><strong>Documents:</strong> <%= currentAuthor.getDocumentList() %></p>
<p><strong>Movies:</strong> <%= currentAuthor.getMovieList() %></p>
</body>
</html>