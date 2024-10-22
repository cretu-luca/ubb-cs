package model.statement;

import Utils.MyIStack;
import controller.MyException;
import model.ProgState;

public class CompStatement implements IStatement {
    IStatement first, second;

    public CompStatement(IStatement first, IStatement second) {
        this.first = first;
        this.second = second;
    }

    @Override
    public ProgState execute(ProgState state) throws MyException {
        MyIStack<IStatement> execStack = state.getExecStack();

        execStack.push(second);
        execStack.push(first);

        return state;
    }
}
