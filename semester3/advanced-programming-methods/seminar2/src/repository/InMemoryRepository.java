package repository;

import model.Vehicle;

public class InMemoryRepository implements Repository {
    private Vehicle[] vehicles;
    private int size;

    public InMemoryRepository() {
        this.vehicles = new Vehicle[3];
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
        // TODO: repository remove
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
}
