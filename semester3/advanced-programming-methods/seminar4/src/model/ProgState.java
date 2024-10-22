package model;

import Utils.MyIDictionary;
import Utils.MyIList;
import Utils.MyIStack;
import model.statement.IStatement;
import model.value.Value;

public class ProgState {
    private MyIDictionary<String, Value> symbolTable;
    private MyIStack<IStatement> execStack;
    private MyIList<Value> output;

    private IStatement originalProgram;

    public MyIDictionary<String, Value> getSymbolTable() {
        return symbolTable;
    }

    public MyIStack<IStatement> getExecStack() {
        return execStack;
    }

    public MyIList<Value> getOutput() {
        return output;
    }

    public ProgState(MyIStack<IStatement> execStack, MyIDictionary<String, Value> symbolTable, MyIList<Value> output, IStatement program) {
        this.execStack = execStack;
        this.symbolTable = symbolTable;
        this.output = output;
        this.originalProgram = program;

        this.execStack.push(program);
    }

    @Override
    public String toString() {
        return "ExeStack: " + this.execStack.toString() + "\nSymTable: " + this.symbolTable.toString() + "\nOutput: " + this.output.toString();
    }

}
