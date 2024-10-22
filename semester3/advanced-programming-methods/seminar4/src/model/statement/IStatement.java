package model.statement;

import controller.MyException;
import model.ProgState;

public interface IStatement {
    ProgState execute(ProgState state) throws MyException;
}
