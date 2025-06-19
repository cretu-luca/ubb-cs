package com.example.demo5;

import com.example.demo5.Model.Article;
import com.example.demo5.Model.Journal;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

@WebServlet("/add")
public class Add extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        request.getRequestDispatcher("/add.jsp").forward(request, response);
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String journal = request.getParameter("journal");
        String summary = request.getParameter("summary");
        String username = request.getSession().getAttribute("username").toString();

        Journal foundJournal = null;

        List<Journal> journals = DbManager.findAll(Journal.class);
        for (Journal j : journals) {
            if (Objects.equals(j.Name, journal)) {
                foundJournal = j;
            }
        }

        if (foundJournal == null) {
            foundJournal = new Journal();
            foundJournal.Name = journal;

            foundJournal = DbManager.save(foundJournal);
        }

        Article article = new Article();
        article.JournalId = foundJournal.Id;
        article.Summary = summary;
        article.User = username;
        article.Date = LocalDate.parse("2025-10-10");

        DbManager.save(article);
        
        String notification = username + " added a new article: " + summary;
        NotificationServlet.sendNotification(notification);
        
        request.getRequestDispatcher("/add.jsp").forward(request, response);
    }
}
