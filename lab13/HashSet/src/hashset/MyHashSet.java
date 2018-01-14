package hashset;

import java.util.HashSet;

/**
 * Created by Michał on 14.01.2018.
 */
public class MyHashSet {

    private HashSet<Integer> hashSet = new HashSet<Integer>();


    public synchronized void add(Integer arg){
        hashSet.add(arg);
        System.out.println("Dodaje: "+arg);
    }

    public synchronized String getToString(){
        return hashSet.toString();
    }
}
