import java.math.BigInteger;
import java.util.Scanner;

public class Main {

    static int N;
    static BigInteger P;

    static BigInteger diff(int k) {
        BigInteger pow = BigInteger.valueOf(k).pow(N);
        return pow.subtract(P).abs();
    }

    static int searchForK(int left, int right) {
        int center = left + (right - left) / 2;

        BigInteger diffCenter = diff(center);

        if (diffCenter.equals(BigInteger.ZERO)) {
            return center;
        }

        BigInteger diffLeft = diff(center - 1);

        if (diffCenter.compareTo(diffLeft) < 0) {
            return searchForK(center + 1, right);
        } else {
            return searchForK(left, center - 1);
        }
    }

    // https://uva.onlinejudge.org/external/1/113.pdf
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNext()) {
            N = sc.nextInt();
            P = new BigInteger(sc.next());

            System.out.println(searchForK(1, 1_000_000_000));
        }

        sc.close();
    }

}
