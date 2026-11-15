#ifdef PROFESOR
#include "solucion/trie.hpp"
#else
#include "trie.hpp"
#endif
#include <algorithm>
#include <iostream>
#include <random>
#include <set>

void exigir(bool ok,const char* texto) {
    if(!ok) throw std::runtime_error(texto);
}

int main() {
    try {
        Trie t;
        exigir(t.nodos()==1,"raiz inicial");
        exigir(!t.buscar("") && t.empieza_por(""),"vacio: raiz no terminal");
        exigir(t.autocompletar("").empty(),"sin palabras");
        t.insertar("casa"); exigir(t.nodos()==5,"nodos casa");
        t.insertar("caso"); exigir(t.nodos()==6,"compartir cas");
        t.insertar("cama"); exigir(t.nodos()==8,"compartir ca");
        t.insertar("casa"); exigir(t.nodos()==8,"duplicados");
        t.insertar("pe"); t.insertar("pez");
        exigir(t.buscar("casa") && !t.buscar("cas") && t.empieza_por("cas"),"palabra frente a prefijo");
        exigir(t.autocompletar("ca")==std::vector<std::string>({"cama","casa","caso"}),"orden alfabetico");
        exigir(t.autocompletar("pe")==std::vector<std::string>({"pe","pez"}),"prefijo es palabra");
        int antes=t.nodos();
        for(const auto& p:{"casco","z","Casa","casa!","a1"}) {
            exigir(!t.buscar(p),"consulta ausente/invalida");
            exigir(!t.empieza_por(p),"prefijo ausente/invalido");
            exigir(t.autocompletar(p).empty(),"autocompletar ausente/invalido");
        }
        exigir(t.nodos()==antes,"consulta crea nodos");
        bool lanzo=false;
        try { t.insertar("casamiento!"); } catch(const std::invalid_argument&) { lanzo=true; }
        exigir(lanzo && t.nodos()==antes,"validacion previa sin cambios");
        t.insertar("");
        auto todo=t.autocompletar("");
        exigir(t.buscar("") && !todo.empty() && todo[0].empty(),"palabra vacia");
        todo.push_back("intruso");
        exigir(t.autocompletar("").size()+1==todo.size(),"salida independiente");

        Trie aleatorio;
        std::set<std::string> palabras,prefijos{""};
        std::mt19937 rng(808);
        for(int i=0;i<150;++i) {
            std::string p;
            int longitud=static_cast<int>(rng()%7);
            for(int j=0;j<longitud;++j) p+=static_cast<char>('a'+rng()%3);
            aleatorio.insertar(p); palabras.insert(p);
            for(std::size_t j=0;j<=p.size();++j) prefijos.insert(p.substr(0,j));
        }
        exigir(aleatorio.nodos()==static_cast<int>(prefijos.size()),"nodos aleatorios");
        antes=aleatorio.nodos();
        for(const std::string pre:{"","a","b","c","ab","zz","abc"}) {
            std::vector<std::string> esperado;
            for(const auto& p:palabras) if(p.compare(0,pre.size(),pre)==0) esperado.push_back(p);
            exigir(aleatorio.autocompletar(pre)==esperado,"autocompletar aleatorio");
            exigir(aleatorio.autocompletar(pre)==esperado,"consulta repetida");
            exigir(aleatorio.buscar(pre)==(palabras.count(pre)!=0),"buscar aleatorio");
            exigir(aleatorio.empieza_por(pre)==(prefijos.count(pre)!=0),"prefijo aleatorio");
        }
        exigir(aleatorio.nodos()==antes,"mutacion aleatoria");
        std::cout << "Trie: insercion, consultas y autocompletado OK\n";
        return 0;
    } catch(const std::exception& e) {
        std::cerr << "FALLO: " << e.what() << '\n';
        return 1;
    }
}
