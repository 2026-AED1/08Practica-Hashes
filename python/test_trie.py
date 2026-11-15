"""Pruebas públicas: palabras frente a prefijos, orden y consultas sin mutación."""
import random
import unittest
from trie import Trie


def construir(palabras):
    t=Trie()
    for p in palabras:
        t.insertar(p)
    return t


class PruebasInsercion(unittest.TestCase):
    def test_raiz_prefijos_compartidos_y_duplicados(self):
        t=Trie()
        self.assertEqual(t.nodos(),1)
        t.insertar('casa')
        self.assertEqual(t.nodos(),5)
        t.insertar('caso')
        self.assertEqual(t.nodos(),6)
        t.insertar('cama')
        self.assertEqual(t.nodos(),8)
        t.insertar('casa')
        self.assertEqual(t.nodos(),8)

    def test_cadena_vacia_y_validacion_antes_de_crear(self):
        t=Trie()
        t.insertar('')
        self.assertEqual(t.nodos(),1)
        for invalida in ['casa!','Casa','niño','a b','a1']:
            with self.assertRaises(ValueError):
                t.insertar(invalida)
            self.assertEqual(t.nodos(),1)


class PruebasConsultas(unittest.TestCase):
    def test_palabra_y_prefijo_no_son_lo_mismo(self):
        t=construir(['casa','caso','pe','pez'])
        self.assertTrue(t.buscar('casa'))
        self.assertFalse(t.buscar('cas'))
        self.assertTrue(t.empieza_por('cas'))
        self.assertTrue(t.buscar('pe'))
        self.assertTrue(t.empieza_por('pe'))
        self.assertFalse(t.buscar('perro'))

    def test_consultas_no_crean_nodos(self):
        t=construir(['casa'])
        antes=t.nodos()
        for palabra in ['casco','z','casa!','Casa','niño']:
            self.assertFalse(t.buscar(palabra))
            self.assertFalse(t.empieza_por(palabra))
        self.assertEqual(t.nodos(),antes)

    def test_vacio_tiene_raiz_pero_no_palabra(self):
        t=Trie()
        self.assertFalse(t.buscar(''))
        self.assertTrue(t.empieza_por(''))
        t.insertar('')
        self.assertTrue(t.buscar(''))


class PruebasAutocompletar(unittest.TestCase):
    def test_alfabetico_terminal_y_duplicados(self):
        t=construir(['pez','caso','casa','cama','pe','casa','casco'])
        self.assertEqual(t.autocompletar('ca'),['cama','casa','casco','caso'])
        self.assertEqual(t.autocompletar('pe'),['pe','pez'])
        self.assertEqual(t.autocompletar('casa'),['casa'])
        self.assertEqual(t.autocompletar('x'),[])
        self.assertEqual(t.autocompletar('C'),[])

    def test_todas_incluida_palabra_vacia_y_salida_independiente(self):
        t=construir(['z','a',''])
        self.assertEqual(t.autocompletar(''),['','a','z'])
        salida=t.autocompletar('')
        salida.append('intruso')
        self.assertEqual(t.autocompletar(''),['','a','z'])
        self.assertEqual(Trie().autocompletar(''),[])

    def test_recoger_restaura_camino_y_no_reinicia_salida(self):
        t=construir(['casa','caso'])
        camino=list('cas')
        salida=['previo']
        t._recoger(t._bajar('cas'),camino,salida)
        self.assertEqual(camino,list('cas'))
        self.assertEqual(salida,['previo','casa','caso'])

    def test_aleatorio_con_oraculo_y_consultas_repetidas(self):
        rng=random.Random(808)
        palabras=[''.join(rng.choice('abc') for _ in range(rng.randrange(7))) for _ in range(100)]
        t=construir(palabras)
        conjunto=set(palabras)
        prefijos={p[:i] for p in conjunto for i in range(len(p)+1)}
        self.assertEqual(t.nodos(),len(prefijos))
        for pre in ['','a','b','c','ab','zz','abc']:
            esperado=sorted(p for p in conjunto if p.startswith(pre))
            self.assertEqual(t.autocompletar(pre),esperado)
            self.assertEqual(t.autocompletar(pre),esperado)
            self.assertEqual(t.empieza_por(pre),pre in prefijos)
            self.assertEqual(t.buscar(pre),pre in conjunto)
        self.assertEqual(t.nodos(),len(prefijos))


if __name__ == '__main__':
    unittest.main()
