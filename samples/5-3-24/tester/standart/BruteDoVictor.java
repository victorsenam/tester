public class BruteDoVictor {

    public static void main (String[] args) {
        String pat = StdIn.readString();
        int n = StdIn.readInt();
        StdIn.readChar();

        while (n-- > 0) {
            for (int i : Brute.findAll(StdIn.readString(), pat))
                StdOut.print(i + " ");
            StdOut.println();
        }
    }
}
