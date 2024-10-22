package model.statement;

import controller.MyException;
import model.ProgState;
import model.Type.Type;

public class VarDeclStatement implements IStatement {
    private String id;
    Type type;

    public VarDeclStatement(String id, Type type) {
        this.id = id;
        this.type = type;
    }

    @Override
    public ProgState execute(ProgState state) throws MyException {
        return null;
    }
}
