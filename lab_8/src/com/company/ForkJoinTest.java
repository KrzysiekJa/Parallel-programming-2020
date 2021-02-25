package com.company;

import com.company.Classes.DivideTask;

import java.util.Arrays;
import java.util.Random;
import java.util.concurrent.ForkJoinPool;

public class ForkJoinTest {

    public static void main(String[] args) {

        int[] randomTab = new int[30];
        Random generator = new Random();

        for (int i = 0; i < randomTab.length - 1; ++i) {
            randomTab[i] = generator.nextInt();
        }


        DivideTask task = new DivideTask(randomTab);
        ForkJoinPool forkJoinPool = new ForkJoinPool();

        randomTab = forkJoinPool.invoke(task);
        System.out.println("Sorted array: " + Arrays.toString(randomTab));
    }
}
