package com.example.demo4;

import com.example.demo4.Model.Author;
import com.example.demo4.Model.Document;
import com.example.demo4.Model.Movie;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.List;
import java.util.Objects;

@WebServlet("/all")
public class All extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<Movie> movies = DbManager.findAll(Movie.class);
        List<Document> documents = DbManager.findAll(Document.class);

        request.getSession().setAttribute("movies", movies);
        request.getSession().setAttribute("documents", documents);

        request.getRequestDispatcher("/all.jsp").forward(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");
        String id = request.getParameter("id");

        if (Objects.equals(action, "movie")) {
            Movie movie = DbManager.findById(Movie.class, Integer.parseInt(id));
            DbManager.delete(movie);
        }

        if (Objects.equals(action, "document")) {
            Document document = DbManager.findById(Document.class, Integer.parseInt(id));
            DbManager.delete(document);
        }
        
        List<Movie> movies = DbManager.findAll(Movie.class);
        List<Document> documents = DbManager.findAll(Document.class);

        request.getSession().setAttribute("movies", movies);
        request.getSession().setAttribute("documents", documents);
        
        response.sendRedirect("all");
    }
}
