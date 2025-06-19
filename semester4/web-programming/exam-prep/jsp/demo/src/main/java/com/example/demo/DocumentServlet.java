package com.example.demo;

import com.example.demo.Model.Author;
import com.example.demo.Model.Document;
import com.example.demo.Model.Movie;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;

import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

@WebServlet("/documents")
public class DocumentServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String action = request.getParameter("action");

        if ("interleaved".equals(action)) {
            showInterleavedView(request, response);
        } else if ("largest".equals(action)) {
            showLargestDocument(request, response);
        } else {
            response.sendRedirect("dashboard.jsp");
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String action = request.getParameter("action");

        if ("add".equals(action)) {
            addDocument(request, response);
        } else {
            response.sendRedirect("dashboard.jsp");
        }
    }

    private void addDocument(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        HttpSession session = request.getSession();
        Author currentAuthor = (Author) session.getAttribute("currentAuthor");

        if (currentAuthor == null) {
            response.sendRedirect("login");
            return;
        }

        String docName = request.getParameter("docName");
        String contents = request.getParameter("contents");

        Connection conn = null;
        try {
            conn = DatabaseConnection.getConnection();

            // Insert new document
            String sql = "INSERT INTO Documents (name, contents) VALUES (?, ?)";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, docName);
            stmt.setString(2, contents);
            stmt.executeUpdate();

            // Update author's document list
            String currentDocs = currentAuthor.getDocumentList();
            String newDocs = currentDocs.isEmpty() ? docName : currentDocs + "," + docName;

            String updateSql = "UPDATE Authors SET documentList = ? WHERE id = ?";
            PreparedStatement updateStmt = conn.prepareStatement(updateSql);
            updateStmt.setString(1, newDocs);
            updateStmt.setInt(2, currentAuthor.getId());
            updateStmt.executeUpdate();

            // Update session
            currentAuthor.setDocumentList(newDocs);

            request.setAttribute("success", "Document added successfully!");
            request.getRequestDispatcher("/dashboard.jsp").forward(request, response);

        } catch (SQLException e) {
            e.printStackTrace();
            request.setAttribute("error", "Database error: " + e.getMessage());
            request.getRequestDispatcher("/dashboard.jsp").forward(request, response);
        } finally {
            DatabaseConnection.closeConnection(conn);
        }
    }

    private void showInterleavedView(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        Connection conn = null;
        try {
            conn = DatabaseConnection.getConnection();

            List<Object> items = new ArrayList<>();

            // Get all documents
            String docSql = "SELECT * FROM Documents";
            PreparedStatement docStmt = conn.prepareStatement(docSql);
            ResultSet docRs = docStmt.executeQuery();

            while (docRs.next()) {
                Document doc = new Document(
                        docRs.getInt("id"),
                        docRs.getString("name"),
                        docRs.getString("contents")
                );
                items.add(doc);
            }

            // Get all movies
            String movieSql = "SELECT * FROM Movies";
            PreparedStatement movieStmt = conn.prepareStatement(movieSql);
            ResultSet movieRs = movieStmt.executeQuery();

            while (movieRs.next()) {
                Movie movie = new Movie(
                        movieRs.getInt("id"),
                        movieRs.getString("title"),
                        movieRs.getInt("duration")
                );
                items.add(movie);
            }

            request.setAttribute("items", items);
            request.getRequestDispatcher("/interleaved.jsp").forward(request, response);

        } catch (SQLException e) {
            e.printStackTrace();
            request.setAttribute("error", "Database error: " + e.getMessage());
            request.getRequestDispatcher("/dashboard.jsp").forward(request, response);
        } finally {
            DatabaseConnection.closeConnection(conn);
        }
    }

    private void showLargestDocument(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        Connection conn = null;
        try {
            conn = DatabaseConnection.getConnection();

            // Get all documents and count authors for each
            String sql = "SELECT * FROM Documents";
            PreparedStatement stmt = conn.prepareStatement(sql);
            ResultSet rs = stmt.executeQuery();

            Document largestDoc = null;
            int maxAuthors = 0;

            while (rs.next()) {
                Document doc = new Document(
                        rs.getInt("id"),
                        rs.getString("name"),
                        rs.getString("contents")
                );

                // Count authors for this document
                int authorCount = countAuthorsForDocument(conn, doc.getName());

                if (authorCount > maxAuthors) {
                    maxAuthors = authorCount;
                    largestDoc = doc;
                }
            }

            request.setAttribute("document", largestDoc);
            request.setAttribute("authorCount", maxAuthors);
            request.getRequestDispatcher("/largest.jsp").forward(request, response);

        } catch (SQLException e) {
            e.printStackTrace();
            request.setAttribute("error", "Database error: " + e.getMessage());
            request.getRequestDispatcher("/dashboard.jsp").forward(request, response);
        } finally {
            DatabaseConnection.closeConnection(conn);
        }
    }

    private int countAuthorsForDocument(Connection conn, String docName) throws SQLException {
        String sql = "SELECT COUNT(*) FROM Authors WHERE documentList LIKE ?";
        PreparedStatement stmt = conn.prepareStatement(sql);
        stmt.setString(1, "%" + docName + "%");

        ResultSet rs = stmt.executeQuery();
        if (rs.next()) {
            return rs.getInt(1);
        }
        return 0;
    }
}