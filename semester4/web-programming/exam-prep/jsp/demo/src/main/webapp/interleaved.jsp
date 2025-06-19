<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="java.util.List" %>
<%@ page import="com.example.demo.Document" %>
<%@ page import="com.example.demo.Movie" %>
<html>
<head>
  <title>Documents & Movies - Interleaved View</title>
  <style>
    body { font-family: Arial; margin: 30px; background: #f5f5f5; }
    .container { max-width: 800px; background: white; padding: 30px; border-radius: 8px; }
    .item { margin: 15px 0; padding: 15px; border-radius: 5px; border-left: 5px solid #007cba; }
    .document { background: #e7f3ff; border-left-color: #007cba; }
    .movie { background: #fff3cd; border-left-color: #ffc107; }
    .back-btn { background: #6c757d; color: white; padding: 10px 20px; text-decoration: none; border-radius: 5px; }
    .back-btn:hover { background: #545b62; }
    h3 { margin: 0 0 10px 0; }
    .type-badge { display: inline-block; background: #007cba; color: white; padding: 3px 8px; border-radius: 12px; font-size: 12px; margin-bottom: 5px; }
    .movie .type-badge { background: #ffc107; color: #212529; }
  </style>
</head>
<body>
<div class="container">
  <h1>📋 Documents & Movies (Interleaved)</h1>

  <a href="main?action=dashboard" class="back-btn">← Back to Dashboard</a>

  <div style="margin: 20px 0;">
    <%
      List<Object> items = (List<Object>) request.getAttribute("items");
      if (items != null && !items.isEmpty()) {
        for (Object item : items) {
          if (item instanceof Document) {
            Document doc = (Document) item;
    %>
    <div class="item document">
      <div class="type-badge">📄 DOCUMENT</div>
      <h3><%= doc.getName() %></h3>
      <p><strong>ID:</strong> <%= doc.getId() %></p>
      <p><strong>Contents:</strong> <%= doc.getContents() %></p>
    </div>
    <%
    } else if (item instanceof Movie) {
      Movie movie = (Movie) item;
    %>
    <div class="item movie">
      <div class="type-badge">🎬 MOVIE</div>
      <h3><%= movie.getTitle() %></h3>
      <p><strong>ID:</strong> <%= movie.getId() %></p>
      <p><strong>Duration:</strong> <%= movie.getDuration() %> minutes</p>
    </div>
    <%
        }
      }
    } else {
    %>
    <div class="item">
      <p>No documents or movies found.</p>
    </div>
    <%
      }
    %>
  </div>

  <div style="margin-top: 30px; text-align: center;">
    <a href="main?action=dashboard" class="back-btn">← Back to Dashboard</a>
  </div>
</div>
</body>
</html>