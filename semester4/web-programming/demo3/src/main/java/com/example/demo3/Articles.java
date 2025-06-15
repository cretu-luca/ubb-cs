package com.example.demo3;

import com.example.demo3.Models.Article;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

@WebServlet("/articles")
public class Articles extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String journalName = request.getParameter("journalName");

        if (journalName != null && !journalName.isEmpty()) {
            String userName = (String) request.getSession().getAttribute("username");

            Map<String, Object> journal = DatabaseConnection.findOne("SELECT * FROM Journals WHERE Name = ?", journalName);

            if (journal != null) {
                Integer journalId = (Integer) journal.get("Id");

                if (journalId != null) {

                    List<Map<String, Object>> articles = DatabaseConnection.executeQuery("SELECT * FROM Articles WHERE JournalId = ? AND User = ?", journalId, userName);
                    List<Article> articleList = new ArrayList<>();

                    for (Map<String, Object> article: articles) {
                        Article newArticle = new Article();
                        newArticle.Id = (Integer)article.get("Id");
                        newArticle.User = (String) article.get("User");
                        newArticle.JournalId = (Integer)article.get("JournalId");
                        newArticle.Summary = (String) article.get("Summary");
                        newArticle.Date = (Integer)article.get("DATE");

                        articleList.add(newArticle);
                    }

                    request.setAttribute("articles", articleList);
                }
            }
        }
        
        request.getRequestDispatcher("/articles.jsp").forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String journalName = request.getParameter("journalName");
        String summary = request.getParameter("summary");
        String userName = (String) request.getSession().getAttribute("username");

        Map<String, Object> journal = DatabaseConnection.findOne("SELECT * FROM Journals WHERE Name = ?", journalName);

        int journalId;

        if (journal == null) {
            journalId = (int) DatabaseConnection.executeInsertAndGetId("INSERT INTO Journals (Name) VALUES (?)", journalName);
        } else {
            journalId = (int) journal.get("Id");
        }

        DatabaseConnection.executeInsertAndGetId("INSERT INTO Articles (User, JournalId, Summary, Date) VALUES (?, ?, ?, ?)",
                userName, journalId, summary, 1);

        request.getRequestDispatcher("/articles.jsp").forward(request, response);
    }
}
