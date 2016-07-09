import edu.princeton.cs.algs4.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.function.Function;
import java.io.*;
import java.nio.file.*;

public class CorretorDoVictaum {
    private static class ArgsPasser {
        public int siz;
        public String a, b;
        public WordDAG ex;
        public Out exOut;
        public In answer;
        public Path file;
        public boolean tl;

        ArgsPasser () { }
    }

    public static String getStackTrace(Throwable t) {
        StringWriter sw = new StringWriter();
        t.printStackTrace(new PrintWriter(sw));
        return sw.toString();
    }

    public static int test(String nome, Function<ArgsPasser, Throwable> runner, long timeout, ArgsPasser args, int i, boolean keeptl) {
        String casename = String.format("%03d", i) + "_" + args.file.getFileName().toString().replace(".", "_");
        args.exOut = new Out("saida.txt");
        
        Callable<Throwable> task = ()-> (Throwable)runner.apply(args);
        ExecutorService executor = Executors.newFixedThreadPool(1);
        Future<Throwable> future = executor.submit(task);

        try {
            Throwable ret = null;
            ret = future.get(timeout, TimeUnit.MILLISECONDS);

            if (ret != null) {
                throw ret;
            }
            System.err.print(".");
        } catch (UnsupportedOperationException e) {
            args.exOut.println("FALHA NA MONTAGEM");
            System.err.print("M");
        } catch (TimeoutException e) {
            args.exOut.println("TEMPO DE EXECUCAO EXCEDIDO");
            System.err.print("T");
        } catch (Throwable e) {
            args.exOut.println("ERRO DE EXECUCAO");
            System.err.print("R");
            while (e.getCause() != null)
                e = e.getCause();
            System.out.println(getStackTrace(e));
        } finally {
            executor.shutdownNow();
            if (!executor.isShutdown())
                System.err.println("NOT SHUT DOWN");
        }
        System.out.println("----------");

        return 0;
    }

    public static Throwable mountGraph(ArgsPasser args) {
        args.tl = true;
        In in = new In(args.file.toString());
        String[] strings = new String[args.siz];

        for (int i = 0; i < args.siz; i++)
            strings[i] = in.readLine();

        try {
            args.ex = new WordDAG(strings);
        } catch (Throwable e) {
            return e;
        }
        args.tl = false;

        try {
            args.ex.PrintDag();
        } catch (Throwable e) {
            return e;
        }
        return null;
    }

    public static Throwable printPathCount(ArgsPasser args)  {
        if (args.tl == true) {
            return new UnsupportedOperationException();
        }
        try {
            args.ex.PrintPathCount(args.a, args.b);
        } catch (Throwable e) {
            return e;
        }
        return null;
    }

    public static void main(String args[]) {
        int nota = 10000;
        long stdTime = 1000;

        ArgsPasser env = new ArgsPasser();
        env.tl = false;
        try {
            env.exOut = new Out("saida.txt");
        } catch (Exception e) {
            System.err.println("This failed!");
            return;
        }

        int n = StdIn.readInt();
        int stdDiscount = nota/n;
        
        for (int i = 0; i < n; i++) {
            String command = StdIn.readString();
            if (command.equals("mount")) {
                env.file = Paths.get(StdIn.readString());
                env.siz = StdIn.readInt();
                nota -= test("Monta o grafo num tempo razoável", CorretorDoVictaum::mountGraph, 90000, env, i, true);
            } else if (command.equals("count")) {
                env.a = StdIn.readString();
                env.b = StdIn.readString();
                nota -= test("Conta caminho corretamente", CorretorDoVictaum::printPathCount, 3000, env, i, false);
            }
        }
        System.err.println("");

        System.exit(0);
    }
}
