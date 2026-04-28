class Solution {
    public int minOperations(int[][] grid, int x) {
        int m = grid.length;
        int n = grid[0].length;

        int[] arr = new int[m * n];
        int k = 0;

        for (int[] row : grid) {
            for (int num : row) {
                arr[k++] = num;
            }
        }

        int rem = arr[0] % x;

        for (int num : arr) {
            if (num % x != rem) return -1;
        }

        Arrays.sort(arr);

        int median = arr[arr.length / 2];
        int operations = 0;

        for (int num : arr) {
            operations += Math.abs(num - median) / x;
        }

        return operations;
    }
}