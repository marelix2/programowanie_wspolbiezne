/**
 * Created by Michał on 08.01.2018.
 */
public class ModificateValueSynMethod {

    private long value;

    public synchronized long getValue() {

        return value;


    }

    public synchronized void increaseValue() {

        this.value++;

    }

    public synchronized void decreaseValue() {

        this.value--;

    }
}
