package com.company.Classes;

import java.util.Random;


public class Obraz {

    private int size_n;
    private int size_m;
    private char[][] tab;
    private int[] histogram;

    public Obraz(int n, int m) {

        this.size_n = n;
        this.size_m = m;
        tab = new char[n][m];

        final Random random = new Random();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                tab[i][j] = (char) (random.nextInt(94) + 33);  // ascii 33-127
                System.out.print(tab[i][j] + " ");
            }
            System.out.print("\n");
        }
        System.out.print("\n\n");

        histogram = new int[94];
        clear_histogram();
    }

    public int getSize_n() {
        return size_n;
    }

    public int[] getHistogram() {
        return histogram;
    }

    public void setHistogram(int[] histogram) {
        this.histogram = histogram;
    }

    public void clear_histogram() {

        for (int i = 0; i < 94; i++) histogram[i] = 0;

    }

    public void calculate_histogram() {

        for (int i = 0; i < size_n; i++) {
            for (int j = 0; j < size_m; j++) {

                for (int k = 0; k < 94; k++) {
                    if (tab[i][j] == (char) (k + 33)) histogram[k]++;
                }

            }
        }
    }

    public void print_histogram() {

        for (int i = 0; i < 94; i++) {
            System.out.print((char) (i + 33) + " " + histogram[i] + "\n");
        }

    }

    public int calculate_search(int num) {
        int result = 0;

        for (int i = 0; i < size_n; i++) {
            for (int j = 0; j < size_m; j++) {

                if (tab[i][j] == (num + 33)) ++result;

            }
        }

        return result;
    }

    public void sign_searching(int i, int iter) {
        System.out.print((char) (i + 33) + " ");

        for (int j = 0; j < iter; ++j) {
            System.out.print("=");
        }
        System.out.print("\n");
    }


    public char[] go_by_row(int first, int last) {
        char[] result = new char[94];

        for (int j = 0; j < last - first; ++j) {
            for (int i = 0; i < size_m; i++) {

                for (int k = 0; k < 94; k++) {
                    if (tab[first+j][i] == (char) (k + 33)) result[k]++;
                }
            }
        }
        return result;
    }
}