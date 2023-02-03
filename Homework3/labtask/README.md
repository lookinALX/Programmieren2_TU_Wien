# Aufgabenstellung im Labor 3

Implementieren Sie die folgenden 4 Funktionen in den bereits vorbereiteten Dateien. Neben der Funktionsentwicklung gehört es auch zu Ihren Aufgaben Annahmen (also welchen Zustand Sie nach den jeweiligen Funktionsaufrufen erwarten) mittels (`assert`) zu überprüfen. 

---

**Demonstration**

0. Quelldateien Herunterladen: [https://gitlab.tuwien.ac.at/360.017_programming_2/homework3](https://gitlab.tuwien.ac.at/360.017_programming_2/homework3)

1. Implementierung Funktionen `list_pop_front` und `list_push_front` 
    - Implementieren Sie die beiden Funktionen anhand der untenstehenden Spezifikationen in der bereits vorbereiteten Datei `labtask/test_push_front_pop_front.c` .
    - Implementieren Sie ebenso die bereits in der Quelldatei angedeuteten Annahmen mittels Aufrufen von `assert` [(cppref)](https://en.cppreference.com/w/c/error/assert).
    - Nutzen Sie die CMake-Konfiguration die im Ordner `labtask` zur Verfügung steht um den Test zu kompilieren und auszuführen.

2. Implementierung Funktionen `list_insert_before` und `list_insert_after` 
    - Implementieren Sie die beiden Funktionen anhand der untenstehenden Spezifikationen in der bereits vorbereiteten Datei `labtask/test_insert_before_insert_after.c` .
    - Implementieren Sie ebenso die bereits in der Quelldatei angedeuteten Annahmen mittels Aufrufen von `assert` [(cppref)](https://en.cppreference.com/w/c/error/assert).
    - Nutzen Sie die CMake-Konfiguration die im Ordner `labtask` zur Verfügung steht um den Test zu kompilieren und auszuführen.

---

## `list_pop_front`: Entfernen des ersten Elements 
### (`labtask/test_push_front_pop_front.c`)
```c
void list_pop_front(struct List *self);
```
Funktionsbeschreibung: Entfernt das erste Element (und gibt den zugehörigen Speicher frei).

Parameter `self`: Zeiger auf die Liste

Annahme: Die Liste ist nicht leer.

## `list_push_front`: Anhängen eines Elements am Anfang
### (`labtask/test_push_front_pop_front.c`)
```c
void list_push_front(struct List *self, const T *value);
```
Funktionsbeschreibung: Fügt ein weiteres Element am Anfang hinzu.

Parameter:

- `self`: Zeiger auf die Liste  
- `value`: Zeiger auf den einzufügenden Wert

## `list_insert_before`: Einfügen eines Elements vor dem übergebenen Knoten
### (`labtask/test_insert_before_insert_after.c`)
```c
void list_insert_before(struct ListNode *node, const T *value);
```
Funktionsbeschreibung: Fügt einen Knoten mit dem übergebenen Wert vor dem übergebenen Knoten ein.

Parameter:

- `self`: Zeiger auf den Knoten vor dem eingefügt wird. 
- `value`: Zeiger auf den einzufügenden Wert

Annahme: Der übergebene Knoten ist Bestandteil einer Liste.

## `list_insert_after`: Einfügen eines Elements nach dem übergebenen Knoten
### (`labtask/test_insert_before_insert_after.c`)
```c
void list_insert_after(struct ListNode *node, const T *value);
```
Funktionsbeschreibung: Fügt einen Knoten mit dem übergebenen Wert nach dem übergebenen Knoten ein.

Parameter:

- `self`: Zeiger auf den Knoten, nach dem eingefügt wird.
- `value`: Zeiger auf den einzufügenden Wert.

Annahme:

- Der übergebene Knoten ist Bestandteil einer Liste.

## Vorgehensweise (CMake/CTest):

Sie können folgende Befehle nutzen, um einzelne oder alle Tests mit Ihrer Implementierung zu kompilieren und auszuführen:

```
cd labtask
cmake -S . -B build                 # configure build (into build folder)
cd build                            # change to build folder
make                                # try to build all targets
make test_push_front_pop_front      # try to build single target
ctest --verbose                     # run all tests
./test_push_front_pop_front         # run single test as regular executable  
```
