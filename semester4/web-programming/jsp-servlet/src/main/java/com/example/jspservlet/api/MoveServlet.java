package com.example.jspservlet.api;

import com.example.jspservlet.db.DatabaseConnection;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;

import java.io.IOException;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

@WebServlet("/route/move")
public class MoveServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        HttpSession session = request.getSession();
        
        if (session.getAttribute("username") == null) {
            response.sendRedirect("../login");
            return;
        }

        try {
            int cityId = Integer.parseInt(request.getParameter("cityId"));
            String username = (String) session.getAttribute("username");
            
            List<Integer> journey = (List<Integer>) session.getAttribute("journey");
            if (journey == null) {
                journey = new ArrayList<>();
            }
            journey.add(cityId);
            session.setAttribute("journey", journey);
            session.setAttribute("currentCityId", cityId);
            
            // Handle journey tracking
            Integer currentJourneyId = (Integer) session.getAttribute("currentJourneyId");
            if (currentJourneyId == null) {
                currentJourneyId = DatabaseConnection.getNextJourneyId(username);
                session.setAttribute("currentJourneyId", currentJourneyId);
            }
            
            int stepNumber = DatabaseConnection.getNextStepInJourney(username, currentJourneyId);
            DatabaseConnection.saveStep(username, cityId, stepNumber, currentJourneyId);
            
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
        
        response.sendRedirect("../route");
    }
} 