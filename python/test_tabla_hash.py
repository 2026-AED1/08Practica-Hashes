import random
import unittest
from tabla_hash import hash_cadena, TablaHash


class PruebasHash(unittest.TestCase):
    def test_horner_y_colisiones(self):
        self.assertEqual(hash_cadena('',7),0)
        for clave in ['a','h','o']:
            self.assertEqual(hash_cadena(clave,7),1)
        self.assertEqual(hash_cadena('ab',7),5)
        self.assertEqual(hash_cadena('abc',1000),26)
        for m in [1,7,31,101]:
            for clave in ['a','ab','casa','pez','z'*100]:
                esperado=sum((ord(c)-96)*31**(len(clave)-i-1) for i,c in enumerate(clave))%m
                self.assertEqual(hash_cadena(clave,m),esperado)

    def test_invalidos(self):
        for m in [0,-1]:
            with self.assertRaises(ValueError): hash_cadena('a',m)
            with self.assertRaises(ValueError): TablaHash(m)
        for clave in ['A','a!','niño']:
            with self.assertRaises(ValueError): hash_cadena(clave,7)


class PruebasTabla(unittest.TestCase):
    def test_colision_actualizacion_y_cero(self):
        t=TablaHash(7)
        t.guardar('a',10); t.guardar('h',20); t.guardar('o',0)
        self.assertEqual(t.tamano(),3)
        self.assertEqual(t.cubetas()[1],[('a',10),('h',20),('o',0)])
        t.guardar('a',99)
        self.assertEqual(t.obtener('a'),99)
        self.assertEqual(t.obtener('h'),20)
        self.assertEqual(t.obtener('o'),0)
        self.assertIsNone(t.obtener('v'))
        self.assertEqual(t.tamano(),3)
        self.assertAlmostEqual(t.factor_carga(),3/7)

    def test_borrado_dado_no_rompe_cadena(self):
        t=TablaHash(1)
        for p,v in [('a',1),('b',2),('c',3),('',0)]: t.guardar(p,v)
        self.assertTrue(t.borrar('b'))
        self.assertFalse(t.borrar('b'))
        self.assertEqual(t.obtener('c'),3)
        self.assertEqual(t.obtener(''),0)
        self.assertEqual(t.tamano(),3)
        self.assertGreater(t.factor_carga(),1)

    def test_consulta_y_snapshot_no_modifican(self):
        t=TablaHash()
        t.guardar('a',1)
        antes=t.cubetas()
        self.assertIsNone(t.obtener('h'))
        copia=t.cubetas(); copia[1].clear()
        self.assertEqual(t.cubetas(),antes)
        with self.assertRaises(ValueError): t.guardar('ab!',9)
        self.assertEqual(t.cubetas(),antes)

    def test_oraculo_y_contador_con_tabla_propia(self):
        rng=random.Random(81)
        t=TablaHash(3)
        esperado={}
        palabras=['casa','caso','pez','ca','a','h','o']
        for _ in range(100):
            p=rng.choice(palabras)
            valor=t.obtener(p)
            t.guardar(p,1 if valor is None else valor+1)
            esperado[p]=esperado.get(p,0)+1
        self.assertEqual(t.tamano(),len(esperado))
        for p,v in esperado.items(): self.assertEqual(t.obtener(p),v)


if __name__=='__main__':
    unittest.main()
