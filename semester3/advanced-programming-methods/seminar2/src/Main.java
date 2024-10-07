import ui.Console;
import repository.InMemoryRepository;
import service.Service;

public class Main {
    public static void main(String[] args) {
        InMemoryRepository repository = new InMemoryRepository();
        Service service = new Service(repository);
        Console console = new Console(service);
        console.run();
    }
}
