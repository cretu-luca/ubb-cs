package com.example.demo5;

import com.example.demo5.Model.Article;
import com.example.demo5.Model.Journal;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

@WebServlet("/articles")
public class Articles extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        List<Article> articles = new ArrayList<>();
        request.setAttribute("articles", articles);
        request.getRequestDispatcher("/articles.jsp").forward(request, response);
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String journalName = request.getParameter("journal");
        String username = request.getSession().getAttribute("username").toString();

        System.out.println(journalName);
        System.out.println(username);

        int journalId = -1;
        List<Journal> journal = DbManager.findAll(Journal.class);
        for (Journal j : journal) {
            if (Objects.equals(j.Name, journalName)) {
                journalId = j.Id;
            }
        }

        List<Article> articles = DbManager.findAll(Article.class);
        List<Article> userArticles = new ArrayList<>();

        for (Article article : articles) {
            if (Objects.equals(article.User, username) && journalId == article.JournalId) {
                userArticles.add(article);
            }
        }

        request.setAttribute("articles", userArticles);
        request.getRequestDispatcher("/articles.jsp").forward(request, response);
    }
}
