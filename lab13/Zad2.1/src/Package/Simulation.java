package Package;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * Created by Michał on 14.01.2018.
 */
public class Simulation {

    public static void main(String[] args) {

        BlockingQueue<Message> blockingQueue = new ArrayBlockingQueue<Message>(1024);
        ExecutorService executorService = Executors.newCachedThreadPool();
        executorService.execute(new ConservatorThread(blockingQueue));
        for (int i=0;i<Configuration.getInhibitantnumber();i++)
            executorService.execute(new InhabitantThread(i,blockingQueue));
        executorService.shutdown();

    }
}
