import java.util.*;

class Solution {

    public int maxDistance(int side, int[][] points, int k) {
        List<Long> arr = new ArrayList<>();

        for (int[] p : points) {
            int x = p[0];
            int y = p[1];

            if (x == 0) {
                arr.add((long) y);
            } else if (y == side) {
                arr.add((long) side + x);
            } else if (x == side) {
                arr.add(3L * side - y);
            } else {
                arr.add(4L * side - x);
            }
        }

        Collections.sort(arr);

        long low = 1, high = side;
        int ans = 0;

        while (low <= high) {
            long mid = (low + high) / 2;

            if (check(arr, side, k, mid)) {
                ans = (int) mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }

    private boolean check(List<Long> arr, int side, int k, long dist) {
        long perimeter = 4L * side;

        for (long start : arr) {
            long end = start + perimeter - dist;
            long cur = start;

            for (int i = 0; i < k - 1; i++) {
                int idx = lowerBound(arr, cur + dist);

                if (idx == arr.size() || arr.get(idx) > end) {
                    cur = -1;
                    break;
                }

                cur = arr.get(idx);
            }

            if (cur != -1) return true;
        }

        return false;
    }

    private int lowerBound(List<Long> arr, long target) {
        int left = 0, right = arr.size();

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (arr.get(mid) < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;
    }
}