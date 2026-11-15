#pragma once
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

inline int hash_cadena(const std::string& clave, int m) {
    if (m<=0) throw std::invalid_argument("m debe ser positivo");
    for(char c:clave) if(c<'a' || c>'z') throw std::invalid_argument("Solo a..z");
    // TODO: Horner, h=0; h=(31*h + c-'a'+1)%m. '' -> 0.
    // Usar 31ULL para evitar overflow con signo en la multiplicación.
    // No usar std::hash. Tiempo O(?), espacio O(?).
    throw std::logic_error("TODO hash_cadena");
}

class TablaHash {
    using Cubeta = std::vector<std::pair<std::string,int>>;
    std::vector<Cubeta> cubetas_;
    int tamano_=0;
public:
    explicit TablaHash(int m=7) {
        if(m<=0) throw std::invalid_argument("m debe ser positivo");
        cubetas_.resize(m);
    }

    void guardar(const std::string& clave,int valor) {
        // TODO: insertar o actualizar. No duplicar ni cambiar m.
        // Sin map/unordered_map/set. Coste O(?), incluyendo el hash.
        (void)clave; (void)valor;
        throw std::logic_error("TODO guardar");
    }

    std::optional<int> obtener(const std::string& clave) const {
        // TODO: valor o nullopt. 0 es válido. Consultar no inserta. O(?).
        (void)clave;
        throw std::logic_error("TODO obtener");
    }

    bool borrar(const std::string& clave) {
        auto& cubeta=cubetas_[hash_cadena(clave,static_cast<int>(cubetas_.size()))];
        for(auto it=cubeta.begin();it!=cubeta.end();++it) {
            if(it->first==clave) {
                cubeta.erase(it); --tamano_; return true;
            }
        }
        return false;
    }

    int tamano() const { return tamano_; }
    double factor_carga() const { return static_cast<double>(tamano_)/cubetas_.size(); }
    std::vector<Cubeta> cubetas() const { return cubetas_; } // copia para trazar
};
