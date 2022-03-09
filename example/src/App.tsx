import * as React from 'react';

import { StyleSheet, View, Text } from 'react-native';
import * as mcl from 'react-native-mcl';

export default function App() {
  const [result, setResult] = React.useState([0]);
  const [result2, setResult2] = React.useState('');
  const [rand, setRandom] = React.useState('');

  React.useEffect(() => {
    mcl.init();
    let rr = [];

    let g1 = new mcl.G1();
    g1.deserialize(new Uint8Array([
      0xc0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0,
    ]));
    let fr = new mcl.Fr();
    fr.deserialize(new Uint8Array([
      2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
    ]))

    setResult2(mcl.mulVec([g1],[fr]).serialize().toString())

    setResult(rr);
    let random = new mcl.Fr();
    random.setLittleEndian(new Uint8Array([0xc2, 2, 2]));
    setRandom(random.getStr(16));
  }, []);

  return (
    <View style={styles.container}>
      <Text>Result: {JSON.stringify(result)}</Text>
      <Text>Result2: {JSON.stringify(result2)}</Text>
      <Text>Random: {JSON.stringify(rand)}</Text>
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
