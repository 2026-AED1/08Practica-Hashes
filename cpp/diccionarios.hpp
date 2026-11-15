#pragma once
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using Frecuencias = std::unordered_map<std::string, int>;

// Sin ordenar ni contar con bucles anidados. Tiempo esperado O(?), espacio O(?).
inline Frecuencias frecuencias(const std::vector<std::string>& palabras) {
    (void)palabras;
    throw std::logic_error("TODO frecuencias");
}

// Primera de la ENTRADA con frecuencia 1; std::nullopt si no hay ninguna.
// Usar frecuencias y recorrer palabras; no depender del orden del unordered_map.
// Tiempo esperado O(?), espacio O(?). No modificar palabras.
inline std::optional<std::string> primera_unica(const std::vector<std::string>& palabras) {
    (void)palabras;
    throw std::logic_error("TODO primera_unica");
}
