package model;

public class Motorcycle implements Vehicle {
    String color;

    public Motorcycle(String color) {
        this.color = color;
    }

    @Override
    public String getColor() {
        return color;
    }

    @Override
    public String getModel() {
        return "Motorcycle";
    }

    @Override
    public String toString() {
        return "Motorcycle {color='" + color + "'}";
    }
}
