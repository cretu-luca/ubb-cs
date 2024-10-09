package model;

public class Bicycle implements Vehicle {
    String color;
    String licencePlate;

    public Bicycle(String color, String licencePlate) {
        this.color = color;
        this.licencePlate = licencePlate;
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
    public String getLicensePlate() {
        return this.licencePlate;
    }

    @Override
    public String toString() {
        return "Model: " + this.getModel() + "\n" +
                "License plate: " + this.getLicensePlate() + "\n" +
                "Color: " + this.getColor() + "\n\n";
    }
}
