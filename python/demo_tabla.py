"""Traza ya hecha; ejecutar después de completar hash_cadena y TablaHash."""
from tabla_hash import hash_cadena, TablaHash


def main():
    m=7
    h=0
    print('Horner para ab, m=7:')
    for letra in 'ab':
        valor=ord(letra)-ord('a')+1
        siguiente=(31*h+valor)%m
        print(f'{letra}: (31*{h}+{valor}) mod {m} = {siguiente}')
        h=siguiente
    assert hash_cadena('ab',m)==h
    tabla=TablaHash(m)
    for clave,valor in [('a',10),('h',20),('o',0),('a',99),('ab',40)]:
        tabla.guardar(clave,valor)
        print('guardar',clave,valor,'->',tabla.cubetas())
    print('h:',tabla.obtener('h'),'v:',tabla.obtener('v'))
    tabla.borrar('h')
    print('Tras borrar h, o sigue siendo:',tabla.obtener('o'))
    print('Tamano:',tabla.tamano(),'alfa:',tabla.factor_carga())


if __name__=='__main__':
    main()
