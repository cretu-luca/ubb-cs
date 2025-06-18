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

@WebServlet("/most")
public class Most extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<Author> authors = DbManager.findAll(Author.class);

        int[] authorsPerDocument = new int[1000];

        for (Author author: authors) {
            String[] documentIdsArray = author.DocumentList.split(",");

            for (String documentId: documentIdsArray) {
                int Id = Integer.parseInt(documentId.trim());
                authorsPerDocument[Id]++;
            }
        }

        int key = -1, value = -1;

        for (int i = 0; i < 1000; i++) {
            if (authorsPerDocument[i] > value) {
                value = authorsPerDocument[i];
                key = i;
            }
        }

        Document doc = DbManager.findById(Document.class, key);
        request.setAttribute("mostAuthorsDocument", doc);

        request.getRequestDispatcher("/most.jsp").forward(request, response);
    }
}
