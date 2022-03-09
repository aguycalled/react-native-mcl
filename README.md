# react-native-mcl

React Native MCL

## Installation

```sh
npm install react-native-mcl
```

## Usage

```js
import * as mcl from "react-native-mcl";


mcl.init.then(() => {
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

    const result = mcl.mul(g1, fr);
}
```

## Contributing

See the [contributing guide](CONTRIBUTING.md) to learn how to contribute to the repository and the development workflow.

## License

MIT
