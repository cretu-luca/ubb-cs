<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="java.util.List" %>
<%@ page import="com.example.demo.Movie" %>
<%@ page import="com.example.demo.Author" %>
<html>
<head>
  <title>Delete Movie</title>
  <style>
    body { font-family: Arial; margin: 30px; background: #f5f5f5; }
    .container { max-width: 600px; background: white; padding: 30px; border-radius: 8px; }
    .movie-item { background: #fff3cd; padding: 15px; margin: 10px 0; border-radius: 5px; border-left: 5px solid #ffc107; }
    .back-btn { background: #6c757d; color: white; padding: 10px 20px; text-decoration: none; border-radius: 5px; }
    .delete-btn { background: #dc3545; color: white; padding: 8px 16px; border: none; cursor: pointer; border-radius: 5px; margin-left: 10px; }
    .delete-btn:hover { background: #c82333; }
    .warning { background: #f8d7da; color: #721c24; padding: 15px; border-radius: 5px; margin: 15px 0; border-left: 5px solid #dc3545; }
    select { padding: 10px; margin: 10px; border: 1px solid #ddd; border-radius: 5px; }
  </style>
</head>
<body>
<div class="container">
  <h1>🗑️ Delete Movie</h1>

  <a href="main?action=dashboard" class="back-btn">← Back to Dashboard</a>

  <%
    Author currentAuthor = (Author) session.getAttribute("currentAuthor");
    List<Movie> movies = (List<Movie>) request.getAttribute("movies");
  %>

  <div class="warning">
    <strong>⚠️ Warning:</strong> Deleting a movie will remove it from the entire system and update your movieList.
  </div>

  <% if (currentAuthor.getMovieList().isEmpty()) { %>

  <div style="background: #f8f9fa; padding: 20px; border-radius: 5px; text-align: center; margin: 20px 0;">
    <p>You don't have any movies in your list to delete.</p>
    <p><strong>Your current movies:</strong> (none)</p>
  </div>

  <% } else { %>

  <div style="background: #e9ecef; padding: 15px; border-radius: 5px; margin: 20px 0;">
    <strong>Your current movies:</strong> <%= currentAuthor.getMovieList() %>
  </div>

  <h3>Select a movie to delete:</h3>

  <% if (movies != null && !movies.isEmpty()) { %>

  <form method="post" action="main" onsubmit="return confirm('Are you sure you want to delete this movie? This action cannot be undone.')">
    <input type="hidden" name="action" value="confirmDelete">

    <select name="movieTitle" required>
      <option value="">-- Select a movie to delete --</option>
      <%
        for (Movie movie : movies) {
          // Only show movies that the current author has
          if (currentAuthor.getMovieList().contains(movie.getTitle())) {
      %>
      <option value="<%= movie.getTitle() %>">
        <%= movie.getTitle() %> (<%= movie.getDuration() %> min)
      </option>
      <%
          }
        }
      %>
    </select>

    <button type="submit" class="delete-btn">🗑️ Delete Selected Movie</button>
  </form>

  <% } else { %>

  <p>No movies available in the system.</p>

  <% } %>

  <% } %>

  <div style="margin-top: 30px; text-align: center;">
    <a href="main?action=dashboard" class="back-btn">← Back to Dashboard</a>
  </div>

  <div style="margin-top: 20px; padding: 15px; background: #f8f9fa; border-radius: 5px; font-size: 14px; color: #6c757d;">
    <strong>Note:</strong> Only movies that you currently have in your movieList are available for deletion.
  </div>
</div>
</body>
</html>