package com.example.demo;

import com.example.demo.Model.Author;
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


@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Show login page
        request.getRequestDispatcher("/login.jsp").forward(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String name = request.getParameter("name");

        if (name == null || name.trim().isEmpty()) {
            request.setAttribute("error", "Please enter a name");
            request.getRequestDispatcher("/login.jsp").forward(request, response);
            return;
        }

        Connection conn = null;
        try {
            conn = DatabaseConnection.getConnection();

            // Find author by name
            String sql = "SELECT * FROM Authors WHERE name = ?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, name.trim());

            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                // Author found - create session
                Author author = new Author(
                        rs.getInt("id"),
                        rs.getString("name"),
                        rs.getString("documentList"),
                        rs.getString("movieList")
                );

                HttpSession session = request.getSession();
                session.setAttribute("currentAuthor", author);

                response.sendRedirect("dashboard.jsp");
            } else {
                // Author not found
                request.setAttribute("error", "Author not found!");
                request.getRequestDispatcher("/login.jsp").forward(request, response);
            }

        } catch (SQLException e) {
            e.printStackTrace();
            request.setAttribute("error", "Database error: " + e.getMessage());
            request.getRequestDispatcher("/login.jsp").forward(request, response);
        } finally {
            DatabaseConnection.closeConnection(conn);
        }
    }
}