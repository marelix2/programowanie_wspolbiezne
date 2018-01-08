/**
 * Created by Michał on 08.01.2018.
 */
public class ModificateValueVolatile {

    private volatile long value;

    public long getValue() {
        return value;
    }

    public void increaseValue() {
        this.value++;
    }
    public void decreaseValue() {
        this.value--;
    }
}
