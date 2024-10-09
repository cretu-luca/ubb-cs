package model;

public class Motorcycle implements Vehicle {
    String color;
    String licensePlate;

    public Motorcycle(String color, String licensePlate) {
        this.color = color;
        this.licensePlate = licensePlate;
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
    public String getLicensePlate() {
        return this.licensePlate;
    }

    @Override
    public String toString() {
        return "Model: " + this.getModel() + "\n" +
               "License plate: " + this.getLicensePlate() + "\n" +
               "Color: " + this.getColor() + "\n\n";
    }
}
