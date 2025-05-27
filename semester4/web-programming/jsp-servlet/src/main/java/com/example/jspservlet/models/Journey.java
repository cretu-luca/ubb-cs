package com.example.jspservlet.models;

public class Journey {
    private int id;
    private int userId;
    private int cityId;
    private int step;

    public Journey() {}

    public Journey(int userId, int cityId, int step) {
        this.userId = userId;
        this.cityId = cityId;
        this.step = step;
    }

    public Journey(int id, int userId, int cityId, int step) {
        this.id = id;
        this.userId = userId;
        this.cityId = cityId;
        this.step = step;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getUserId() {
        return userId;
    }

    public void setUserId(int userId) {
        this.userId = userId;
    }

    public int getCityId() {
        return cityId;
    }

    public void setCityId(int cityId) {
        this.cityId = cityId;
    }

    public int getStep() {
        return step;
    }

    public void setStep(int step) {
        this.step = step;
    }
} 