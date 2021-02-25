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
        this.tab = new char[n][m];
        Random random = new Random();

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                this.tab[i][j] = (char)(random.nextInt(94) + 33);
                System.out.print(this.tab[i][j] + " ");
            }

            System.out.print("\n");
        }

        System.out.print("\n\n");
        this.histogram = new int[94];
        this.clear_histogram();
    }

    public void clear_histogram() {
        for(int i = 0; i < 94; ++i) {
            this.histogram[i] = 0;
        }

    }

    public void calculate_histogram() {
        for(int i = 0; i < this.size_n; ++i) {
            for(int j = 0; j < this.size_m; ++j) {
                for(int k = 0; k < 94; ++k) {
                    if (this.tab[i][j] == (char)(k + 33)) {
                        int var10002 = this.histogram[k]++;
                    }
                }
            }
        }

    }

    public void print_histogram() {
        for(int i = 0; i < 94; ++i) {
            System.out.print((char)(i + 33) + " " + this.histogram[i] + "\n");
        }

    }

    public int calculate_search(int num) {
        int result = 0;

        for(int i = 0; i < this.size_n; ++i) {
            for(int j = 0; j < this.size_m; ++j) {
                if (this.tab[i][j] == num + 33) {
                    ++result;
                }
            }
        }

        return result;
    }

    public void sign_searching(int i, int iter) {
        System.out.print((char)(i + 33) + " ");

        for(int j = 0; j < iter; ++j) {
            System.out.print("=");
        }

        System.out.print("\n");
    }
}

