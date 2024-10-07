package model;

public class Bicycle implements Vehicle {
    String color;

    public Bicycle(String color) {
        this.color = color;
    }

    @Override
    public String getColor() {
        return color;
    }

    @Override
    public String getModel() {
        return "Bicycle";
    }

    @Override
    public String toString() {
        return "Motorcycle{color='" + color + "'}";
    }
}
