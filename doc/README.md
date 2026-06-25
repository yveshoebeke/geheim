## GEHEIM


### General

Encryption utility that will let you obfuscate the content of a file, rendering it unable to display or otherwise render, its content.

---

### Target Platforms

* MacOS
* Linux
* Unix

---

### Install

* Prerequisites to build the application:
    * A ```C``` or ```C++``` compiler:
        * MacOS: ```Xcode Command Line Tools``` (provides ```clang```).
        * Linux: ```gcc``` or ```clang```.
        * Unix: ```cc``` , ```gcc``` or ```clang```.
    * A native build engine / generator:
        * ```make``` or ```ninja```.
* From the command line (Terminal) type: 
        ```curl -sSL https://yveshoebeke.github.io/build/geheim.sh | sh```
* The installation will start automatically.

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

