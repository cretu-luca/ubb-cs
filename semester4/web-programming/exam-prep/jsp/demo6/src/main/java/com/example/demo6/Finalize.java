package com.example.demo6;

import com.example.demo6.Model.ProductsOrders;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Objects;

@WebServlet("/finalize")
public class Finalize extends HttpServlet {
    protected void doGet (HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("/finalize.jsp").forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");

        if (Objects.equals(action, "finalize")) {
            ArrayList<ProductsOrders> orders = (ArrayList<ProductsOrders>) request.getSession().getAttribute("sessionOrders");
            if (orders != null) {
                for (ProductsOrders order : orders) {
                    DbManager.save(order);
                }
            }
        } else {
            request.getSession().removeAttribute("sessionOrders");
        }
    }
}
