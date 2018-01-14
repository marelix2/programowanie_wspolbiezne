package Package;

import java.util.Random;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.TimeUnit;

/**
 * Created by Michał on 14.01.2018.
 */
public class InhabitantThread implements Runnable {
    private BlockingQueue<Message> blockingQueue;
    Random random = new Random();
    private int nr;
    public InhabitantThread(int nr,BlockingQueue<Message> blockingQueue) {
        this.nr=nr;
        this.blockingQueue = blockingQueue;
    }

    @Override
    public void run() {
        while (true) {
            float probability = Configuration.getProbabilityoffailure();
            int maxValue = 10 / Math.round(probability * 10);




            int loosedValue = random.nextInt(maxValue);
            if (loosedValue == 0)
                try {
                    String description="Cos nie tak u mieszkanca "+nr;
                    blockingQueue.put(new Message(description));
                    System.out.println("Mieszkaniec "+nr+" zglaszam awarie");
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            try {
                TimeUnit.SECONDS.sleep(Configuration.getInhibitanttimesleep());
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
