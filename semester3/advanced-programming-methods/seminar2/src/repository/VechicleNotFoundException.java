package repository;

public class VechicleNotFoundException extends RuntimeException {
    public VechicleNotFoundException(String message) {
        super(message);
    }
}
