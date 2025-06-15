package com.example.demo2;

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

@WebServlet("/document")
public class DocumentServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Forward to the add document form
        request.getRequestDispatcher("/document.jsp").forward(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");

        switch (action) {
            case "add":
                addDocument(request, response);
                break;
            case "delete":
                deleteDocument(request, response);
                break;
            case "checkCount":
                checkCount(request, response);
                break;
            default:
                break;
        }
    }

    public void addDocument(HttpServletRequest request, HttpServletResponse response) {
        String name = request.getParameter("name");
        String content = request.getParameter("content");
        String authorId = request.getParameter("authorId");

        long documentId = DatabaseConnection.executeInsertAndGetId("INSERT INTO Documents (DocumentName, Contents) VALUES (?, ?)", name, content);

        Map<String, Object> author = DatabaseConnection.findOne("SELECT * FROM Authors WHERE Id = ?", authorId);
        String documentList = (String) author.get("DocumentList");

        documentList = documentList + documentId + ", ";

        DatabaseConnection.executeUpdate("UPDATE Authors SET DocumentList = ? WHERE Id = ?", documentList, authorId);

        Boolean validated = false;

        String[] authoredDocumentsIds =  ((String) author.get("DocumentList")).split(", ");

        List<Document> documents = new ArrayList<Document>();

        for (var docuId : authoredDocumentsIds) {
            if (docuId != null && !docuId.isEmpty()) {
                Map<String, Object> docData = DatabaseConnection.findOne("SELECT * FROM Documents WHERE Id = ?", docuId);
                if (docData != null) {
                    Document doc = new Document();
                    doc.Id = ((Number) docData.get("Id")).intValue();
                    doc.title = (String) docData.get("DocumentName");
                    doc.contents = (String) docData.get("Contents");
                    documents.add(doc);
                }
            }
        }

        request.getSession().setAttribute("documents", documents);
    }

    public void deleteDocument(HttpServletRequest request, HttpServletResponse response) {
        String documentId = request.getParameter("documentId");

        DatabaseConnection.executeUpdate("DELETE FROM Documents WHERE Id = ?", documentId);

        Map<String, Object> user = (Map<String, Object>) request.getSession().getAttribute("loggedInUser");

        String documentList = (String) user.get("DocumentList");
        documentList = documentList.replace(documentId, " ");

        DatabaseConnection.executeUpdate("UPDATE Authors SET DocumentList = ? WHERE Id = ?", documentList, user.get("Id"));
    }

    public void checkCount(HttpServletRequest request, HttpServletResponse response) {
        List<Map<String, Object>> documents = DatabaseConnection.executeQuery("SELECT * FROM Documents");

        for (Object doc : documents) {

        }
    }
}
