import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import java.util.function.Function;
import java.io.*;

public class Tester {
    public static /* varargs */ int test(int discount, String nome, Function<Integer[], String> runner, long timeout, int repetitions, Integer ... args) {
        StdOut.println(nome);
        
        Callable<String> task = () -> (String)runner.apply(args);
        ExecutorService executor = Executors.newFixedThreadPool(1);

        try {
            String res = "";
            while (repetitions > 0 && res == "") {
                Future<String> future = executor.submit(task);
                res = future.get(timeout, TimeUnit.MILLISECONDS);
                --repetitions;
            }
            if (res == "") {
                StdOut.println("OK :)");
                discount = 0;
            } else {
                StdOut.print("[-" + (double)discount/100. + "] ");
                StdOut.println(res);
            }
        } catch (TimeoutException e) {
            StdOut.print("[-" + (double)discount/100. + "] ");
            StdOut.println("TEMPO DE EXECUÇÃO EXCEDIDO");
        } catch (Throwable e) {
            StdOut.print("[-" + (double)discount/100. + "] ");
            StdOut.println("ERRO DE EXECUÇÃO");
            while (e.getCause() != null)
                e = e.getCause();
            e.printStackTrace();
        } finally {
            executor.shutdownNow();
            if (!executor.isShutdown())
                StdOut.println("NOT SHUT DOWN");

            StdOut.println("---------------");
            return discount;
        }
    }

    public static /* varargs */ String independentQueues(Integer ... args) {
        Integer siz = args[0];
        RandomQueue<Integer> first = new RandomQueue<Integer>();
        RandomQueue<Integer> second = new RandomQueue<Integer>();
        for (int i = 0; i < siz; ++i) {
            first.enqueue(i);
            second.enqueue(i);
        }
        while (!first.isEmpty()) {
            if (first.dequeue() == second.dequeue()) continue;
            return "";
        }
        return "Filas independentes ficam iguais";
    }

    private static /* varargs */ String repetitions(Integer ... args) {
        Integer siz = args[0];
        RandomQueue<Integer> queue = new RandomQueue<Integer>();
        boolean[] visited = new boolean[siz.intValue()];
        for (int i = 0; i < siz; ++i) {
            queue.enqueue(i);
            visited[i] = false;
        }
        while (!queue.isEmpty()) {
            int rm = (Integer)queue.dequeue();
            if (rm < 0 || rm >= siz) {
                return "Valor n\u00e3o inserido retornado";
            }
            if (visited[rm]) {
                return "Repeti\u00e7\u00e3o de valor retornado";
            }
            visited[rm] = true;
        }
        return "";
    }

    public static /* varargs */ String distribution(Integer ... args) {
        Integer siz = args[0];
        Integer lim = args[1];
        RandomQueue<Integer> queue = new RandomQueue<Integer>();
        Integer fat = 0;
        for (int i = 0; i < siz; ++i) {
            fat = fat + (i + 1);
        }
        Integer tableSiz = 1;
        for (int i2 = 0; i2 < siz; ++i2) {
            tableSiz = tableSiz * siz;
        }
        boolean[] visited = new boolean[tableSiz.intValue()];
        int visiCount = 0;
        for (int i3 = 0; i3 < lim && visiCount < fat; ++i3) {
            for (int j = 0; j < siz; ++j) {
                queue.enqueue(j);
            }
            int pot = 1;
            int val = 0;
            for (int j2 = 0; j2 < siz; ++j2) {
                val += pot * (Integer)queue.dequeue();
                pot *= siz.intValue();
            }
            if (visited[val]) continue;
            visited[val] = true;
            ++visiCount;
        }
        if (visiCount == fat) {
            return "";
        }
        return "Distribui\u00e7\u00e3o Enviesada";
    }

    public static /* varargs */ String bigCase(Integer ... args) {
        int i;
        Integer siz = args[0];
        RandomQueue<Integer> queue = new RandomQueue<Integer>();
        for (i = 0; i < siz; ++i) {
            queue.enqueue(i);
        }
        for (i = 0; i < siz; ++i) {
            queue.dequeue();
        }
        return "";
    }

    public static /* varargs */ String dynamic(Integer ... args) {
        Integer siz = args[0];
        RandomQueue<Integer> queue = new RandomQueue<Integer>();
        while (siz > 0) {
            int op = StdRandom.uniform((int)1);
            if (queue.isEmpty()) {
                op = 0;
            }
            if (op == 0) {
                queue.enqueue(StdRandom.uniform((int)100000));
            } else {
                queue.dequeue();
            }
            Integer n = siz;
            Integer n2 = siz = Integer.valueOf(siz - 1);
        }
        return "";
    }

