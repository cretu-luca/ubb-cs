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

@WebServlet("/route")
public class RouteController extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        if (!isAuthenticated(request, response)) return;
        
        try {
            showCurrentState(request, response);
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        doGet(request, response);
    }

    private void showCurrentState(HttpServletRequest request, HttpServletResponse response) 
            throws SQLException, ServletException, IOException {
        
        HttpSession session = request.getSession();
        Integer currentCityId = (Integer) session.getAttribute("currentCityId");
        List<Integer> journey = (List<Integer>) session.getAttribute("journey");
        
        if (currentCityId != null && journey != null) {
            request.setAttribute("currentCity", getCityById(currentCityId));
            request.setAttribute("neighbors", getNeighboringCities(currentCityId));
            request.setAttribute("journey", getJourneyCities(journey));
        } else {
            request.setAttribute("cities", getAllCities());
        }
        
        request.getRequestDispatcher("/route.jsp").forward(request, response);
    }

    private boolean isAuthenticated(HttpServletRequest request, HttpServletResponse response) 
            throws IOException {
        HttpSession session = request.getSession();
        if (session.getAttribute("username") == null) {
            response.sendRedirect("login");
            return false;
        }
        return true;
    }

    private List<City> getAllCities() throws SQLException {
        List<City> cities = new ArrayList<>();
        ResultSet resultSet = DatabaseConnection.executeQuery("SELECT * FROM cities");
        
        while (resultSet.next()) {
            cities.add(new City(resultSet.getInt("id"), resultSet.getString("name")));
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

    private List<City> getNeighboringCities(int cityId) throws SQLException {
        List<City> neighbors = new ArrayList<>();
        
        String query = "SELECT DISTINCT c.* FROM cities c " +
                    "JOIN route r ON (c.id = r.finish_city_id OR c.id = r.start_city_id) " +
                    "WHERE (r.start_city_id = ? OR r.finish_city_id = ?) AND c.id != ?";
        
        ResultSet resultSet = DatabaseConnection.executeQuery(query, cityId, cityId, cityId);
        
        while (resultSet.next()) {
            neighbors.add(new City(resultSet.getInt("id"), resultSet.getString("name")));
        }
        
        return neighbors;
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
} 