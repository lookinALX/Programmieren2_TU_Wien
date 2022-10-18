# Hausübung 1 (Abgabe via TUWEL bis 7. November 10:00 Uhr)

Hinweis: Diese Hausübung wird als Projektordner mit CMake-Konfiguration ausgegeben, und wir empfehlen Ihnen bei der Ausarbeitung von dieser Konfiguration intensiv Gebrauch zu machen. 

Gegeben ist die Struktur `struct Vector` (in folgendem *Vector*), die ein dynamisch alloziertes Array `data` mit Elementen vom Typ `T` (siehe Typedef) und dessen aktuelle Größe `size` hält.

```cpp
typedef double T;
struct Vector
{
  T *data;     
  size_t size;  
};
```

Es ist Ihre Aufgabe, die folgenden Funktionen zu implementieren (genauere Anforderungen siehe unten):

```cpp
void vector_init(struct Vector *self, size_t n, const T *init);
void vector_free(struct Vector *self);

void vector_push_back(struct Vector *self, const T *value);
void vector_pop_back(struct Vector *self);

void vector_push_front(struct Vector *self, const T *value);
void vector_pop_front(struct Vector *self);

void vector_insert_before(struct Vector *self, size_t n, const T *value);
void vector_erase(struct Vector *self, size_t n);

void vector_reverse(struct Vector *self);
```

Die obigen Funktionen haben alle als erstes Argument einen Zeiger auf das betreffende *Vector*-Objekt, und deshalb auch den Namenspräfix `vector_`.

Die Definition der Struktur `struct Vector` und die Deklarationen obiger Funktionen befinden sind in der Datei `include/Vector.h`.
Ihre Aufgabe ist es, die Definitionen der Funktionen in der Datei `src/Vector.c` zu implementieren.
Diese beiden Quelltextdateien (`include/Vector.h` und `src/Vector.c`) stellen eine Übersetzungseinheit dar, werden also zu einer Objektdatei (nicht ausführbar, da keine `main`-Funktion enthalten ist) kompiliert.

Diese C-Datei alleine kann noch zu keinem ausführbares Programm übersetzt werden, da noch keine `main` Funktion enthalten ist.
Erst das Linken (Zusammenhängen) dieser Objektdatei mit einer anderen Objektdatei mit enthaltener `main` Funktion, kann ein ausführbares Programm erzeugen.

Im Ordner `test` sind Programmteile verfügbar, die jeweils eine gewisse Funktionalität aus `Vector.c` testen sollen. Weiters können diese als Hilfestellung bei der Implementierung der Funktionen dienen. Die Tests stellen ebenso die Basis für die Bewertung der Hausübuing dar.

Jeder Quelltext eines Tests enthält eine `main` Funktion, die ebenfalls zu einer Objektdatei kompiliert wird. 
Zusammengehängt mit voriger Objektdatei entsteht ein ausführbares Programm, welches eine Funktionalität testet und wie weiter unten beschrieben mit `ctest` ausgeführt werden kann. 

**Wichtig 1:** Es steht Ihnen frei, während der Entwicklung auch den Quellcode der Tests zwecks Debugging/Fehlersuche anzupassen. 

**Wichtig 2:** Sobald Sie die Implementiereung der Funktionen in der Datei `src/Vector.c` abgeschlossen haben, laden Sie **nur die Datei `src/Vector.c`** nach TUWEL noch. 

**Wichtig 3:** Die Header-Datei `include/Vector.h` stellt die Schnittstelle zwischen dem *Vector*-Typ samt Funktionen und den Tests dar, und darf von Ihnen **nicht verändert werden** (deshalb müssen Sie diese Datei auch gar nicht nach TUWEL hochladen).

**Wichtig 4:** Fügen Sie `#include`s für die von Ihnen benötigten Header aus der Standardbibliothek in `src/Vector.c` ein (und nicht in `src/Vector.c`).

Folgender Verzeichnisbaum gibt einen Überblick über die Projektstruktur:
```
.
├── include
│   └── Vector.h                    Schnittstelle zwischen Vector und Tests
├── src
│   └── Vector.c                    Hier implementieren Sie die Funktionen
├── test
│   ├── CMakeLists.txt              Konfiguration der Übersetzungseinheit der Tests
│   ├── test_init_free.c            Testet die Funktionen vector_init und vector_free
│   ├── test_insert_before.c        Testet die Funktion vector_insert_before
│   ├── test_erase.c                Testet die Funktion vector_erase
│   ├── test_push_pop_back.c        Testet die Funktionen vector_push_back und vector_pop_back
│   ├── test_push_pop_front.c       Testet die Funktionen vector_push_front und vector_pop_front
│   └── test_reverse.c              Testet die Funktion vector_reverse           
├── CMakeLists.txt                Konfiguration der Übersetzungseinheit des Vector
└── README.md                     
```

## Vorgehensweise (CMake/CTest):

Sie können folgende Befehle nutzen, um zu kontrollieren ob einzelne oder alle Tests mit Ihrer Implementierung durchlaufen oder Fehler melden:

```
cd path/to/my/project
cmake -S . -B build                             # configure build (into build folder)
cmake --build build                             # build all targets
cmake --build build --target Vector             # build only Vector
ctest --test-dir build                          # run all tests
ctest --test-dir build -R test_erase --verbose  # run test_erase with output
```

