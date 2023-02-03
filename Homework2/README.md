# Hausübung 2 (Abgabe via TUWEL bis 21. November 10:00 Uhr)

Hinweis: Diese Hausübung wird als Projektordner mit CMake-Konfiguration ausgegeben, und wir empfehlen Ihnen bei der Ausarbeitung von dieser Konfiguration intensiv Gebrauch zu machen. 

Ihre Aufgabe ist es, die folgenden  Funktionen in `src/numerics.c` nach den untenstehenden Anforderungen zu implementieren. Die Deklarationen der Funktionen befinden sich bereits in `include/numerics.h`.

```cpp
struct Vector *num_linspace(double start, double stop, size_t n);
struct Vector *num_sample(const struct Vector *x, double (*func)(double));
struct Vector *num_interpolate(const struct Vector *xinterp, const struct Vector *x,
                          const struct Vector *f);
struct Vector *num_grad(const struct Vector *x, const struct Vector *f);
double num_integrate(const struct Vector *x, const struct Vector *f);
```

Die Funktionen arbeiten mit Parametern vom Typ `struct Vector` und geben ebenso Zeiger auf (dynamisch allozierte) Strukturen vom Typ `struct Vector` zurück. Sie sollen die gegebene Datenstruktur *Vector* und die dazugehörigen Funktionen (Präfix `vector_`) **benutzen aber nicht anpassen**, um die Funktionalität für die obigen 5 Funktionen zu implementieren. 

**Hinweis:** Sie können sich im Ordner `test_vector` den Quellcode der Tests zum `struct Vector`-Typ und den zugeordnenten Funktionen ansehen um sich mit der Funktionalität vertraut zu machen. 

Folgender Verzeichnisbaum gibt einen Überblick über die Projektstruktur:
```
.
├── CMakeLists.txt         Root-Konfiguration
├── include         
│   ├── helpers.h          allgemeine Hilfsfunktionen
│   ├── numerics.h         Deklarationen der von Ihnen zu implementierenden Funktionen
│   └── Vector.h           Deklarationen der Vector Datenstruktur
├── src
│   ├── numerics.c         Hier implementieren Sie Ihre Funktionen
│   └── Vector.c           Definitionen der Funktionen zur Vector Datenstruktur
├── test
│   ├── CMakeLists.txt     Test-Konfiguration
│   ├── test_linspace.c    Testet die Funktion num_linspace
│   ├── test_sample.c      Testet die Funktion num_sample (, num_linspace)
│   ├── test_interpolate.c Testet die Funktion num_interpolate (, num_sample, num_linspace)
│   ├── test_grad.c        Testet die Funktion num_grad (, num_sample, num_linspace)
│   └── test_integrate.c   Testet die Funktion num_integrate (, num_sample, num_linspace)
└── test_vector            Ordner mit Test für vector_* -Funktionen    
    ├── ...               
    └── ...
              
```

Es steht Ihnen frei, während der Entwicklung auch den Quellcode der Tests zwecks Debugging/Fehlersuche anzupassen. 

Sobald Sie die Implementiereung der Funktionen in der Datei `src/numerics.c` abgeschlossen haben, laden Sie **nur die Datei `src/numerics.c`** nach TUWEL noch. 

Die Header-Datei `include/numerics.h` stellt die Schnittstelle zwischen den Funktionen und den Tests dar, und darf von Ihnen **nicht verändert werden** (deshalb müssen Sie diese Datei auch gar nicht nach TUWEL hochladen).

Fügen Sie `#include`s für die von Ihnen benötigten Header aus der Standardbibliothek in `src/numerics.c` ein (und nicht in `include/numerics.h`).

## Vorgehensweise (CMake/CTest):

Sie können folgende Befehle nutzen, um einzelne oder alle Tests mit Ihrer Implementierung zu kompilieren und auszuführen:

```
cd path/to/my/project
cmake -S . -B build    # configure build (into build folder)
cd build               # change to build folder
make                   # try to build all targets
make test_linspace     # try to build single target
ctest                  # run all tests
./test/test_linspace   # run single test as regular executable  
```

**Hinweis1:** Alle mitgelieferten Tests schlagen ohne Ihre Implementierenungen fehl: alle Funktionen liefern NULL-Zeiger zurück, was beim ersten Zugriff zu einer Speicherzugriffsverletzung führt.

**Hinweis2:** Starten Sie jedenfalls mit der Implementierung von `num_linspace` und danach `num_sample`, da alle anderen Tests von diesen zwei Funktionen Gebrauch machen.

-------

