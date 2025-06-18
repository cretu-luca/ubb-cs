package com.example.demo6;

import com.example.demo6.Model.Products;
import com.example.demo6.Model.ProductsOrders;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

@WebServlet("/order")
public class Order extends HttpServlet {
    protected void doGet (HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("/order.jsp").forward(request, response);
    }

    protected void doPost (HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String quantity = request.getParameter("quantity");

        List<Products> productsList = DbManager.findAll(Products.class);
        int productId = -1;

        for (Products product : productsList) {
            if (Objects.equals(product.Name, name)) {
                productId = product.Id;
            }
        }

        ProductsOrders order = new ProductsOrders();
        order.Quantity = Integer.parseInt(quantity);
        order.user = request.getSession().getAttribute("username").toString();
        order.ProductId = productId;

        ArrayList<ProductsOrders> sessionOrders = (ArrayList<ProductsOrders>) request.getSession().getAttribute("sessionOrders");
        if (sessionOrders != null) {
            sessionOrders.add(order);
            request.getSession().setAttribute("sessionOrders", sessionOrders);
        } else {
            ArrayList<ProductsOrders> newSessionOrders = new ArrayList<>();
            newSessionOrders.add(order);
            request.getSession().setAttribute("sessionOrders", newSessionOrders);
        }
    }
}
