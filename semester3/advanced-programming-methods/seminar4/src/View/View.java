package View;

import Utils.*;
import controller.Service;
import model.ProgState;
import model.statement.CompStatement;
import model.statement.IStatement;
import model.value.Value;
import repository.IRepository;
import repository.Repository;

public class View {
    public static void main(String[] args) {

        // int v;
        // print(v);
        IStatement ex1= new CompStatement(new VarDeclStmt("v",new IntType()),
                        new PrintStmt(new VarExp("v")));

        MyIStack<IStatement> stack = new MyStack<>();
        MyIDictionary<String, Value> symT = new MyDictionary<>();
        MyIList<Value> out = new MyList<>();

        ProgState progState = new ProgState(stack, symT, out, ex1);

        IRepository repo = new Repository();
        repo.add(progState);
        Service serv = new Service(repo);
        serv.allStep();
    }
}
