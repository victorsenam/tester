#include "../testlib.h"
#include <sstream>

using namespace std;

const int N = 10000;

bool val[N];

bool getVal (int a) {
    if (a < 0)
        return !val[-a-1];
    return val[a-1];
}

int main(int argc, char * argv[])
{
    setName("2-sat checker\n");

    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();

    string res = upperCase(ouf.readString());
    if (res == "MENTIRA") {
        res = upperCase(ans.readString());
        
        if (res == "MENTIRA")
            quitf(_ok, "não há como satisfazer a expressão\n");
        else if (res != "VERDADE")
            quitf(_fail, "juíz dá resposta inválida %s\n", res.c_str());

        for (int i = 0; i < n; i++)
            val[i] = ans.readInt(0, 1);

        for (int i = 0; i < m; i++) {
            bool a = getVal(inf.readInt());
            bool b = getVal(inf.readInt());

            if (!(a || b))
                quitf(_fail, "juíz dá valoração falsa e diz ser verdadeira\n");
        }

        quitf(_wa, "solução existente e não encontrada\n");
    } else if (res == "VERDADE") {
        res = upperCase(ans.readString());
        for (int i = 0; i < n; i++)
            val[i] = ouf.readInt(0, 1);

        for (int i = 0; i < m; i++) {
            bool a = getVal(inf.readInt());
            bool b = getVal(inf.readInt());


            if (!(a || b))
                quitf(_wa, "valoração dada não satisfaz a expressão\n");
        }

        if (res == "MENTIRA")
            quitf(_fail, "solução do juíz não encontra valoração existente\n");
        else if (res != "VERDADE")
            quitf(_fail, "juíz dá resposta inválida %s\n", res.c_str());

        quitf(_ok, "solução correta\n");
    } else {
        quitf(_wa, "resposta inválida %s\n", res.c_str());
    }
}
