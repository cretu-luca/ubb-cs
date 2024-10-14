package repository;

import model.Vehicle;

public class InMemoryRepository implements Repository {
    private Vehicle[] vehicles;
    private int size;

    public InMemoryRepository() {
        this.vehicles = new Vehicle[5];
        this.size = 0;
    }

    @Override
    public void add(Vehicle vehicle) {
        if (this.size == this.vehicles.length) {
            /*
                Vehicle[] newVehicles = new Vehicle[this.vehicles.length * 2];
                System.arraycopy(this.vehicles, 0, newVehicles, 0, this.vehicles.length);
                this.vehicles = newVehicles;
             */
            throw new CapacityExceededException("Capacity exceeded.");
        }
        this.vehicles[this.size++] = vehicle;
    }

    @Override
    public void remove(Vehicle vehicle) {
        for (int i = 0; i < size; i++) {
            if (this.vehicles[i].equals(vehicle)) {
                for (int j = i; j < size - 1; j++) {
                    this.vehicles[j] = this.vehicles[j + 1];
                }

                this.vehicles[size - 1] = null;
                size--;
            }
        }
    }

    @Override
    public Vehicle[] getAll() {
        Vehicle[] result = new Vehicle[this.size];
        System.arraycopy(this.vehicles, 0, result, 0, this.size);
        return result;
    }

    @Override
    public int getSize() {
        return this.size;
    }

    @Override
    public boolean exists(Vehicle vehicle) {
        for (int i = 0; i < size; i++) {
            if (this.vehicles[i].equals(vehicle))
                return true;
        }

        return false;
    }
}
