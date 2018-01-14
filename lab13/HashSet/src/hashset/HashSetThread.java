package hashset;

import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * Created by Michał on 14.01.2018.
 */
public class HashSetThread implements Runnable {

    private MyHashSet myHashSet;

    public HashSetThread(MyHashSet myHashSet) {
        this.myHashSet = myHashSet;
    }

    @Override
    public void run() {

            Random random = new Random();
            myHashSet.add(random.nextInt(100));
            System.out.println(myHashSet.getToString());

    }

    public static void main(String[] args){

        ExecutorService executorService = Executors.newCachedThreadPool();
        MyHashSet myHashSet = new MyHashSet();
        for (int i = 0; i < 10; i++)
            executorService.execute(new HashSetThread( myHashSet));
        executorService.shutdown();

    }
}
