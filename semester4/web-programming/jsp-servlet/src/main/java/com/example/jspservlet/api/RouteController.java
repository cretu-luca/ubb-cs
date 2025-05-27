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
        
        HttpSession session = request.getSession();
        
        if (session.getAttribute("username") == null) {
            response.sendRedirect("login");
            return;
        }
        
        String action = request.getParameter("action");
        
        if (action == null) {
            action = "start";
        }
        
        try {
            switch (action) {
                case "start":
                    handleStart(request, response, session);
                    break;
                case "move":
                    handleMove(request, response, session);
                    break;
                case "back":
                    handleBack(request, response, session);
                    break;
                case "finish":
                    handleFinish(request, response, session);
                    break;
                default:
                    handleStart(request, response, session);
            }
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        doGet(request, response);
    }

    private void handleStart(HttpServletRequest request, HttpServletResponse response, HttpSession session) 
            throws SQLException, ServletException, IOException {
        
        List<City> cities = getAllCities();
        request.setAttribute("cities", cities);
        
        session.removeAttribute("currentCityId");
        session.removeAttribute("journey");
        
        request.getRequestDispatcher("/route.jsp").forward(request, response);
    }

    private void handleMove(HttpServletRequest request, HttpServletResponse response, HttpSession session) 
            throws SQLException, ServletException, IOException {
        
        int cityId = Integer.parseInt(request.getParameter("cityId"));
        
        List<Integer> journey = (List<Integer>) session.getAttribute("journey");
        if (journey == null) {
            journey = new ArrayList<>();
        }
        journey.add(cityId);
        session.setAttribute("journey", journey);
        session.setAttribute("currentCityId", cityId);
        
        City currentCity = getCityById(cityId);
        List<City> neighbors = getNeighboringCities(cityId);
        
        request.setAttribute("currentCity", currentCity);
        request.setAttribute("neighbors", neighbors);
        request.setAttribute("journey", getJourneyCities(journey));
        
        request.getRequestDispatcher("/route.jsp").forward(request, response);
    }

    private void handleBack(HttpServletRequest request, HttpServletResponse response, HttpSession session) 
            throws SQLException, ServletException, IOException {
        
        int stepIndex = Integer.parseInt(request.getParameter("step"));
        
        List<Integer> journey = (List<Integer>) session.getAttribute("journey");
        if (journey != null && stepIndex < journey.size()) {
            journey = journey.subList(0, stepIndex + 1);
            session.setAttribute("journey", journey);
            
            int currentCityId = journey.get(journey.size() - 1);
            session.setAttribute("currentCityId", currentCityId);
            
            City currentCity = getCityById(currentCityId);
            List<City> neighbors = getNeighboringCities(currentCityId);
            
            request.setAttribute("currentCity", currentCity);
            request.setAttribute("neighbors", neighbors);
            request.setAttribute("journey", getJourneyCities(journey));
        }
        
        request.getRequestDispatcher("/route.jsp").forward(request, response);
    }

    private void handleFinish(HttpServletRequest request, HttpServletResponse response, HttpSession session) 
            throws SQLException, ServletException, IOException {
        
        List<Integer> journey = (List<Integer>) session.getAttribute("journey");
        if (journey != null) {
            request.setAttribute("finalRoute", getJourneyCities(journey));
        }
        
        request.getRequestDispatcher("/finish.jsp").forward(request, response);
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