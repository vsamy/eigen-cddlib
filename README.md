# DEPRECATED

Please refer to [eigen-ccd](https://github.com/vsamy/eigen-cdd)

# eigen-cddlib

eigen-cddlib is a library that wraps cdd library.

## Installing

### Manual

#### Dependencies

To compile you need the following tools:

 * [Git]()
 * [CMake]() >= 2.8
 * [pkg-config]()
 * [doxygen]()
 * [c++ compiler]() Version to compile C++0x
 * [Boost](http://www.boost.org/doc/libs/1_58_0/more/getting_started/unix-variants.html) >= 1.58 (Older version may work as well)
 * [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) >= 3.2
 * [cdd]()

#### Building
First install cddlib
```sh
sudo apt-get install libcdd-dev
```

then install the eigen-cddlib part

```sh
git clone --recursive https://github.com/vsamy/eigen-cddlib
cd eigen-cddlib
mkdir _build
cd _build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFX=<your_path>
make -j8
make install
```

If cdd has not been install in the default path, cmake may not find it (there is no pkg-config for cdd).
Add the path as a HINTS in find_path and/or find_library.

#### Testing

Test the file by simply doing a make test.
For c++
```sh
cd eigen-cddlib/_build
make test
```

#### Examples

There is no basic examples yet. Please see test files for an overview.
Please see the doxygen files for the documentation.