package com.example.jspservlet.db;

import java.sql.*;

public class DatabaseConnection {
    private static final String url = "jdbc:mysql://localhost:3306/transport";
    private static final String username = "root";
    private static final String password = "";

    public static Connection getConnection() throws SQLException {
        return DriverManager.getConnection(url, username, password);
    }

    public static ResultSet executeQuery(String sql, Object... params) throws SQLException {
        Connection connection = getConnection();
        PreparedStatement statement = connection.prepareStatement(sql);
        
        for (int i = 0; i < params.length; i++) {
            statement.setObject(i + 1, params[i]);
        }
        
        return statement.executeQuery();
    }

    public static int executeUpdate(String sql, Object... params) throws SQLException {
        try (Connection connection = getConnection();
             PreparedStatement statement = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
            
            for (int i = 0; i < params.length; i++) {
                statement.setObject(i + 1, params[i]);
            }
            
            int rowsAffected = statement.executeUpdate();
            
            try (ResultSet resultSet = statement.getGeneratedKeys()) {
                if (resultSet.next()) {
                    return resultSet.getInt(1);
                }
            } catch (SQLException e) {
            }
            
            return rowsAffected;
        }
    }

    public static void saveStep(String username, int cityId, int step, int journeyId) throws SQLException {
        ResultSet userResult = executeQuery("SELECT id FROM users WHERE username = ?", username);
        if (!userResult.next()) {
            throw new SQLException("User not found: " + username);
        }
        int userId = userResult.getInt("id");
        
        executeUpdate("INSERT INTO journey (journey_id, user_id, city_id, step) VALUES (?, ?, ?, ?)", 
                     journeyId, userId, cityId, step);
    }

    public static void deleteStepsFrom(String username, int journeyId, int fromStep) throws SQLException {
        ResultSet userResult = executeQuery("SELECT id FROM users WHERE username = ?", username);
        if (!userResult.next()) {
            throw new SQLException("User not found: " + username);
        }
        int userId = userResult.getInt("id");
        
        executeUpdate("DELETE FROM journey WHERE user_id = ? AND journey_id = ? AND step >= ?", 
                     userId, journeyId, fromStep);
    }

    public static int getMaxJourneyId(String username) throws SQLException {
        ResultSet userResult = executeQuery("SELECT id FROM users WHERE username = ?", username);
        if (!userResult.next()) {
            return 0;
        }
        int userId = userResult.getInt("id");
        
        ResultSet journeyResult = executeQuery("SELECT MAX(journey_id) FROM journey WHERE user_id = ?", userId);
        if (journeyResult.next()) {
            return journeyResult.getInt(1);
        }
        return 0;
    }

    public static int getNextJourneyId(String username) throws SQLException {
        return getMaxJourneyId(username) + 1;
    }
    
    public static int getMaxStepInJourney(String username, int journeyId) throws SQLException {
        ResultSet userResult = executeQuery("SELECT id FROM users WHERE username = ?", username);
        if (!userResult.next()) {
            return 0;
        }
        int userId = userResult.getInt("id");
        
        ResultSet stepResult = executeQuery("SELECT MAX(step) FROM journey WHERE user_id = ? AND journey_id = ?", 
                                          userId, journeyId);
        if (stepResult.next()) {
            return stepResult.getInt(1);
        }
        return 0;
    }
    
    public static int getNextStepInJourney(String username, int journeyId) throws SQLException {
        return getMaxStepInJourney(username, journeyId) + 1;
    }
} 