Nach dem Verändern einer der Sourcedateien müssen eventuell manche Executables/Tests neu generiert werden.
Dies erledigt CMake automatisch für sie:
```
cmake --build build   # (re-)compiles all targets
```
Danach können die Tests wieder mit ctest getestet werden.

## `struct Vector`: Allgemeines/Invarianten 

```cpp
typedef double T;
struct Vector
{
  T *data;      // pointer to first element of dynamic array
  size_t size;  // number of elements in dynamic array
};
```

- `data` zeigt immer auf das erste Element im dynamisch allozierten Feld
- `size` hält immer die aktuelle Anzahl an Elementen in `data`
- Die Größe des dynamisch allozierten Speichers `data` entspricht immer genau der aktuellen Anzahl an Elementen im Vector.
- Falls ein Vector keine Ressouren hält (also leer ist), gilt: `size == 0` und `data == NULL`
- Bei allen Funktionen gilt die Annahme, dass der übergebene Vector `self` kein Nullzeiger ist.


## `vector_init`: Initialisierung/Allokation (2 Punkte)
```c
void vector_init(struct Vector *self, size_t n, const T *init);
```
Funktionsbeschreibung: Alloziert im übergebenen Vector Speicher für die übergebene Anzahl an Elementen und initialisiert alle Elemente mit dem ebenfalls übergebenen Initialwert. Falls der übergebene Vektor nicht leer ist, werden die bislang gehaltenen Ressourcen vorher freigegeben.

Parameter:

- `self`: Zeiger auf den Vector
- `n`: Anzahl an Elementen 
- `init`: Zeiger auf den Initialwert

## `vector_free`: Deallokation (1 Punkt)
```c
void vector_free(struct Vector *self);
```
Funktionsbeschreibung: Falls der übergebene Vector nicht leer ist, werden die bislang gehaltenen Ressourcen freigegeben.

Parameter:

- `self`: Zeiger auf den Vector 

## `vector_push_back`: Anhängen eines Elements am Ende (1 Punkt)
```c
void vector_push_back(struct Vector *self, const T *value);
```
Funktionsbeschreibung: Fügt ein weiteres Element am Ende hinzu. Die Werte und Reihenfolge aller existierenden Elemente bleibt unberührt.

Parameter:

- `self`: Zeiger auf den Vector  
- `value`: Zeiger auf den einzufügenden Wert

## `vector_pop_back`: Entfernen des letzten Elements (1 Punkt)
```c
void vector_pop_back(struct Vector *self);
```
Funktionsbeschreibung: Entfernt das letzte Element. Die Werte und Reihenfolge aller anderen bereits existierenden Elemente bleibt unberührt.

Parameter:

- `self`: Zeiger auf den Vector  

## `vector_push_front`: Anhängen eines Elements am Anfang (1 Punkt)
```c
void vector_push_front(struct Vector *self, const T *value);
```
Funktionsbeschreibung: Fügt ein weiteres Element am Anfang hinzu. Die bereits vorhandenen Werte wandern dadurch um eins nach hinten, die Reihenfolge bleibt allerdings unberührt.

Parameter:

- `self`: Zeiger auf den Vector  
- `value`: Zeiger auf einzufügenden Wert

## `vector_pop_front`: Entfernen des ersten Elements (1 Punkt)
```c
void vector_pop_front(struct Vector *self);
```
Funktionsbeschreibung: Entfernt das erste Element. Die Werte und Reihenfolge aller anderen bereits existierenden Elemente bleibt unberührt.

Parameter:

- `self`: Zeiger auf den Vector

## `vector_insert_before`: Einfügen eines Elements (1 Punkt)
```c
void vector_insert_before(struct Vector *self, size_t n, const T *value);
```
Funktionsbeschreibung: Fügt ein weiteres Element vor der übergebene Position ein. Die Werte und Reihenfolge aller existierenden Elemente bleibt unberührt.

Parameter:

- `self`: Zeiger auf den Vector
- `n`: Position vor der eingefügt wird
- `value`: Zeiger auf den Initialwert

Annahmen:

- Die übergebene Position `n` liegt im Interval [`0` , `self.size`]


## `vector_erase`: Entfernen eines Elements (1 Punkt)
```c
void vector_erase(struct Vector *self, size_t n);
```
Funktionsbeschreibung: Entfernt das Element an der übergebenen Position. Die Werte und Reihenfolge aller anderen bereits existierenden Elemente bleibt unberührt.

Parameter:

- `self`: Zeiger auf den Vector
- `n`: Position die entfernt wird

Annahmen:

- Die übergebene Position `n` liegt im Intervall [`0` , `self.size - 1`]

## `vector_reverse`: Invertieren der Reihenfolge (1 Punkt)
```c
void vector_reverse(struct Vector *self);
```
Funktionsbeschreibung: Invertiert die Reihenfolge der Elemente des übergebenen Vectors.

Parameter:

- `self`: Zeiger auf den Vector  

Bedingung:

- Die Adresse des dynamischen Arrays im Vector (`self.data`) wird durch die Funktionen nicht verändert. 