    public static /* varargs */ String specification(Integer ... args) {
        RandomQueue<Integer> queue = new RandomQueue<Integer>();
        if (queue.isEmpty()) {
            queue.enqueue(10);
        }
        int val = (Integer)queue.sample();
        val = (Integer)queue.dequeue();
        queue.enqueue(val);
        return "";
    }

    public static /* varargs */ String sampling(Integer ... args) {
        RandomQueue<Integer> queue = new RandomQueue<Integer>();
        queue.enqueue(1);
        int ret = (Integer)queue.sample();
        if (ret != 1) {
            return "Sample retorna um elemento fora da fila";
        }
        if (queue.isEmpty()) {
            return "Sample remove elemento da fila";
        }
        return "";
    }

    public static /* varargs */ String stringTest(Integer ... args) {
        RandomQueue<String> queue = new RandomQueue<String>();
        queue.enqueue("A string");
        String res = (String)queue.dequeue();
        if (res != "A string") {
            return "A fila funciona mal com strings";
        }
        queue.enqueue("Another String");
        return "";
    }

    public static String bridgeValid(Integer ... args) {
        try {
            Process p = Runtime.getRuntime().exec("java-algs4 Bridge");
            p.waitFor();

            BufferedReader b = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String lines[] = new String[20];
            int i = 0;

            while (i < 20 && (lines[i] = b.readLine()) != null) {
                int cnt = 0;
                char[] c = new char[2];
                c[0] = lines[i].charAt(0);
                c[1] = lines[i].charAt(1);
                if ( ((c[0] < '0' || c[0] > '9') && (c[0] != 'J') && (c[0] != 'Q') && (c[0] != 'K') && (c[0] != 'A') && (c[0] != 'T')) ||
                     ( c[1] != 'S' && c[1] != 'C' && c[1] != 'D' && c[1] != 'H') )
                    return "Carta inválida: " + lines[i];
                i++;
            }
            if (i != 13)
                return "Não imprimiu 13 cartas";

            b.close();
        } catch (IOException | InterruptedException e) {
            return "Erro do Testador (se receber, reclame com o monitor)";
        }
        return "";
    }

    public static String bridgeRepeat(Integer ... args) {
        try {
            Process p = Runtime.getRuntime().exec("java-algs4 Bridge");
            p.waitFor();

            BufferedReader b = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String lines[] = new String[20];
            int i = 0;

            while (i < 20 && (lines[i] = b.readLine()) != null) {
                int cnt = 0;
                for (int j = 0; j < i; j++) {
                    if (lines[i].charAt(0) == lines[j].charAt(0) && lines[i].charAt(1) == lines[j].charAt(1)) {
                        cnt++;
                    }
                }

                if (cnt >= 2)
                    return "A carta " + lines[i] + " aparece mais de duas vezes";
                i++;
            }

            if (i != 13)
                return "Não imprimiu 13 cartas";

            b.close();
        } catch (IOException | InterruptedException e) {
            return "Erro do Testador (se receber, reclame com o monitor)";
        }
        return "";
    }

    public static void main(String[] args) {
        int nota = 10000;
        long stdTime = 1000;
        int stdDiscount = 1000;
        nota -= Tester.test(stdDiscount, "Duas filas independentes têm grande chance de gerar permutações diferentes quando alimentadas com a mesma entrada", Tester::independentQueues, stdTime, 1, 10);
        nota -= Tester.test(stdDiscount, "A fila não deve desenfileirar duas vezes o mesmo item", Tester::repetitions, stdTime, 1, 200);
        nota -= Tester.test(stdDiscount, "A fila deve gerar permutações bem distribuidas (não enviesadas)", Tester::distribution, stdTime, 5, 4, 200);
        nota -= Tester.test(stdDiscount, "Gerar uma permutação grande não deve demorar muito tempo", Tester::bigCase, stdTime, 5, 100000);
        nota -= Tester.test(stdDiscount, "É possível alternar operações de enfileirar e desenfileirar sem muitos problemas", Tester::dynamic, stdTime, 30, 100);
        nota -= Tester.test(stdDiscount, "É possível chamar todos os métodos especificados no enunciado", Tester::specification, stdTime, 1);
        nota -= Tester.test(stdDiscount, "A função sample funciona corretamente", Tester::sampling, stdTime, 1);
        nota -= Tester.test(stdDiscount, "A fila funciona com Strings", Tester::stringTest, stdTime, 1);

        try {
            Process p = Runtime.getRuntime().exec("javac-algs4 Bridge.java");
            p.waitFor();
        } catch (Throwable e) {
        }
        nota -= Tester.test(stdDiscount, "A classe bridge imprime apenas cartas válidas", Tester::bridgeValid, 60000, 10);
        nota -= Tester.test(stdDiscount, "A classe bridge não imprime três vezes a mesma carta", Tester::bridgeRepeat, 60000, 30);

        StdOut.println("Nota final: " + ((double)(nota) / 100.));
        System.exit(0);
    }
}
