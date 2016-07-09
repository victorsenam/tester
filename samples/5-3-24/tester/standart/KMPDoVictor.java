public class KMPDoVictor {

    public static void main (String[] args) {
        KMP ex = new KMP(StdIn.readString());

        int n = StdIn.readInt();
        StdIn.readChar();

        while (n-- > 0) {
            for (int i : ex.findAll(StdIn.readString()))
                StdOut.print(i + " ");
            StdOut.println();
        }
    }
}
