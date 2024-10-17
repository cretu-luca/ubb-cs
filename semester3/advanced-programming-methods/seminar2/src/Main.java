import ui.Console;
import repository.InMemoryRepository;
import controller.Controller;

public class Main {
    public static void main(String[] args) {
        InMemoryRepository repository = new InMemoryRepository();
        Controller controller = new Controller(repository);
        Console console = new Console(controller);
        console.run();
    }
}
