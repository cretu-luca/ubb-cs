package com.example.demo5;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

@WebServlet("/notification-stream")
public class NotificationServlet extends HttpServlet {
    private static final List<PrintWriter> clients = new CopyOnWriteArrayList<>();
    private static final List<String> recentNotifications = new ArrayList<>();
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/event-stream");
        response.setCharacterEncoding("UTF-8");
        response.setHeader("Cache-Control", "no-cache");
        response.setHeader("Connection", "keep-alive");
        
        PrintWriter writer = response.getWriter();
        clients.add(writer);
        
        for (String notification : recentNotifications) {
            writer.write("data: " + notification + "\n\n");
            writer.flush();
        }
        
        try {
            while (!writer.checkError()) {
                Thread.sleep(1000);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            clients.remove(writer);
        }
    }
    
    public static void sendNotification(String message) {
        if (recentNotifications.size() >= 10) {
            recentNotifications.remove(0);
        }
        recentNotifications.add(message);
        
        for (PrintWriter client : clients) {
            try {
                client.write("data: " + message + "\n\n");
                client.flush();
            } catch (Exception e) {
                clients.remove(client);
            }
        }
    }
} 