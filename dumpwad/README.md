# Dumpwad Tool

`dumpwad` is a simple command line tool for printing the contents of a WAD file. It
will print the WAD type(IWAD or PWAD), along with the name and size of each lump.

## Usage

The command takes a single argument, which is a path to a WAD file:

```bash
dumpwad <WAD file>
```

Running `dumpwad doom1.wad` gives the following output:

```
dumpwad.exe doom1.wad
+------------------------------+
| IWAD           1264 lumps    |
+------------------------------+
| name           size          |
+------------------------------+
| PLAYPAL        10752         |
| COLORMAP       8704          |
| ENDOOM         4000          |
| DEMO1          20118         |
| DEMO2          15358         |
| DEMO3          8550          |
| E1M1           0             |
| THINGS         1380          |
| LINEDEFS       6650          |
| SIDEDEFS       19440         |
...
```