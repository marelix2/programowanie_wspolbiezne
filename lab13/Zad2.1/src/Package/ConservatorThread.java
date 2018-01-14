package Package;

import java.util.Random;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.TimeUnit;

/**
 * Created by Michał on 14.01.2018.
 */
public class ConservatorThread implements Runnable {
    private BlockingQueue<Message> blockingQueue;
    Random random = new Random();

    public ConservatorThread(BlockingQueue<Message> blockingQueue) {
        this.blockingQueue = blockingQueue;
    }

    @Override
    public void run() {
        while (true) {

            try {
                Message message = blockingQueue.take();
                System.out.println("Otrzymalem zgloszenie awari - " + message);
                try {
                    TimeUnit.SECONDS.sleep(random.nextInt(Configuration.getMaxrepairtime()));
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.println("Naprawilem awarie - " + message);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        }

    }

}
