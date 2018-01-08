import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * Created by Michał on 08.01.2018.
 */
public class ModificateThreadVolatile implements Runnable {
    private String name;



    static ModificateValueVolatile value = new ModificateValueVolatile();


    public ModificateThreadVolatile(String name) {
        this.name=name;
    }
    public void run() {

        for (int i=0;i<10;i++){
            value.increaseValue();
            System.out.println(name+":"+value.getValue() + " iteracja: "+ i);
            value.decreaseValue();

            System.out.println(name+":"+value.getValue()+ " iteracja: "+ i);
        }
    }
    public static void main(String[] args) {
        ExecutorService executor= Executors.newCachedThreadPool();
        executor.execute(new ModificateThreadVolatile("Watek 1"));
        executor.execute(new ModificateThreadVolatile("Watek 2"));
    }
}
