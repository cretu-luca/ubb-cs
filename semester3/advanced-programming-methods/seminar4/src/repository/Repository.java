package repository;

import model.ProgState;

import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository{
    private List<ProgState> repository;

    public Repository() {
        this.repository = new ArrayList<>();
    }

    @Override
    public ProgState getCurrentProgram() {
        return this.repository.getFirst();
    }

    @Override
    public void add(ProgState s) {
        this.repository.add(s);
    }

}
