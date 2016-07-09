#include "../testlib.h"
#include <string>
#include <vector>
#include <sstream>

using namespace std;

char buff[1000];

bool compareWords(string a, string b)
{
    vector<string> va, vb;
    stringstream sa;
    
    sa << a;
    string cur;
    while (sa >> cur)
        va.push_back(cur);

    stringstream sb;
    sb << b;
    while (sb >> cur)
        vb.push_back(cur);

    return (va == vb);
}

int main(int argc, char * argv[])
{
    setName("compare files as sequence of tokens in lines");
    registerTestlibCmd(argc, argv);

    std::string strAnswer;

    std::string first = "";

    inf.readString();
    int n = 0;
    int t = 0;
    int c = 0;
    while (!ans.eof() && !ouf.eof()) 
    {
        std::string opr = inf.readString();
        if (opr[0] == 'a') {
            n++;
            continue;
        }

        std::string j = ans.readString();

        if (j == "" && ans.eof())
          break;
        
        std::string p = ouf.readString();
        strAnswer = p;

        n++;
        t++;

        if (!compareWords(j, p)) {
            if (first == "") {
                sprintf(buff, "linha %d difere - operação: '%s', esperado: '%s', encontrado: '%s'", n, compress(opr).c_str(), compress(j).c_str(), compress(p).c_str());
                first = buff;
            }
        } else {
            c++;
        }
    }

    while (!ans.eof())
        ans.readString();
    while (!ouf.eof())
        ouf.readString();
    
    if (c < t)
        quitf(_pc(200*c/t), "%d linhas certas de %d. primeiro erro: %s", c, t, first.c_str());
    else
        quitf(_pc(200), "perfeito");
}
