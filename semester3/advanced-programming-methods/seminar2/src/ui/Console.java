package ui;

import model.Bicycle;
import model.Car;
import model.Motorcycle;
import model.Vehicle;
import repository.VechicleExistenceException;
import controller.Controller;

import java.util.Scanner;

public class Console {
    private Controller controller;
    private Scanner scanner;

    public Console(Controller controller) {
        this.controller = controller;
        this.scanner = new Scanner(System.in);
    }

    private void printMenu() {
        System.out.println("0. Exit");
        System.out.println("1. Add vehicle");
        System.out.println("2. Remove vehicle");
        System.out.println("3. Display all vehicles");
        System.out.println("4. Display filtered vehicles");
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
                try {
                    this.controller.addVehicleService(readVehicleInput());
                    System.out.println("Vehicle added.");
                } catch (VechicleExistenceException e) {
                    System.out.println(e.getMessage());
                }
                break;
            case 2:
                try {
                    this.controller.removeVehicleService(readVehicleInput());
                    System.out.println("Vehicle removed.");
                } catch (VechicleExistenceException e) {
                    System.out.println(e.getMessage());
                }
                break;
            case 3:
                this.displayAllVehicles();
                break;
            case 4:
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

        System.out.println("License plate:");
        String licensePlate = scanner.nextLine();

        vehicle = switch (type) {
            case 1 -> new Car(color, licensePlate);
            case 2 -> new Motorcycle(color, licensePlate);
            case 3 -> new Bicycle(color, licensePlate);
            default -> vehicle;
        };

        return vehicle;
    }

    private void displayAllVehicles() {
        Vehicle[] vehicles = this.controller.getAllVehiclesService();
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
        String filterKey;

        System.out.print("Color to filter by: ");
        filterKey = scanner.nextLine();

        Vehicle[] vehicles = this.controller.filter(filterKey);
        if (vehicles.length == 0) {
            System.out.println("No such vehicles found.");
        } else {
            System.out.println("Filtered Vehicles:");
            for (Vehicle vehicle : vehicles) {
                System.out.println(vehicle);
            }
        }
    }
}
