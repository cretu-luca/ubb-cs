package ui;

import model.Bicycle;
import model.Car;
import model.Motorcycle;
import model.Vehicle;
import service.Service;

import java.util.Scanner;

public class Console {
    private Service service;
    private Scanner scanner;

    public Console(Service service) {
        this.service = service;
        this.scanner = new Scanner(System.in);
    }

    private void printMenu() {
        System.out.println("0. Exit");
        System.out.println("1. Add vehicle");
        System.out.println("2. Display all vehicles");
        System.out.println("3. Display filtered vehicles");
        System.out.print("> ");
    }

    public void run() {
        int option;
        do {
            printMenu();
            try {
                option = Integer.parseInt(scanner.nextLine());
                executeCommand(option);
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please enter a number.");
                option = -1;
            }
        } while(option != 0);
    }

    private void executeCommand(int option) {
        switch (option) {
            case 0:
                System.out.println("Exiting the application.");
                break;
            case 1:
                this.service.addVehicleService(readVehicleInput());
                break;
            case 2:
                this.displayAllVehicles();
                break;
            case 3:
                this.displayFilteredVehicles();
                break;
            default:
                System.out.println("Invalid option. Please try again.");
        }
    }

    private Vehicle readVehicleInput() {
        Vehicle vehicle = null;
        System.out.print("Vehicle Type:\n" +
                         "1. Car\n" +
                         "2. Motorcycle\n" +
                         "3. Bicycle\n");
        int type;
        try {
            type = Integer.parseInt(scanner.nextLine());
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Defaulting to Car.");
            type = 1;
        }

        System.out.println("Color:");
        String color = scanner.nextLine();

        vehicle = switch (type) {
            case 1 -> new Car(color);
            case 2 -> new Motorcycle(color);
            case 3 -> new Bicycle(color);
            default -> vehicle;
        };

        return vehicle;
    }

    private void displayAllVehicles() {
        Vehicle[] vehicles = this.service.getAllVehiclesService();
        if (vehicles.length == 0) {
            System.out.println("No vehicles available.");
        } else {
            System.out.println("All Vehicles:");
            for (Vehicle vehicle : vehicles) {
                System.out.println(vehicle);
            }
        }
    }

    private void displayFilteredVehicles() {
        Vehicle[] vehicles = this.service.filter();
        if (vehicles.length == 0) {
            System.out.println("No red vehicles found.");
        } else {
            System.out.println("Filtered Vehicles (Red Color):");
            for (Vehicle vehicle : vehicles) {
                System.out.println(vehicle);
            }
        }
    }
}
