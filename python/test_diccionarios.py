"""Tests públicos. Ejecutar desde python/: python -m unittest -v test_diccionarios."""
import random
import unittest
from diccionarios import frecuencias, primera_unica


class PruebasFrecuencias(unittest.TestCase):
    def test_vacio_y_repeticiones(self):
        self.assertEqual(frecuencias([]), {})
        self.assertEqual(frecuencias(['casa','caso','casa','pez']), {'casa':2,'caso':1,'pez':1})
        self.assertEqual(frecuencias(['a']*20), {'a':20})

    def test_no_modificar_ni_compartir_resultado(self):
        palabras=['pez','casa','pez']
        antes=palabras.copy()
        a=frecuencias(palabras)
        a['pez']=99
        self.assertEqual(palabras, antes)
        self.assertEqual(frecuencias(palabras), {'pez':2,'casa':1})

    def test_aleatorio_con_oraculo(self):
        rng=random.Random(8)
        for _ in range(40):
            palabras=[rng.choice(['ca','casa','caso','pe','pez','x']) for _ in range(rng.randrange(100))]
            esperado={p:palabras.count(p) for p in set(palabras)}
            self.assertEqual(frecuencias(palabras), esperado)


class PruebasPrimeraUnica(unittest.TestCase):
    def test_orden_de_entrada_no_alfabetico(self):
        self.assertEqual(primera_unica(['zorro','abeja','zorro','pez','casa']), 'abeja')
        self.assertEqual(primera_unica(['zorro','abeja','pez']), 'zorro')

    def test_ninguna_y_repeticiones_tardias(self):
        self.assertIsNone(primera_unica([]))
        self.assertIsNone(primera_unica(['a','a','b','b']))
        self.assertEqual(primera_unica(['a','b','c','a','b']), 'c')
        self.assertEqual(primera_unica(['sol']), 'sol')

    def test_entrada_intacta_y_aleatorios(self):
        rng=random.Random(80)
        for _ in range(50):
            palabras=[rng.choice(['a','b','c','d','z']) for _ in range(rng.randrange(15))]
            antes=palabras.copy()
            esperado=next((p for p in palabras if palabras.count(p)==1),None)
            self.assertEqual(primera_unica(palabras),esperado)
            self.assertEqual(palabras,antes)


if __name__ == '__main__':
    unittest.main()
