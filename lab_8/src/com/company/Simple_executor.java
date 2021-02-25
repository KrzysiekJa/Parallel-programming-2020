package com.company;

import com.company.Classes.Calka_callable;
import com.company.java_executor_test.Counter;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;

public class Simple_executor {

    private static final int NTHREADS = 4;


    public static void main(String[] args) {

        Counter counter = new Counter();
        ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);
        List<Future<Double>> list = new ArrayList<>();
        double integralSum = 0.0, iter = 0.0;
        int iterNum = 50;

        for (int i = 0; i < iterNum; i++) {
            Callable<Double> worker = new Calka_callable((iter / iterNum) * Math.PI, ((iter + 1) / iterNum) * Math.PI, 0.01);
            Future<Double> future = executor.submit(worker);
            list.add(future);
            iter += 1;
            try{
                Thread.sleep(1);
            }catch (InterruptedException exception){
                System.err.println("ERROR: " + exception);
            }
        }

        for(Future<Double> future : list) {
            try {
                integralSum += future.get();
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
        }


        // This will make the executor accept no new threads
        // and finish all existing threads in the queue
        executor.shutdown();

        // Wait until all threads finish
        while (!executor.isTerminated()) {
        }

        System.out.println("\n\nFinal result of integration: " + integralSum);
        System.out.println("Finished all threads");
        System.out.format("\nCounter_1: %d, Counter_2: %d\n\n", counter.get_c1(), counter.get_c2());
    }
} 