# Aufgabenstellung/Anforderungen

Die 5 von Ihnen zu implementierenden Funktionen haben folgende Deklarationen:

```cpp
struct Vector *num_linspace(double start, double stop, size_t n);
struct Vector *num_sample(const struct Vector *x, double (*func)(double));
struct Vector *num_interpolate(const struct Vector *xinterp, const struct Vector *x,
                          const struct Vector *f);
struct Vector *num_grad(const struct Vector *x, const struct Vector *f);
double num_integrate(const struct Vector *x, const struct Vector *f);
```

## Allgemeines 

- Alle 5 Funktionen geben einen Zeiger auf ein dynamisch alloziertes Vector-Objekt zurück (Hinweis: `vector_new`).
- Der Aufrufende wird alleiniger Besitzer dieses dynamischen Speichers und übernimmt somit auch die Pflicht des Freigebens (Hinweis: `vector_delete`).

## `num_linspace`: Dynamisches Vector-Object mit äquidistanten Werten erzeugen (2 Puntke)
```c
struct Vector *num_linspace(double start, double stop, size_t n);
```
Funktionsbeschreibung: Initialisiert ein dynamisch alloziertes Vector-Object mit `n` äquidistanten Werten verteilt über das Intervall `[start, stop]`. 

Rückgabewert: Zeiger auf das dynamisch allozierte Vector-Objekt.

Annahmen: `n` > 1

## `num_sample`: Funktion an diskreten Stellen abtasten (2 Puntke)
```c
struct Vector *num_sample(const struct Vector *x, double (*func)(double));
```
Funktionsbeschreibung: Evaluiert eine übergebene 1D-Funktion an den durch den übergebenen Vector definierten Werten und speichert die Funktionswerte in ein dynamisch alloziertes Vector-Object.

Rückgabewert: Zeiger auf das dynamisch allozierte Vector-Objekt.

## `num_interpolate`: Funktionswerte interpolieren (2 Puntke)
```c
struct Vector *num_interpolate(const struct Vector *xinterp, const struct Vector *x,
                          const struct Vector *f);
```
Funktionsbeschreibung: Interpoliert 1D-Funktionswerte an den übergebenen Stellen (`xinterp`) linear mittels ebenfalls übergebener diskreter Funktionswertepaare (`x`, `f`) und speichert die interpolierten Funktionswerte in ein dynamisch alloziertes Vector-Objekt. Zu interpolierende Werte ausserhalb des durch `x` vorgegebenen Intervalls nehmen den ensprechenden Randwert an.

Rückgabewert: Zeiger auf das dynamisch allozierte Vector-Objekt.

Annahmen: 

- Die x-Koordinaten im übergebenen Vector `x` sind monoton aufsteigend.  
- Die Vectoren `x` und `f` enthalten dieselbe Anzahl an Elementen.

## `num_grad`: Numerische Ableitung/Gradient (2 Puntke)
```c
struct Vector *num_grad(const struct Vector *x, const struct Vector *f);
```
Funktionsbeschreibung: Berechnet den numerischen Gradienten für alle übergebenen Funktionswerte mit folgender Approximation:
  - Für den unteren Rand wird der Vorwärts-Differenzenquotient verwendet: 
    ```math
    grad_{i=0} =  (f(x_{i+1}) - f(x_{i})) / (x_{i+1} - x_{i})
    ```
  - Für den oberen Rand wird der Rückwärts-Differenzenquotient verwendet: 
    ```math
    grad_{i=size-1} =  (f(x_{i}) - f(x_{i-1})) / (x_{i} - x_{i-1})
    ```
  - Für alle anderen Werte dazwischen wird der Zentrale-Differenzenquotient verwendet: 
    ```math
    grad_{i} =  (f(x_{i+1}) - f(x_{i-1})) / (x_{i+1} - x_{i-1})
    ```           

Rückgabewert:

- Zeiger auf das dynamisch allozierte Vector-Objekt.

Annahmen: 

- Die x-Koordinaten im übergebenen Vector `x` sind monoton aufsteigend. 
- Die Vectoren `x` und `f` enthalten die dieselbe Anzahl an Elementen.
- Der Vector `x` enthält mindestens 2 Elemente.

Hinweis: Die vorgegebene numerische Approximation geht von annähernd äquidistanten x-Koordinaten aus. 

## `num_integrate`: Numerische Integration (2 Punkte)
```c
double num_integrate(const struct Vector *x, const struct Vector *f);
```
Funktionsbeschreibung: Berechnet mittels der übergebenen Wertepaare einer 1D-Funktion (`x` `f`) das Integral für das Intervall der übergebenen x-Koordinaten mit der summierten Trapezregel.

