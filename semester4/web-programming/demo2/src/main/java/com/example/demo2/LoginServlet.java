package com.example.demo2;

import com.example.demo2.Model.Author;
import com.example.demo2.Model.Document;
import com.example.demo2.Model.Movie;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("/login.jsp").forward(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

        String username = request.getParameter("username");
        String authored = request.getParameter("authored");

        boolean userFound = false;
        Map<String, Object> foundAuthor = null;

        List<Map<String, Object>> authors = DatabaseConnection.executeQuery("SELECT * FROM Authors");
        for (Map<String, Object> authorRow : authors) {
            if (username.equals(authorRow.get("AuthorName"))) {
                userFound = true;
                foundAuthor = authorRow;
                break;
            }
        }

        if (!userFound) {
            request.setAttribute("error", "User not found! Please check your username.");
            request.getRequestDispatcher("/login.jsp").forward(request, response);
        } else {

            Boolean validated = false;

            String[] authoredMoviesIds =  ((String) foundAuthor.get("MovieList")).split(", ");
            String[] authoredDocumentsIds =  ((String) foundAuthor.get("DocumentList")).split(", ");

            List<Movie> movies = new ArrayList<Movie>();
            List<Document> documents = new ArrayList<Document>();

            for (var movieId : authoredMoviesIds) {
                if (movieId != null && !movieId.isEmpty()) {
                    Map<String, Object> movieData = DatabaseConnection.findOne("SELECT * FROM Movies WHERE Id = ?", movieId);
                    if (movieData != null) {
                        Movie movie = new Movie();
                        movie.Id = ((Number) movieData.get("Id")).intValue();
                        movie.title = (String) movieData.get("Title");
                        movie.duration = ((Number) movieData.get("Duration")).intValue();
                        movies.add(movie);
                        
                        if (movie.title.contains(authored)) {
                            validated = true;
                        }
                    }
                }
            }

            for (var docuId : authoredDocumentsIds) {
                if (docuId != null && !docuId.isEmpty()) {
                    Map<String, Object> docData = DatabaseConnection.findOne("SELECT * FROM Documents WHERE Id = ?", docuId);
                    if (docData != null) {
                        Document doc = new Document();
                        doc.Id = ((Number) docData.get("Id")).intValue();
                        doc.title = (String) docData.get("DocumentName");
                        doc.contents = (String) docData.get("Contents");
                        documents.add(doc);
                        
                        if (doc.title.contains(authored)) {
                            validated = true;
                        }
                    }
                }
            }

            if (validated) {
                request.getSession().setAttribute("loggedInUser", foundAuthor);
                request.getSession().setAttribute("username", username);

                request.getSession().setAttribute("movies", movies);
                request.getSession().setAttribute("documents", documents);

                request.setAttribute("message", "Welcome, " + username + "!");
                request.setAttribute("user", foundAuthor);

                request.getRequestDispatcher("/welcome.jsp").forward(request, response);
            } else {
                request.setAttribute("error", "Invalid movie/document name");
                request.getRequestDispatcher("/login.jsp").forward(request, response);
            }
        }
    }
}
