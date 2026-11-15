#ifdef PROFESOR
#include "solucion/diccionarios.hpp"
#include "solucion/trie.hpp"
#else
#include "diccionarios.hpp"
#include "trie.hpp"
#endif
#include <iostream>

int main() {
    int n;
    if (!(std::cin>>n)) return 0;
    std::vector<std::string> palabras(n);
    for(auto& p:palabras) std::cin>>p;
    int q;
    std::cin>>q;
    auto primera=primera_unica(palabras);
    std::cout<<(primera ? *primera : "-")<<'\n';
    Trie indice;
    for(const auto& p:palabras) indice.insertar(p);
    for(int i=0;i<q;++i) {
        std::string prefijo;
        std::cin>>prefijo;
        if(prefijo=="-") prefijo.clear();
        auto resultado=indice.autocompletar(prefijo);
        if(resultado.empty()) std::cout<<'-';
        for(std::size_t j=0;j<resultado.size();++j) {
            if(j) std::cout<<' ';
            std::cout<<resultado[j];
        }
        std::cout<<'\n';
    }
}
