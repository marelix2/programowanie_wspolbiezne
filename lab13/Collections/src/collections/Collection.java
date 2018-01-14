package collections;

import java.util.Collections;
import java.util.HashSet;
import java.util.Random;
import java.util.Set;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * Created by Michał on 14.01.2018.
 */
public class Collection implements Runnable{

    private int nr;
    private Set<Integer> hashSet;
    Random random;


    public Collection(int nr, Set<Integer> myHashSet) {
        this.hashSet = myHashSet;
        random = new Random();
    }

    @Override
    public void run() {

        hashSet.add(random.nextInt(10));
        System.out.println(hashSet);

    }

    public static void main(String[] args) {
        ExecutorService executorService = Executors.newCachedThreadPool();
        Set<Integer> set = Collections.synchronizedSet(new HashSet<Integer>());
        for (int i = 0; i < 10; i++)
            executorService.execute(new Collection(i,
                    set));
        executorService.shutdown();
    }
}
