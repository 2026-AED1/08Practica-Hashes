"""Programa ya hecho: integra el contador de biblioteca y el trie.

Formato y ejemplos en data/README.md. No hay mensajes interactivos.
"""
from diccionarios import primera_unica
from trie import Trie


def main():
    n=int(input())
    palabras=input().split()
    if len(palabras)!=n:
        raise ValueError('La segunda linea debe contener n palabras')
    q=int(input())
    primera=primera_unica(palabras)
    print(primera if primera is not None else '-')
    indice=Trie()
    for p in palabras:
        indice.insertar(p)
    for _ in range(q):
        prefijo=input().strip()
        if prefijo=='-':
            prefijo=''
        resultado=indice.autocompletar(prefijo)
        print(' '.join(resultado) if resultado else '-')


if __name__ == '__main__':
    main()
