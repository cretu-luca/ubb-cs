package com.example.demo2;

import com.example.demo2.Model.Document;
import com.example.demo2.Model.Movie;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.List;
import java.util.Map;

@WebServlet("/interleaved")
public class Interleaved extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Get the logged in user from session
        Map<String, Object> user = (Map<String, Object>) request.getSession().getAttribute("loggedInUser");
        
        if (user == null) {
            response.sendRedirect("login");
            return;
        }
        
        // Get the movies and documents from the session
        List<Movie> movies = (List<Movie>) request.getSession().getAttribute("movies");
        List<Document> documents = (List<Document>) request.getSession().getAttribute("documents");
        
        // Set attributes for the JSP
        request.setAttribute("movies", movies);
        request.setAttribute("documents", documents);
        request.setAttribute("user", user);
        
        // Forward to the JSP
        request.getRequestDispatcher("/interleaved.jsp").forward(request, response);
    }
}
