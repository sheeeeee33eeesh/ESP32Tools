# ESP32 Tools

Compilation of different hacking tool firmware sources using platform.io. If you're interested in creating all-in-one hacking tools such as ESP32 Maurader and others here's a good place to start

**Build Command**
```bash
pio run --target upload
```

For projects that use additional libraries you may need to run 
```bash
pio run -t compiledb
```

[platform.io Install Guide](https://docs.platformio.org/en/latest/core/installation/methods/installer-script.html)

## Projects
- [CC1101](./CC1101/ReadME.md)
- [WifiScan](./WifiScan/ReadME.md)
- [bluetoothSpam](./bluetoothSpam/ReadME.md)
- [touchScreenDisplay](./touchScreenDisplay/ReadME.md)
