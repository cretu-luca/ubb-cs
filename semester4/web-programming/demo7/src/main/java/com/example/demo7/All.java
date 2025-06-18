package com.example.demo7;

import com.example.demo7.Model.MyOrder;
import com.example.demo7.Model.MyOrderItem;
import com.example.demo7.Model.MyProduct;
import com.example.demo7.Model.MyUser;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

@WebServlet("/all")
public class All extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        List<MyProduct> allProducts = DbManager.findAll(MyProduct.class);
        List<MyProduct> orderProducts = new ArrayList<>();

        request.getSession().setAttribute("orderProducts", orderProducts);
        request.getSession().setAttribute("products", allProducts);
        request.getRequestDispatcher("/all.jsp").forward(request, response);
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String action = request.getParameter("action");
        String productId = request.getParameter("productId");

        if (Objects.equals(action, "addToOrder")) {
            //
            List<MyOrder> allOrders = DbManager.findAll(MyOrder.class);

            // List<MyOrder> last3 = allOrders.subList(allOrders.size() - Math.min(allOrders.size(), 3), allOrders.size());



            //
            List<MyProduct> allProducts = DbManager.findAll(MyProduct.class);

            MyProduct productToAdd = null;

            for (MyProduct myProduct: allProducts) {
                if (myProduct.Id == Integer.parseInt(productId)) {
                    productToAdd = myProduct;
                }
            }

            List<MyProduct> orderProducts = (List<MyProduct>) request.getSession().getAttribute("orderProducts");
            orderProducts.add(productToAdd);
            request.getSession().setAttribute("orderProducts", orderProducts);
        } else if (Objects.equals(action, "confirmOrder")) {
            String username = request.getSession().getAttribute("username").toString();

            List<MyUser> allUsers = DbManager.findAll(MyUser.class);
            int userId = -1;

            for (MyUser user: allUsers) {
                if (Objects.equals(user.Username, username)) {
                    userId = user.Id;
                }
            }

            MyOrder myOrder = new MyOrder();
            myOrder.UserId = userId;

            List<MyProduct> orderProducts = (List<MyProduct>) request.getSession().getAttribute("orderProducts");
            List<String> categories = new ArrayList<>();

            boolean doubleCat = false;
            boolean moreThanThree = false;

            double initialPrice = 0;

            for (MyProduct product: orderProducts) {
                initialPrice = initialPrice + product.Price;
            }

            if (orderProducts.size() >= 3) {
                moreThanThree = true;
            }

            // extragem categoriile
            for (MyProduct product: orderProducts) {
                String category = product.Name.split("-")[0];
                categories.add(category);
            }

            for (int i = 0; i < categories.size(); i++) {
                for (int j = 0; j < categories.size(); j++) {
                    if (Objects.equals(categories.get(i), categories.get(j)) && i != j) {
                        // doua categorii
                        doubleCat = true;

                    }
                }
            }

            if (moreThanThree) {
                initialPrice = initialPrice - initialPrice / 10;
            }

            if (doubleCat) {
                initialPrice = initialPrice - initialPrice / 20;
            }

            myOrder.TotalPrice = initialPrice;

            MyOrder addedOrder = DbManager.save(myOrder);
            int addedOrderId = addedOrder.Id;

            for (MyProduct product: orderProducts) {
                MyOrderItem orderItem = new MyOrderItem();
                orderItem.OrderId = addedOrderId;
                orderItem.ProductId = product.Id;

                DbManager.save(orderItem);
            }

            request.getSession().setAttribute("finalPrice", initialPrice);
        }

        request.getRequestDispatcher("/all.jsp").forward(request, response);
    }
}
