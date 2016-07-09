import edu.princeton.cs.algs4.StdIn;

public class CorretorDoVictor {

    public static void main (String[] args) {
        List<Integer> ex = new List<Integer>();
        int indexed = 0;
        if (args.length > 0 && args[0].charAt(0) == 'i')
            indexed++;
        int n = StdIn.readInt();

        for (int i = 2; i < n+2; i++) {
            StdIn.readChar();
            char c = StdIn.readChar();
            StdIn.readChar();

            int exs = ex.size();

            if (c == 'a') {
                int a = StdIn.readInt() + indexed;
                int b = StdIn.readInt();
                ex.add(a,b);
                exs++;
            } else if (c == 'd') {
                int a = StdIn.readInt() + indexed;
                StdOut.print(ex.delete(a));
                exs--;
            } else if (c == 'g') {
                int a = StdIn.readInt() + indexed;
                StdOut.print(ex.get(a));
            } else if (c == 'f') {
                int a = StdIn.readInt();
                ex.addFront(a);
                exs++;
            } else if (c == 'b') {
                int a = StdIn.readInt();
                ex.addBack(a);
                exs++;
            } else if (c == 'F') {
                StdOut.print(ex.deleteFront());
                exs--;
            } else if (c == 'B') {
                StdOut.print(ex.deleteBack());
                exs--;
            } else if (c == 's') {
                StdOut.print(ex.size());
            } else if (c == 'e') {
                StdOut.print(ex.isEmpty());
            } else if (c == 'c') {
                int a = StdIn.readInt();
                StdOut.print(ex.contains(a));
            } else if (c == 'D') {
                Integer a = StdIn.readInt();
                ex.delete(a);
                exs--;
            } else if (c == 'i') {
                //StdOut.print("|");
                boolean ok = false;
                for (Integer el : ex) {
                    if (ok)
                        StdOut.print(" ");
                    ok = true;
                    StdOut.print(el);
                }
            }

            StdOut.println(" " + i + " " + ex.size());
        }
    }
}
