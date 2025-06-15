package com.example.demo;

import com.example.demo.Model.Author;
import com.example.demo.Model.Movie;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;

import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

@WebServlet("/movies")
public class MovieServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String action = request.getParameter("action");

        if ("delete".equals(action)) {
            showDeletePage(request, response);
        } else {
            response.sendRedirect("dashboard.jsp");
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String action = request.getParameter("action");

        if ("confirmDelete".equals(action)) {
            deleteMovie(request, response);
        } else {
            response.sendRedirect("dashboard.jsp");
        }
    }

    private void showDeletePage(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        Connection conn = null;
        try {
            conn = DatabaseConnection.getConnection();

            // Get all movies
            List<Movie> movies = new ArrayList<>();
            String sql = "SELECT * FROM Movies";
            PreparedStatement stmt = conn.prepareStatement(sql);
            ResultSet rs = stmt.executeQuery();

            while (rs.next()) {
                Movie movie = new Movie(
                        rs.getInt("id"),
                        rs.getString("title"),
                        rs.getInt("duration")
                );
                movies.add(movie);
            }

            request.setAttribute("movies", movies);
            request.getRequestDispatcher("/deleteMovie.jsp").forward(request, response);

        } catch (SQLException e) {
            e.printStackTrace();
            request.setAttribute("error", "Database error: " + e.getMessage());
            request.getRequestDispatcher("/dashboard.jsp").forward(request, response);
        } finally {
            DatabaseConnection.closeConnection(conn);
        }
    }

    private void deleteMovie(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        HttpSession session = request.getSession();
        Author currentAuthor = (Author) session.getAttribute("currentAuthor");

        if (currentAuthor == null) {
            response.sendRedirect("login");
            return;
        }

        String movieTitle = request.getParameter("movieTitle");

        Connection conn = null;
        try {
            conn = DatabaseConnection.getConnection();

            // Delete movie from Movies table
            String deleteSql = "DELETE FROM Movies WHERE title = ?";
            PreparedStatement deleteStmt = conn.prepareStatement(deleteSql);
            deleteStmt.setString(1, movieTitle);
            deleteStmt.executeUpdate();

            // Update author's movie list - remove the movie
            String currentMovies = currentAuthor.getMovieList();
            String newMovies = removeMovieFromList(currentMovies, movieTitle);

            String updateSql = "UPDATE Authors SET movieList = ? WHERE id = ?";
            PreparedStatement updateStmt = conn.prepareStatement(updateSql);
            updateStmt.setString(1, newMovies);
            updateStmt.setInt(2, currentAuthor.getId());
            updateStmt.executeUpdate();

            // Update session
            currentAuthor.setMovieList(newMovies);

            request.setAttribute("success", "Movie deleted successfully!");
            request.getRequestDispatcher("/dashboard.jsp").forward(request, response);

        } catch (SQLException e) {
            e.printStackTrace();
            request.setAttribute("error", "Database error: " + e.getMessage());
            request.getRequestDispatcher("/dashboard.jsp").forward(request, response);
        } finally {
            DatabaseConnection.closeConnection(conn);
        }
    }

    private String removeMovieFromList(String movieList, String movieToRemove) {
        if (movieList == null || movieList.isEmpty()) {
            return "";
        }

        String[] movies = movieList.split(",");
        List<String> newMovies = new ArrayList<>();

        for (String movie : movies) {
            if (!movie.trim().equals(movieToRemove)) {
                newMovies.add(movie.trim());
            }
        }

        return String.join(",", newMovies);
    }
}