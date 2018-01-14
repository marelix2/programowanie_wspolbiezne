import java.util.Random;
import java.util.concurrent.CopyOnWriteArraySet;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * Created by Michał on 14.01.2018.
 */
class TCopyOnWriteArraySet  implements Runnable{

    CopyOnWriteArraySet<Integer> copyOnWriteArraySet;
    Random random = new Random();

    public TCopyOnWriteArraySet(CopyOnWriteArraySet<Integer> copyOnWriteArraySet) {

        this.copyOnWriteArraySet = copyOnWriteArraySet;
    }

    @Override
    public void run() {


            int newValue = random.nextInt(10);
            copyOnWriteArraySet.add(newValue);
            System.out.println(copyOnWriteArraySet);

    }

    public static void main(String[] args) {
        ExecutorService executorService = Executors.newCachedThreadPool();
        CopyOnWriteArraySet<Integer> copyOnWriteArraySet= new CopyOnWriteArraySet<Integer>();
        for (int i = 0; i < 10; i++)
            executorService.execute(new TCopyOnWriteArraySet(copyOnWriteArraySet));
        executorService.shutdown();
    }
}
