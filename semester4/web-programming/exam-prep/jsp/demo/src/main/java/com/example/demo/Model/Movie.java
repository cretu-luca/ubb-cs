package com.example.demo.Model;

public class Movie {
    private int id;
    private String title;
    private int duration;

    public Movie(int id, String title, int duration) {
        this.id = id;
        this.title = title;
        this.duration = duration;
    }

    public int getId() { return id; }
    public String getTitle() { return title; }
    public int getDuration() { return duration; }
}