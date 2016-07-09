public class CorretorDoVictor {

    public static void main (String[] args) {
        TrieST<Integer> ex = new TrieST<Integer>();
        int indexed = 0;
        if (args.length > 0 && args[0].charAt(0) == '1')
            indexed++;
        int n = StdIn.readInt();

        for (int i = 2; i < n+2; i++) {
            StdIn.readChar();
            char c = StdIn.readChar();
            StdIn.readChar();

            String res = "nao imprimir esta linha";

            if (c == 'a') {
                ex.put(StdIn.readString(), i);
            } else if (c == 'r') {
                try {
                    res = (ex.rank(StdIn.readString()) - indexed) + "";
                } catch (Throwable e) {
                    res = "erro de execucao";
                }
            } else if (c == 'f') {
                try {
                    res = ex.floor(StdIn.readString());
                } catch (Throwable e) {
                    res = "erro de execucao";
                }
            } else if (c == 'c') {
                try {
                    res = ex.ceil(StdIn.readString());
                } catch (Throwable e) {
                    res = "erro de execucao";
                }
            } else if (c == 's') {
                try {
                    res = ex.select(StdIn.readInt() + indexed);
                } catch (Throwable e) {
                    res = "erro de execucao";
                }
            }

            if (res != "nao imprimir esta linha")
                StdOut.println(res);
        }
    }
}
