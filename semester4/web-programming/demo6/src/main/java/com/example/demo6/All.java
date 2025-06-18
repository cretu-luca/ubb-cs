package com.example.demo6;

import com.example.demo6.Model.Products;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

@WebServlet("/all")
public class All extends HttpServlet {
    protected void doGet (HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<Products> products = new ArrayList<>();
        request.setAttribute("products", products);

        request.getRequestDispatcher("/all.jsp").forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String query = request.getParameter("query");
        List<Products> products = DbManager.findAll(Products.class);
        List<Products> filteredProducts = new ArrayList<>();

        for (Products product : products) {
            if (product.Name.startsWith(query)) {
                filteredProducts.add(product);
            }
        }

        request.setAttribute("products", filteredProducts);
        request.getRequestDispatcher("/all.jsp").forward(request, response);
    }
}
