#ifdef PROFESOR
#include "solucion/tabla_hash.hpp"
#else
#include "tabla_hash.hpp"
#endif
#include <iostream>

void exigir(bool ok,const char* texto) { if(!ok) throw std::runtime_error(texto); }

int main() {
    try {
        exigir(hash_cadena("",7)==0,"hash vacio");
        exigir(hash_cadena("ab",7)==5,"Horner ab");
        exigir(hash_cadena("abc",1000)==26,"Horner abc");
        for(const auto& p:{"a","h","o"}) exigir(hash_cadena(p,7)==1,"colisiones");
        TablaHash t(7);
        t.guardar("a",10); t.guardar("h",20); t.guardar("o",0);
        exigir(t.tamano()==3,"tamano insercion");
        exigir(t.cubetas()[1].size()==3,"encadenamiento");
        t.guardar("a",99);
        exigir(t.obtener("a")==std::optional<int>(99),"actualizacion");
        exigir(t.obtener("h")==std::optional<int>(20),"no sobrescribir colision");
        exigir(t.obtener("o")==std::optional<int>(0),"valor cero");
        exigir(!t.obtener("v") && t.tamano()==3,"consulta ausente no inserta");
        auto copia=t.cubetas(); copia[1].clear();
        exigir(t.cubetas()[1].size()==3,"snapshot independiente");
        exigir(t.borrar("h") && !t.borrar("h"),"borrar");
        exigir(t.obtener("o")==std::optional<int>(0),"borrado no rompe cadena");
        bool lanzo=false;
        try { t.guardar("abc!",7); } catch(const std::invalid_argument&) { lanzo=true; }
        exigir(lanzo && t.tamano()==2,"invalidos sin cambios");
        lanzo=false;
        try { TablaHash invalida(0); } catch(const std::invalid_argument&) { lanzo=true; }
        exigir(lanzo,"capacidad positiva");
        TablaHash contador(1);
        for(const auto& p:{"casa","caso","casa","pez","pez","pez"})
            contador.guardar(p,contador.obtener(p).value_or(0)+1);
        exigir(contador.obtener("casa")==std::optional<int>(2),"contador casa");
        exigir(contador.obtener("pez")==std::optional<int>(3),"contador pez");
        exigir(contador.factor_carga()==3.0,"carga mayor que uno");
        contador.guardar("",0);
        exigir(contador.obtener("")==std::optional<int>(0),"clave vacia");
        std::cout<<"Hash y tabla propia: OK\n";
        return 0;
    } catch(const std::exception& e) {
        std::cerr<<"FALLO: "<<e.what()<<'\n'; return 1;
    }
}
