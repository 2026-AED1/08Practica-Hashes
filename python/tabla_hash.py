"""Ejercicio 1: nuestro diccionario de cadenas a enteros, con encadenamiento."""


def hash_cadena(clave, m):
    """Horner: h=0; por letra h=(31*h+valor)%m; a=1,...,z=26.

    '' -> 0. m positivo; clave solo a..z. Tiempo O(?), espacio O(?).
    No usar hash() de Python. La validación ya está dada.
    """
    if m <= 0:
        raise ValueError('m debe ser positivo')
    if not all('a' <= c <= 'z' for c in clave):
        raise ValueError('Solo letras a..z')
    raise NotImplementedError('TODO hash_cadena')


class TablaHash:
    def __init__(self, m=7):
        if m <= 0:
            raise ValueError('m debe ser positivo')
        self._cubetas = [[] for _ in range(m)]
        self._tamano = 0

    def guardar(self, clave, valor):
        """Insertar o actualizar el entero asociado. No duplicar claves.

        Colisión: comparar la clave real dentro de la cubeta.
        No usar dict/set ni cambiar m. Coste O(?), incluyendo el hash.
        """
        raise NotImplementedError('TODO guardar')

    def obtener(self, clave):
        """Entero asociado o None si falta; 0 es un valor válido.

        No insertar al consultar. Coste O(?), incluyendo el hash.
        """
        raise NotImplementedError('TODO obtener')

    def borrar(self, clave):
        """Dado como ejemplo: quitar solo la clave, sin romper la cadena."""
        cubeta = self._cubetas[hash_cadena(clave, len(self._cubetas))]
        for i, (actual, _) in enumerate(cubeta):
            if actual == clave:
                cubeta.pop(i)
                self._tamano -= 1
                return True
        return False

    def tamano(self):
        return self._tamano

    def factor_carga(self):
        return self._tamano / len(self._cubetas)

    def cubetas(self):
        """Copia para inspección, O(m+D). No usar dentro de guardar/obtener."""
        return [cubeta.copy() for cubeta in self._cubetas]
