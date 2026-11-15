#ifdef PROFESOR
#include "solucion/diccionarios.hpp"
#else
#include "diccionarios.hpp"
#endif
#include <iostream>
#include <random>
#include <stdexcept>

void exigir(bool ok,const char* texto) {
    if (!ok) throw std::runtime_error(texto);
}

int main() {
    try {
        exigir(frecuencias({}).empty(),"vacio");
        std::vector<std::string> a{"casa","caso","casa","pez"};
        auto antes=a;
        auto f=frecuencias(a);
        exigir(f==Frecuencias({{"casa",2},{"caso",1},{"pez",1}}),"frecuencias");
        exigir(a==antes,"modifica entrada");
        f["casa"]=99;
        exigir(frecuencias(a).at("casa")==2,"estado compartido");
        exigir(!primera_unica({}),"primera vacio");
        exigir(!primera_unica({"a","a","b","b"}),"ninguna unica");
        exigir(primera_unica({"zorro","abeja","pez"})==std::optional<std::string>("zorro"),"orden entrada");
        exigir(primera_unica({"a","b","c","a","b"})==std::optional<std::string>("c"),"repeticion tardia");
        exigir(primera_unica({"sol"})==std::optional<std::string>("sol"),"una palabra");
        std::mt19937 rng(8);
        const std::vector<std::string> vocab{"a","b","c","z","casa"};
        for (int n=0;n<80;++n) {
            a.clear();
            for(int i=0;i<n;++i) a.push_back(vocab[rng()%vocab.size()]);
            Frecuencias esperado;
            for (const auto& p:vocab) {
                int cuenta=0;
                for (const auto& x:a) if (x==p) ++cuenta;
                if(cuenta) esperado[p]=cuenta;
            }
            std::optional<std::string> primera;
            for (const auto& p:a) if(esperado.at(p)==1) { primera=p; break; }
            antes=a;
            exigir(frecuencias(a)==esperado,"frecuencias aleatorias");
            exigir(primera_unica(a)==primera,"primera aleatoria");
            exigir(a==antes,"entrada aleatoria modificada");
        }
        std::cout << "Frecuencias y primera_unica: OK\n";
        return 0;
    } catch(const std::exception& e) {
        std::cerr << "FALLO: " << e.what() << '\n';
        return 1;
    }
}