```math
\int_{x_{i}}^{x_{i+1}} f(x) dx \approx (x_{i+1} - x_{i})  \cdot  (f(x_{i}) + f(x_{i+1})) / 2 
```           

Das bestimmte Integral, mit den x-Koordinaten des übergebenen Vectors als Integrationsgrenzen, ergibt sich aus der Summe aller nach obiger Formel berechneter Teilintegrale.

Rückgabewert:

- numerisches Integral

Annahmen: 

- Die x-Koordinaten im übergebenen Vector `x` sind monoton aufsteigend. 
- Die Vectoren `x` und `f` enthalten die gleiche Anzahl an Elementen.
- Der Vector `x` enthält mindestens 2 Elemente.

---

# Appendix: Vector-Datenstruktur

Wichtig: Sie sollen keinerlei Anpassung an der Vector-Datenstruktur vornehmen, sondern einzig die 5 oben beschriebenen Funktionen unter Zuhilfenahme **existierender Funktionalität** der Vector-Datenstruktur implementieren.


Hinweis: Mit folgender Option können Sie die Tests für den Vector ebenfalls aktivieren/deaktivieren:

```
cd path/to/my/project
cmake -S . -B build         # configure build (into build folder)
cd build
cmake -D TEST_VECTOR=ON ..  # enable tests for Vector
make
ctest 
```

## `struct Vector`: Allgemeines 

Die Datenstruktur `struct Vector` (im Folgenden *Vector*) und die zugehörigen Funktionen implementieren ein dynamisch alloziertes Array. 
`data` enthält das eigentliche Feld von `double` Werten, in `size` steht dessen aktuelle Anzahl an aktiven Elementen und in `cap` dessen momentane Kapazität an Elementen. Die aktuelle Kapazität ist mindestens so groß wie `size`, kann aber auch größer sein: dies ermöglicht es dem Vector, neue Elemente ohne ständige Reallokation einzufügen.

```cpp
struct Vector
{
  double *data;     // invariant: points to first element 
  size_t size;      // invariant: current number of elements
  size_t cap;       // invariant: current capacity
};
```

Zur Benutzung der Datenstruktur Vector stehen bereits implementierte Funktionen bereit, die weitestgehend identisch zu den von Ihnen in Hausübung 1 implementierten Funktionen sind. Hervorzuheben sind vier neu dazugekommene Funktionen:


## `vector_new`: Dynamisches Vector-Objekt erzeugen
```c
struct Vector *vector_new();
```
Funktionsbeschreibung: Alloziert ein `struct Vector`-Objekt, initialisert es (leer) und gibt einen Zeiger darauf zurück.

Rückgabewert:

- Zeiger auf einen dynamisch allozierten Vector.
- Der Aufrufende wird alleiniger Besitzer des dynamischen Speichers (und übernimmt somit auch die Pflicht des Freigebens (Hinweis: `vector_delete`).

## `vector_delete`: Dynamisches Vector-Objekt freigeben
```c
void vector_delete(struct Vector **self);
```
Funktionsbeschreibung: Dealloziert ein per doppelter Referenz übergebenes alloziertes `struct Vector`-Objekt, gibt zuvor den vom Vector selbst gehaltenen dynamischen Speicher frei und setzt den Zeiger auf den Vector auf `NULL`.

Parameter:

- `self`: Zeiger auf einen Zeiger auf einen dynamisch allozierten Vector (Doppelzeiger).

## `vector_reserve`: Kapazität reservieren
```c
void vector_reserve(struct Vector *self, size_t cap);
```
Funktionsbeschreibung: Erweitert die Kapazität eines übergebenen `struct Vector`-Objekts auf einen Wert **mindestens so groß** wie der ebenfalls übergebenen Wert, falls die aktuelle Kapazität kleiner als der übergebene Wert ist. Die aktiven Elemente bleiben erhalten. Falls der übergebene Wert kleiner als die momentane Kapatität ist findet keine Kapazitätsanpassung statt.

Parameter:

- `self`: Zeiger auf den Vector. 
- `cap`: angeforderte Kapazität.

## `vector_shrink`: Kapazität freigeben
```c
void vector_shrink(struct Vector *self);
```
Funktionsbeschreibung: Reduziert die Kapazität eines übergebenen `struct Vector`-Objekts auf die für die aktiven Elemente benötigte Größe. Die Werte der aktiven Elemente bleiben erhalten.

Parameter:

- `self`: Zeiger auf den Vector.

-------
