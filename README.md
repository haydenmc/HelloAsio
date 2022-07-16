# Installing Dependencies

```sh
vcpkg install asio
```

# Building

```sh
mkdir build
cd build
cmake .. "-DCMAKE_TOOLCHAIN_FILE=C:\path\to\vcpkg\scripts\buildsystems\vcpkg.cmake"
```