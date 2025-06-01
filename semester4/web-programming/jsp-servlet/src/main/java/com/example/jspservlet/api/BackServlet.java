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
import java.util.List;

@WebServlet("/route/back")
public class BackServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        HttpSession session = request.getSession();
        
        if (session.getAttribute("username") == null) {
            response.sendRedirect("../login");
            return;
        }

        try {
            int stepIndex = Integer.parseInt(request.getParameter("step"));
            String username = (String) session.getAttribute("username");
            Integer currentJourneyId = (Integer) session.getAttribute("currentJourneyId");
            
            List<Integer> journey = (List<Integer>) session.getAttribute("journey");
            if (journey != null && stepIndex < journey.size() && currentJourneyId != null) {
                int stepsToRemove = journey.size() - (stepIndex + 1);
                
                // Remove steps from database
                if (stepsToRemove > 0) {
                    int maxStep = DatabaseConnection.getMaxStepInJourney(username, currentJourneyId);
                    int deleteFromStep = maxStep - stepsToRemove + 1;
                    DatabaseConnection.deleteStepsFrom(username, currentJourneyId, deleteFromStep);
                }
                
                // Update session
                journey = journey.subList(0, stepIndex + 1);
                session.setAttribute("journey", journey);
                
                int currentCityId = journey.get(journey.size() - 1);
                session.setAttribute("currentCityId", currentCityId);
            }
            
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }
        
        response.sendRedirect("../route");
    }
} 