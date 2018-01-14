package ConcurrentSkipListSet;

import java.util.Random;
import java.util.concurrent.ConcurrentSkipListSet;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * Created by Michał on 14.01.2018.
 */
class TConcurrentSkipListSet implements Runnable{


    ConcurrentSkipListSet<Integer> concurrentSkipListSet;
    Random random = new Random();

    public TConcurrentSkipListSet(ConcurrentSkipListSet<Integer> concurrentSkipListSet) {
        this.concurrentSkipListSet = concurrentSkipListSet;

    }

    @Override
    public void run() {

            int newValue = random.nextInt(10);
            concurrentSkipListSet.add(newValue);
            System.out.println(concurrentSkipListSet);

    }

    public static void main(String[] args) {
        ExecutorService executorService = Executors.newCachedThreadPool();
        ConcurrentSkipListSet<Integer> concurrentSkipListSet= new ConcurrentSkipListSet<Integer>();
        for (int i = 0; i < 10; i++)
            executorService.execute(new TConcurrentSkipListSet(
                    concurrentSkipListSet));
        executorService.shutdown();
    }
}
