package com.example.jspservlet.session;

import com.example.jspservlet.db.DatabaseConnection;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;

import java.io.IOException;
import java.sql.ResultSet;
import java.sql.SQLException;

@WebServlet("/login")
public class SessionUtil extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        request.getRequestDispatcher("/login.jsp").forward(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        try {
            if (isValidUser(username, password)) {
                HttpSession session = request.getSession();
                session.setAttribute("username", username);
                response.sendRedirect("route");
            } else {
                request.setAttribute("error", "Invalid username or password");
                request.getRequestDispatcher("/login.jsp").forward(request, response);
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
    }

    private boolean isValidUser(String username, String password) throws SQLException {
        String query = "SELECT * FROM users WHERE username = ? AND password = ?";
        ResultSet resultSet = DatabaseConnection.executeQuery(query, username, password);
        return resultSet.next();
    }
} 