package com.example.demo6;

import com.example.demo6.Model.Products;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;

@WebServlet("/add")
public class Add extends HttpServlet {
    protected void doGet (HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("/add.jsp").forward(request, response);
    }

    protected void doPost (HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String description = request.getParameter("description");

        Products product = new Products();
        product.Name = name;
        product.Description = description;

        DbManager.save(product);
        request.getRequestDispatcher("/add.jsp").forward(request, response);
    }
}
