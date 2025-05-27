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

    public static void close(ResultSet resultSet, PreparedStatement statement, Connection connection) {
        try {
            if (resultSet != null) resultSet.close();
            if (statement != null) statement.close();
            if (connection != null) connection.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
} 