package com.example.jspservlet.models;

public class Route {
    private int id;
    private int startCityId;
    private int finishCityId;

    public Route() {}

    public Route(int startCityId, int finishCityId) {
        this.startCityId = startCityId;
        this.finishCityId = finishCityId;
    }

    public Route(int id, int startCityId, int finishCityId) {
        this.id = id;
        this.startCityId = startCityId;
        this.finishCityId = finishCityId;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getStartCityId() {
        return startCityId;
    }

    public void setStartCityId(int startCityId) {
        this.startCityId = startCityId;
    }

    public int getFinishCityId() {
        return finishCityId;
    }

    public void setFinishCityId(int finishCityId) {
        this.finishCityId = finishCityId;
    }
} 