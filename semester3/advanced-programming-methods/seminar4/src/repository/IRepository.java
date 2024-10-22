package repository;

import model.ProgState;

public interface IRepository {
    ProgState getCurrentProgram();

    void add(ProgState s);
}
