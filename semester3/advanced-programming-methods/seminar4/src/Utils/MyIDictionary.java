package Utils;

public interface MyIDictionary<K, V> {
    void put(K key, V value);
    V lookUp(K key);
    boolean isDefined(K key);
}
