# Aufgabenstellung Hausübung (Abgabe via TUWEL bis 12. Dezember 10:00 Uhr)

Erweitern Sie die Implementierung in `src/Liste.c` um die folgenden 4 Funktionen (die bereits in `include/Liste.h` deklariert sind).
Sobald Sie die Implementierung der Funktionen in der Datei `src/List.c` abgeschlossen haben, laden Sie **nur die Datei `src/List.c`** nach TUWEL hoch. 

Es steht Ihnen frei, während der Entwicklung auch den Quellcode der Tests (im Ordner `test`) zwecks Debugging/Fehlersuche anzupassen. 

## `list_clone`: Kopie einer Liste (2 Punkt)
```c
struct List *list_clone(const struct List *self);
```
Funktionsbeschreibung: Erzeugt eine unabhängige Kopie der übergebenen Liste. Die geklonte Liste enthaelt eigens allozierte Knoten und keine Verweise auf Knoten der übergebenen Liste.

Parameter `self`: Zeiger auf die Liste 

## `list_concat`: Verketten zweier Listen (2 Punkte)
```c
void list_concat(struct List *dest, struct List *src);
```
Funktionsbeschreibung: Hängt alle Knoten der Liste `src` hinten an die Liste `dest` an. Nach der Verkettung ist die Liste `src` leer.

Parameter 

- `dest`: Zeiger auf die Liste, an die angehängt wird.
- `src`: Zeiger auf die Liste, deren Elemente entnommen werden.

Bedingung: Die Speicheradressen und Werte der einzelnen Knoten bleiben erhalten. Um die Verkettung zu erreichen werden lediglich die Zeiger `prev` und `next` angepasst.

## `list_reverse`: Invertieren der Reihenfolge (3 Punkte)
```c
void list_reverse(struct List *self);
```
Funktionsbeschreibung: Invertiert die Reihenfolge der Elemente der übergebenen Liste.

Parameter `self`: Zeiger auf die Liste 

Bedingung: Die Speicheradressen und Werte der einzelnen Knoten bleiben erhalten. Um die Reihenfolge zu invertieren werden lediglich die Zeiger `prev` und `next` angepasst.

## `list_find`: Ersten Knoten finden, der eine Bedingung erfüllt (3 Punkte)
```c
struct ListNode *list_find(struct ListNode *start, struct ListNode *end,
                           bool (*predicate)(const T *value));

```
Funktionsbeschreibung: Gibt den Zeiger auf den ersten Knoten im Intervall `start` bis `end` zurück, dessen Wert (`value`) eine mittels Funktionszeiger übergebene Bedingung erfüllt. Der übergebene Knoten `end` selbst ist nicht mehr Teil des Intervalls. Falls kein Knoten im Intervall die Bedingung erfüllt, wird `end` zurückgegeben, andernfalls der gefundene Knoten.


Parameter 

- `start`: Zeiger auf den ersten Knoten des Intervalls.
- `end`: Zeiger auf den ersten Knoten nach dem Intervall.
- `predicate`: Suchbedingung.

Rückgabewert: Zeiger auf den gefundenen Knoten oder `end`, falls kein Knoten im Intervall die Bedingung erfüllt.

Annahme: Die übergebenen Knoten sind Bestandteil einer Liste und `start` ist in der Liste vor `end` gereiht. Gültig ist auch `start == end` (also ein leeres Intervall). 

## Vorgehensweise (CMake/CTest):

Sie können folgende Befehle nutzen, um einzelne oder alle Tests mit Ihrer Implementierung zu kompilieren und auszuführen:

```
cd project/home/folder
cmake -S . -B build                 # configure build (into build folder)
cd build                            # change to build folder
make                                # try to build all targets
make test_clone                     # try to build single target
ctest --verbose                     # run all tests
./test/test_clone                   # run single test as regular executable  
```
