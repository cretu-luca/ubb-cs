package com.example.demo4;

import com.example.demo4.Model.*;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.List;
import java.util.Objects;

import static java.lang.System.out;

@WebServlet("/login")
public class Login extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("/login.jsp").forward(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String key = request.getParameter("key");

        List<Author> authors = DbManager.findAll(Author.class);

        Author user = new Author();
        Boolean isValid = false;

        for (Author author: authors) {
            if (Objects.equals(author.Name, username)) {
                user = author;
            }
        }

        String movieList = user.MovieList;
        String[] moviesIds = movieList.split(",");

        for (var id: moviesIds) {
            if (id.trim().equals(key)) {
                isValid = true;
            }

            Movie movie = DbManager.findById(Movie.class, Integer.parseInt(id.trim()));
            if (movie != null) {
                String movieName = movie.Title;
                if (movieName.equals(key)) {
                    isValid = true;
                }
            }
        }

        String documentList = user.DocumentList;
        String[] documentIds = documentList.split(",");

        for (var id: documentIds) {
            if (id.trim().equals(key)) {
                isValid = true;
            }

            Document document = DbManager.findById(Document.class, Integer.parseInt(id.trim()));
            if (document != null) {
                String documentName = document.Name;
                if (documentName.equals(key)) {
                    isValid = true;
                }
            }
        }

        if (isValid) {
            request.getSession().setAttribute("username", username);
            request.getSession().setAttribute("key", key);
            request.getSession().setAttribute("message", "login successful");
        } else {
            request.getSession().setAttribute("message", "login unsuccessful");
        }

        request.getRequestDispatcher("/login.jsp").forward(request, response);
    }
}
