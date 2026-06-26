## GEHEIM


### General

Encryption utility that will let you obfuscate the content of a file, rendering it unable to display or otherwise render, its content.

---

### Target Platforms

* macOS
* Linux
* Unix

---

### System Requirements

* Prerequisites to build the application:
    * A ```C``` or ```C++``` compiler:
        * MacOS: ```Xcode Command Line Tools``` (provides ```clang```).
        * Linux: ```gcc``` or ```clang```.
        * Unix: ```cc``` , ```gcc``` , ```pcc``` ...
    * A native build engine / generator:
        * ```make``` or ```ninja```.

---

### Install

* From the command line (Terminal) type: 
    * ```curl -SL https://yveshoebeke.github.io/install/deploy_geheim.sh | sh```
* The installation will start automatically.
* If standard system directories are not writeable an attempt will be made to create the appropriate locations:
    * ```$HOME/.local/bin/```
    * ```$HOME/.local/share/doc/geheim/```
    * ```$HOME/.local/share/licenses/geheim/```
    * ```$HOME/.local/share/man/```

---

### User Instructions

* ```geheim [-flags] [target]```
* ```-e``` - ```--event``` Encode (omitting will decode)
* ```-f``` - ```--file``` Target file
* ```-o``` - ```--overwrite``` Overwrite (encoding will be performed on the target file itself)
* ```-v``` - ```--version``` Version
* ```-h``` -  ```--help``` Help, shows command line options
* Resulting file will have the ```geheim``` suffix attached to its name.
   * Example: ```my_document.doc``` -> ```my_document.doc.geheim```
   * If the ```-o``` flag is specified the name will not change.
* A blank return on the passcode prompt will omit the passcode process.

---

### Examples

* Encode a file: ```geheim -e -f path/to/file.ext``` 
    * Result: ```path/to/file.ext.geheim``` 
* Encode a file onto itself: ```geheim -e -o -f path/to/file.ext```
* Decode a file: ```geheim -f path/to/file.ext``` 
    * Result: ```path/to/file.ext.geheim```
* Same with a file  overwrite: ```geheim -o -f path/to/file.ext```

---

### Important Notes

* After a file was processed, the resulting file name and hash will be displayed.
* Omitting a passcode will alow anybody to correctly decode with this application.
* Not available for Microsoft Windows(tm) based systems.

---

### License

This code is released under a MIT License

---

