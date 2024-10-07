/*
1. Intr-o parcare exista masini, motociclete
        si biciclete. Sa se afiseze toate vehiculele
        de culoare rosie.

 */

package repository;

import model.Vehicle;

public interface Repository {
    public void add(Vehicle vehicle) throws CapacityExceededException;
    public void remove(Vehicle vehicle);
    public Vehicle[] getAll();
    public int getSize();
}
