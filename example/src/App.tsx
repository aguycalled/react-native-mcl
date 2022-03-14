import * as React from 'react';
import * as mcl from 'react-native-mcl';

import { StyleSheet, View, Text } from 'react-native';

export default function App() {
  const [result, setResult] = React.useState('');

  React.useEffect(() => {
    mcl.init().then(() => {
      let t = new mcl.Fr();

      t.deserialize(new Uint8Array([2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]));

      setResult(t.serialize().toString())

      const assert_equal = (a: any, b: any) => {
        if (a == b)
          console.log(a == b)
        else
          console.log(`FAILED: ${a} != ${b}`)
      }

      const assert = console.log;

      function serializeSubTest(Cstr: any, x: any, newDeserializeHexStr: any) {
        const y = new Cstr()
        y.deserialize(x.serialize())
        assert(y.isEqual(x))
        y.clear()
        const s = x.serializeToHexStr()
        y.deserializeHexStr(s)
        assert(y.isEqual(x))
        const z = newDeserializeHexStr(s)
        assert(z.isEqual(x))
      }

      console.log('fr')

      const a = new mcl.Fr()
      a.setInt(5)
      assert_equal(a.getStr(), '5')
      a.setStr('65535')
      assert_equal(a.getStr(), '65535')
      assert_equal(a.getStr(16), 'ffff')
      a.setStr('ff', 16)
      assert_equal(a.getStr(), '255')
      a.setStr('0x10')
      assert_equal(a.getStr(), '16')
      assert_equal(a.getStr(16), '10')
      const b = new mcl.Fr()
      a.setByCSPRNG()
      serializeSubTest(mcl.Fr, a, mcl.deserializeHexStrToFr)
      b.deserialize(a.serialize())
      a.setStr('1000000000020')
      b.setInt(-15)
      assert_equal(mcl.add(a, b).getStr(), '1000000000005')
      assert_equal(mcl.sub(a, b).getStr(), '1000000000035')
      a.setInt(200)
      b.setInt(20)
      assert_equal(mcl.mul(a, b).getStr(), '4000')
      assert_equal(mcl.div(a, b).getStr(), '10')
      assert_equal(mcl.mul(mcl.div(b, a), a).getStr(), '20')
      a.setInt(-123)
      assert_equal(mcl.neg(a).getStr(), '123')
      assert_equal(mcl.mul(a, mcl.inv(a)).getStr(), '1')
      a.setInt(123459)
      assert(mcl.mul(a, a).isEqual(mcl.sqr(a)))

      a.setInt(3)
      assert(!a.isZero())
      assert(!a.isOne())
      a.setInt(1)
      assert(!a.isZero())
      assert(a.isOne())
      a.setInt(0)
      assert(a.isZero())
      assert(!a.isOne())
      a.setInt(5)
      b.setInt(3)
      assert(!a.isEqual(b))
      b.setInt(5)
      assert(a.isEqual(b))

      a.setHashOf('abc')
      a.dump()
      b.setHashOf(new Uint8Array([97, 98, 99]))
      assert(a.isEqual(b))
      assert(mcl.sub(a, b).isEqual(mcl.neg(mcl.sub(b, a))))
      {
        a.setInt(5)
        b.setInt(7)
        const c = new mcl.Fr()
        c.setInt(12)
        console.log(mcl.add(a, b).isEqual(c))
      }


      console.log('fp')

      {
        const a = new mcl.Fp()
        a.setHashOf('abc')
        serializeSubTest(mcl.Fp, a, mcl.deserializeHexStrToFp)
        const b = new Uint8Array(a.serialize().length)
        for (let i = 0; i < b.length; i++) {
          b[i] = i
        }
        a.setLittleEndian(b)
        const c = a.serialize()
        // b[b.length - 1] may be masked
        for (let i = 0; i < b.length - 1; i++) {
          assert(b[i] === c[i])
        }
        {
          const P1 = mcl.hashAndMapToG1('abc')
          a.setHashOf('abc')
          const P2 = a.mapToG1()
          assert(P1.isEqual(P2))
        }
        {
          const b = new mcl.Fp()
          const c = new mcl.Fp()
          a.setInt(3)
          b.setInt(5)
          c.setInt(8)
          assert(mcl.add(a, b).isEqual(c))
          assert(mcl.sub(a, b).isEqual(mcl.neg(mcl.sub(b, a))))
          c.setInt(-2)
          assert(mcl.sub(a, b).isEqual(c))
          c.setInt(15)
          assert(mcl.mul(a, b).isEqual(c))
          assert(mcl.div(c, a).isEqual(b))
          c.setInt(9)
          assert(mcl.sqr(a).isEqual(c))
        }
        {
          const b = new mcl.Fp()
          a.setInt(5)
          b.setInt(7)
          const c = new mcl.Fp()
          c.setInt(12)
          assert(mcl.add(a, b).isEqual(c))
        }
      }

      console.log('g1');

      const P = new mcl.G1()
      assert(P.isZero())
      P.clear()
      assert(P.isZero())
      P.setHashOf('abc')
      const Q = new mcl.G1()
      Q.setHashOf('abc')
      assert(P.isEqual(Q))
      Q.setHashOf('abcd')
      assert(!P.isEqual(Q))
      let R1 = mcl.add(P, Q)
      let R2 = mcl.add(Q, P)
      assert(R1.isEqual(R2))
      R1 = mcl.sub(R1, R2)
      assert(R1.isZero())
      R1 = mcl.add(P, P) // 2P
      R1 = mcl.add(R1, P) // 3P
      const r = new mcl.Fr()
      r.setInt(3)
      R2 = mcl.mul(P, r) // 3P
      assert(R1.isEqual(R2))
      R1 = mcl.dbl(P)
      R2 = mcl.add(P, P)
      assert(R1.isEqual(R2))
      const R3 = mcl.normalize(R1)
      assert(R1.isEqual(R3))
      const R4 = new mcl.G1()
      R4.setX(R1.getX())
      assert(!R4.isValid())
      R4.setY(R1.getY())
      assert(!R4.isValid())
      R4.setZ(R1.getZ())
      assert(R4.isValid())
      assert(R1.isEqual(R4))
      serializeSubTest(mcl.G1, R1, mcl.deserializeHexStrToG1)

      console.log('g2')

      {
        const P = new mcl.G2()
        assert(P.isZero())
        P.clear()
        assert(P.isZero())
        P.setHashOf('abc')
        const Q = new mcl.G2()
        Q.setHashOf('abc')
        assert(P.isEqual(Q))
        Q.setHashOf('abcd')
        assert(!P.isEqual(Q))
        let R1 = mcl.add(P, Q)
        let R2 = mcl.add(Q, P)
        assert(R1.isEqual(R2))
        R1 = mcl.sub(R1, R2)
        assert(R1.isZero())
        R1 = mcl.add(P, P) // 3P
        R1 = mcl.add(R1, P)
        const r = new mcl.Fr()
        r.setInt(3)
        R2 = mcl.mul(P, r) // 3P
        assert(R1.isEqual(R2))
        R1 = mcl.dbl(P)
        R2 = mcl.add(P, P)
        assert(R1.isEqual(R2))
        const R3 = mcl.normalize(R1)
        assert(R1.isEqual(R3))
        const R4 = new mcl.G2()
        R4.setX(R1.getX())
        assert(!R4.isValid())
        R4.setY(R1.getY())
        assert(!R4.isValid())
        R4.setZ(R1.getZ())
        assert(R4.isValid())
        assert(R1.isEqual(R4))
        serializeSubTest(mcl.G2, R4, mcl.deserializeHexStrToG2)
      }
    })
  }, []);

  return (
    <View style={styles.container}>
      <Text>Sample: {JSON.stringify(result)}</Text>
      <Text>Check the console for test results.</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
  box: {
    width: 60,
    height: 60,
    marginVertical: 20,
  },
});
