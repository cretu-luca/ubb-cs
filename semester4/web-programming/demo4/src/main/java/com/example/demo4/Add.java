package com.example.demo4;

import com.example.demo4.Model.Author;
import com.example.demo4.Model.Document;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.List;
import java.util.Objects;

@WebServlet("/add")
public class Add extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("/add.jsp").forward(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String contents = request.getParameter("contents");
        String username = request.getSession().getAttribute("username").toString();

        Document document = new Document();
        document.Name = name;
        document.Contents = contents;

        Document newDocument = DbManager.save(document);
        int documentId = newDocument.Id;

        Author currentUser = null;
        List<Author> users = DbManager.findAll(Author.class);
        for (Author user: users) {
            if (Objects.equals(user.Name, username)) {
                currentUser = user;
            }
        }
        
        if (currentUser != null) {
            currentUser.DocumentList += "," + documentId + ",";
            DbManager.update(currentUser);
        }

        request.getRequestDispatcher("/add.jsp").forward(request, response);
    }
}
