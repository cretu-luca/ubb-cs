package controller;

import Utils.MyIStack;
import model.ProgState;
import model.statement.IStatement;
import repository.IRepository;

public class Service {
    private IRepository repository;

    public Service(IRepository repo) {
        this.repository = repo;
    }

    private ProgState oneStep(ProgState state) throws MyException {
        MyIStack<IStatement> execStack = state.getExecStack();
        if(execStack.isEmpty())
            throw new MyException("ProgState Stack is empty!");

        IStatement currentStatement = execStack.pop();
        return currentStatement.execute(state);
    }

    public void allStep(){
        ProgState currentProgram = repository.getCurrentProgram();
        System.out.println(currentProgram);

        while (!currentProgram.getExecStack().isEmpty()){
            oneStep(currentProgram);
            System.out.println(currentProgram);
        }
    }
}
