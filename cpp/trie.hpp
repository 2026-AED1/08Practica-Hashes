// Trie simplificado del fichero 06_trie_resuelta.cpp: hijos en std::map.
#pragma once
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

class Trie {
    struct Nodo {
        std::map<char, Nodo*> hijos;
        bool finDePalabra = false;
    };
    Nodo* raiz_ = new Nodo;
    int nodos_ = 1;

    static bool valida(const std::string& s) {
        for (char c : s) if (c<'a' || c>'z') return false;
        return true;
    }

    const Nodo* bajar(const std::string& s) const {
        if (!valida(s)) return nullptr;
        // TODO: usar find; una consulta NO debe crear hijos. Tiempo O(?).
        throw std::logic_error("TODO bajar");
    }

    static void recoger(const Nodo* n, std::string& palabra,
                        std::vector<std::string>& salida) {
        // TODO: preorden; copiar palabra si es terminal; push/pop al recorrer.
        // Restaurar palabra. std::map recorre hijos en orden alfabético.
        (void)n; (void)palabra; (void)salida;
        throw std::logic_error("TODO recoger");
    }

    static void liberar(Nodo* n) {
        if (!n) return;
        for (const auto& par : n->hijos) liberar(par.second);
        delete n;
    }

public:
    Trie() = default;
    ~Trie() { liberar(raiz_); }
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

    // Pre: longitud <= 100. '' se admite; inválida -> excepción sin cambios.
    // Duplicados no crean nodos. Tiempo O(?); nuevos nodos O(?).
    void insertar(const std::string& palabra) {
        if (!valida(palabra)) throw std::invalid_argument("Solo letras a..z");
        throw std::logic_error("TODO insertar");
    }

    bool buscar(const std::string& palabra) const {
        // TODO: no basta con que exista el camino. O(?).
        (void)palabra;
        throw std::logic_error("TODO buscar");
    }

    bool empieza_por(const std::string& prefijo) const {
        // TODO: comprobar camino; vacío -> true, incluso sin claves. O(?).
        (void)prefijo;
        throw std::logic_error("TODO empieza_por");
    }

    // Dado. Salida alfabética, sin duplicados. Inválido/ausente -> vacío.
    std::vector<std::string> autocompletar(const std::string& prefijo) const {
        std::vector<std::string> salida;
        const Nodo* n = bajar(prefijo);
        if (n) {
            auto palabra = prefijo;
            recoger(n, palabra, salida);
        }
        return salida;
    }

    int nodos() const { return nodos_; }
};
