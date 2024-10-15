package model;

import java.util.Objects;

public class Car implements Vehicle {
    String color;
    String licensePlate;

    public Car(String color, String LicensePlate) {
        this.color = color;
        this.licensePlate = LicensePlate;
    }

    @Override
    public String getColor() {
        return color;
    }

    @Override
    public String getModel() {
        return "Car";
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

    @Override
    public boolean equals(Vehicle vehicle) {
        // down-casting
        // Vehicle vehicle = (Vehicle) obj;
        return Objects.equals(this.color, vehicle.getColor()) &&
                Objects.equals(this.licensePlate, vehicle.getLicensePlate()) &&
                Objects.equals(vehicle.getModel(), "Car");
    }
}
