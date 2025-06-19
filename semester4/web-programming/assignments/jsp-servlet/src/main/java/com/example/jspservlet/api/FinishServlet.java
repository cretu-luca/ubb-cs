package com.example.jspservlet.api;

import com.example.jspservlet.db.DatabaseConnection;
import com.example.jspservlet.models.City;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;

import java.io.IOException;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

@WebServlet("/route/finish")
public class FinishServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        HttpSession session = request.getSession();
        
        if (session.getAttribute("username") == null) {
            response.sendRedirect("../login");
            return;
        }

        try {
            List<Integer> journey = (List<Integer>) session.getAttribute("journey");
            if (journey != null) {
                request.setAttribute("finalRoute", getJourneyCities(journey));
            }
            
            request.getRequestDispatcher("../finish.jsp").forward(request, response);
            
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
    }

    private List<City> getJourneyCities(List<Integer> journey) throws SQLException {
        List<City> cities = new ArrayList<>();
        
        for (Integer cityId : journey) {
            City city = getCityById(cityId);
            if (city != null) {
                cities.add(city);
            }
        }
        
        return cities;
    }

    private City getCityById(int id) throws SQLException {
        ResultSet resultSet = DatabaseConnection.executeQuery("SELECT * FROM cities WHERE id = ?", id);
        
        if (resultSet.next()) {
            return new City(resultSet.getInt("id"), resultSet.getString("name"));
        }
        
        return null;
    }
} 