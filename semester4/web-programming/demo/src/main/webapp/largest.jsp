<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="com.example.demo.Document" %>
<html>
<head>
  <title>Most Popular Document</title>
  <style>
    body { font-family: Arial; margin: 30px; background: #f5f5f5; }
    .container { max-width: 600px; background: white; padding: 30px; border-radius: 8px; }
    .document-card { background: #e7f3ff; padding: 20px; border-radius: 8px; border-left: 5px solid #007cba; margin: 20px 0; }
    .back-btn { background: #6c757d; color: white; padding: 10px 20px; text-decoration: none; border-radius: 5px; }
    .back-btn:hover { background: #545b62; }
    .stats { background: #d4edda; padding: 15px; border-radius: 5px; margin: 15px 0; border-left: 5px solid #28a745; }
    h1 { color: #007cba; }
  </style>
</head>
<body>
<div class="container">
  <h1>📊 Most Popular Document</h1>

  <a href="main?action=dashboard" class="back-btn">← Back to Dashboard</a>

  <%
    Document document = (Document) request.getAttribute("document");
    Integer authorCount = (Integer) request.getAttribute("authorCount");

    if (document != null) {
  %>

  <div class="stats">
    <h3>🏆 Winner!</h3>
    <p>This document has <strong><%= authorCount %> author(s)</strong> - the most of any document in the system!</p>
  </div>

  <div class="document-card">
    <h2>📄 <%= document.getName() %></h2>
    <p><strong>Document ID:</strong> <%= document.getId() %></p>
    <p><strong>Contents:</strong></p>
    <div style="background: white; padding: 15px; border-radius: 5px; margin: 10px 0; border: 1px solid #ddd;">
      <%= document.getContents() %>
    </div>
    <p><strong>Number of Authors:</strong> <span style="color: #28a745; font-weight: bold;"><%= authorCount %></span></p>
  </div>

  <% } else { %>

  <div class="document-card">
    <p>No documents found in the system.</p>
  </div>

  <% } %>

  <div style="margin-top: 30px; text-align: center;">
    <a href="main?action=dashboard" class="back-btn">← Back to Dashboard</a>
  </div>

  <div style="margin-top: 20px; padding: 15px; background: #f8f9fa; border-radius: 5px; font-size: 14px; color: #6c757d;">
    <strong>How this works:</strong> The system counts how many authors have this document in their documentList and finds the one with the highest count.
  </div>
</div>
</body>
</html>