package service;

import model.Vehicle;
import repository.CapacityExceededException;
import repository.Repository;

public class Service {
    private Repository repository;

    public Service(Repository repository) {
        this.repository = repository;
    }

    public void addVehicleService(Vehicle vehicle) {
        try {
            this.repository.add(vehicle);
        } catch (CapacityExceededException e) {
            System.out.println(e.getMessage());
        }
    }

    public Vehicle[] filter() {
        Vehicle[] allVehicles = this.repository.getAll();
        Vehicle[] tempFilteredVehicles = new Vehicle[allVehicles.length];

        int filteredSize = 0;
        for(Vehicle vehicle : allVehicles) {
            if("red".equalsIgnoreCase(vehicle.getColor())) {
                tempFilteredVehicles[filteredSize++] = vehicle;
            }
        }

        Vehicle[] filteredVehicles = new Vehicle[filteredSize];
        System.arraycopy(tempFilteredVehicles, 0, filteredVehicles, 0, filteredSize);

        return filteredVehicles;
    }

    public Vehicle[] getAllVehiclesService() {
        return this.repository.getAll();
    }
}
