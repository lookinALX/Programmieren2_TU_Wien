# Hausübung 4 (Abgabe via TUWEL bis 9. Jänner 2023 10:00 Uhr)

In dieser Hausübung ist es Ihre Aufgabe, eine *Hashtabelle* (in folgendem *Tabelle*) mit Kollisionsbehandlung (durch einfach verkettete Listen) zu entwickeln. Die Struktur (`struct Hashtable`) und die Signatur/Beschreibung der zugehörigen Funktionen ist bereits vorgegeben (`include/Hashtable.h` und `src/Hashtable.c`). Des Weiteren finden Sie wie gewohnt Tests für die von Ihnen zu implementierenden Funktionen (Ordner `test_hashtable`).

In `include/Cache.h`/`src/Cache.c` steht Ihnen als Referenz die Implementierung eine Hashtabelle **ohne Kollisionsbehandlung** (*Cache*) zur Verfügung. Die Signaturen und die Funktionalität der Schnittstellenfunktionen sind (bis auf das Fehlen der Kollisionsbehandlung) identisch mit den von Ihnen in `src/Hashtable.c` zu implementierenden Funktionen.

## Vergleich zwischen *Cache* und *Tabelle*:
Im *Cache* stehen die einzelnen Werte direkt von im Typ des Feldes `struct CacheEntry` gehalten. Ob eine Stelle im Feld besetzt ist oder nicht, gibt das `empty`-Flag an.
Im der *Tabelle* stehen die Werte denen ein identischer Hashwert zugeordnet wird in einer in `struct HashTableEntry` hinterlegten Liste. Der Zeiger `list=NULL` gibt an, dass es noch keine Eintraege für diesen Hashwert vorhanden sind.

**Hinweis**: Zur Abgabe laden sie einzig die Datei `src/Hashtable.c` nach TUWEL hoch. (Sie können jedoch während des Entwicklunsprozesses lokal jederzeit auch andere Dateien anpassen; diese Anpassungen werden bei der Bewertung jedoch naturgemäß nicht berücksichtigt).

Folgender Verzeichnisbaum gibt einen Überblick über die Projektstruktur:

```
├── CMakeLists.txt                      Root CMake-Configuration
├── include
│   ├── Book.h                          Typ der im Cache/Hashtable gespeichert wird
│   ├── Cache.h                         Cache (ohne Kollisionsbehandlung)
│   ├── Hashes.h                        Allgemeine Hashfunktionen
│   ├── HashTable.h                     Hashtabelle (mit Kollisionbehandlung)
│   └── Logger.h                        Konsolen Logger
├── src
│   ├── Book.c                          
│   ├── Cache.c                         --> Referenzimplementierung
│   ├── HashTable.c                     --> Implementierung Hausübung
│   └── Logger.c
├── test_cache                          Tests für "Cache"
│   ├── [...]
├── test_hashtable                      Tests für "Hashtable"
│   ├── [...]
└── example
    ├── CMakeLists.txt  
    ├── main_cache.c                    Beispielprogramm "Cache"
    ├── main_hashtable.c                Beispielprogramm "Hashtable"
    └── programming_books_100.txt       Input Datei
```


## Konfigurieren und Ausführen

Für die Referenzimplementierung *Cache* ist alles implementiert und Sie können direkt alle Tests bauen und ausführen:
```
cd src/to/homework4
cmake -S . -B build
cd build/test_cache
make
ctest
./test_cache_insert
```

Analog können Sie für die von Ihnen zu Implementierende Tabelle vorgehen:

```
cd src/to/homework4
cmake -S . -B build
cd build/test_hashtable
make
ctest
./test_hashtable_insert
```

Es stehen ebenso zwei Beispielprogramme zur Verfügung die aus einer Datei Datenstätze lesen und in die jeweilige Datenstuktur einfügen:

```
cd src/to/homework4
cmake -S . -B build
cd build/example
make main_cache
./main_cache programming_books_100.txt
make main_hashtable
./main_hashtable programming_books_100.txt
```


## Hashtabelle mit Kollisionsbehandlung (*Hashtable*)

Die an der Datenstrukture beteiligten Stukturen sehen so aus:

```c
typedef struct Book T; // stored type

struct Node
{
  struct Node *next; // next node in list (or NULL if last node in list)
  T value;           // stored value
};

struct HashTableEntry
{
  struct Node *list; // first node in list (or NULL if list is empty)
};

struct HashTable
{
  struct HashTableEntry *data;    // array indexed by the hashed value
  size_t size;                    // size of the array
  size_t count;                   // number of aktive entries
  float max_load_factor;          // maximum load factor (count/size)
  size_t (*hash)(const T *value); // hash function for entries/keys
  bool (*compare)(const T *value1,
                  const T *value2); // compare function for entries/keys
};
```

Die von Ihnen zu entwickelnden Funktionen sind:

### `hashtable_new`: Dynamisches Tabellen-Objekt erzeugen (1 Punkt)
```c
struct HashTable *hashtable_new(size_t size, float max_load_factor,
                   size_t (*hash)(const T *value),
                   bool (*compare)(const T *value1, const T *value2));
```
Funktionsbeschreibung: Alloziert ein `struct HashTable`-Objekt, initialisert es und gibt einen Zeiger darauf zurück.

Parameter 

- `size`: Initiale Feldgröße
- `max_load_factor`: Maximales Verhältnis von Einträgen zur Feldgröße (Standardwert `0.75`)
- `hash`: Funktionszeiger auf die Funktion, die zum Generieren eines Hashes verwendet wird.
- `compare:` Funktionszeiger auf die Funktion, die zum Vergleichen zweier Werte verwendet wird.

Rückgabewert: Zeiger auf das dynamisch allozierte Objekt.

### `hashtable_delete`: Dynamisches Vector-Objekt freigeben (1 Punkt)
```c
void hashtable_delete(struct Vector **self);
```
Funktionsbeschreibung: Dealloziert ein per doppelter Referenz übergebenes alloziertes `struct HashTable`-Objekt, gibt zuvor den durch die Tabelle selbst gehaltenen dynamischen Speicher frei und setzt den Zeiger auf die Tabelle auf `NULL`.

Parameter:

- `self`: Zeiger auf einen Zeiger auf eine dynamisch allozierte Tabelle (Doppelzeiger).

### `hashtable_clear`:  Alle Einträge entfernen (1 Punkt)
```c
void hashtable_clear(struct HashTable *self);
```
Funktionsbeschreibung: Entfernt alle Einträge aus der Tabelle.

Parameter:

- `self`: Zeiger auf eine dynamisch allozierte Tabelle.

### `hashtable_resize`: Feldgröße anpassen (2 Punkte)
```c
void hashtable_resize(struct HashTable *self, size_t size);
```
Funktionsbeschreibung: Ändert die Feldgröße auf den übergebenen Wert ab. 

Hinweis: Bedenken sie, dass Sie den Hashwert für aller hinterlegten Einträge neu berechnen müssen.

Parameter:

- `self`: Zeiger auf eine dynamisch allozierte Tabelle.
- `size`: neue Feldgröße fuer `data`.

### `hashtable_insert`: Eintrag einfügen (2 Punkte)
```c
bool hashtable_insert(struct HashTable *self, const T *value);
```
Funktionsbeschreibung: Fügt den übergebenen Wert in die Tabelle ein. Zum Berechnen des Hashes wird die Funktion `hash` verwendet. 
Um zu überprüfen ob der dem einzufügenden Wert zugeordnete Schlüssel bereits vorhanden ist, wird die Funktion `compare` verwendet.
Ist der Schlüssel schon in der Tabelle vorhanden wird die Tabelle nicht verändert.

Falls beim Einritt in die Funktion der Befüllungsgrad größer dem durch `max_load_factor` gegebenen Wert liegt, wird unmittelbar mittels der Funktion `hashtable_resize` die aktuelle Feldgröße mit dem Faktor `2.0`.

Parameter:

- `self`: Zeiger auf eine dynamisch allozierte Tabelle.
- `value`: Zeiger auf den einzufügenden Wert (Wertepaar).

Rückgabewert: `false` falls der Wert bereits vorhanden war, und `true` falls übergebene der Wert eingetragen wurde.

### `hashtable_find`: Eintrag finden (1 Punkt)
```c
T *hashtable_find(struct HashTable *self, const T *value);
```
Funktionsbeschreibung: Sucht nach dem übergebenen Wert (genauer: nach dem zugeordneten Schlüssel) in der Tabelle. Zum Berechnen des Hashes wird die Funktion `hash` verwendet. 
Um zu überprüfen ob ein Eintrag dem gesuchten Wert entspricht, wird die Funktion `compare` verwendet.
Wird ein passender Eintrag gefunden, gibt die Funktionen einen Zeiger auf diesen zurück.

Parameter:

- `self`: Zeiger auf eine dynamisch allozierte Tabelle.
- `value`: Zeiger auf den einzufügenden Wert (Wertepaar).

Rückgabewert: Zeiger auf den gefundenen Wert, oder `NULL` falls der gesuchte Wert nicht in der Tabelle vorhanden ist.

### `hashtable_erase`: Eintrag entfernen (2 Punkte)
```c
bool hashtable_erase(struct HashTable *self, const T *value);
```
Funktionsbeschreibung: Sucht nach dem übergebenen Wert in der Tabelle. Wird ein passender Eintrag gefunden wird der Eintrag entfernt. Zum Berechnen des Hashes wird die bei der Konstruktion (`hashtable_new`) übergebene Funktion `hash` verwendet. Um zu überprüfen ob ein Schlüssel dem gesuchten Wert enspricht, wird die Funktion `compare` verwendet.

Parameter:

- `self`: Zeiger auf eine dynamisch allozierte Tabelle.
- `value`: Zeiger auf den einzufügenden Wert (Wertepaar).

Rückgabewert: `true`, falls der Wert gefunden und entfernt wurde und `false` falls der Wert nicht vorhanden war. 

## Referenzimplementierung: Hashtabelle ohne Kollisionsbehandlung (*Cache*)

Ihnen steht eine vollständige Referenzimplementierung `struct Cache` (`include/Cache.h` und `src/Cache.c`) einer Hashtabelle (*Cache*) **ohne Kollisionsbehandlung** zur Verfügung. Die Implementierung unterscheidet sich von der oben beschriebenen Funktionalität insofern, dass keine Kollisionen unterstützt werden: falls der Hashwert eines einzutragenden Werts mit dem Hashwert eines bereits existierenden Wertes kollidiert wird der existierende Wert überschrieben: beachten Sie die hier die Beschreibung zu `cache_insert` (siehe unten).
Die sonstigen Signaturen/Beschreibungen der zughehörigen Funktionen sind identisch (der Präfix ist `cache_` statt `hashtable_`) mit den von Ihnen für `struct Hashtable` zu implementierenden Funktionen.


```c
typedef struct Book T; // stored type

struct CacheEntry
{
  bool empty; // flag indicating if value is active
  T value;    // stored value
};

struct Cache
{
  struct CacheEntry *data;        // array indexed by the hashed value
  size_t size;                    // size of the array
  size_t count;                   // number of active entries
  float max_load_factor;          // maximum load factor (count/size)
  size_t (*hash)(const T *value); // hash function
  bool (*compare)(const T *value1,
                  const T *value2); // compare function
};
```

## `cache_insert`: Wertepaar einfügen 
```c
bool cache_insert(struct Cache *self, const T *value);
```
Funktionsbeschreibung: Fügt den übergebenen Wert in die Tabelle ein; **falls schon ein Eintrag für den Hashwert vorhanden ist wird der dort hinterlegte Wert mit dem übergebenen Wert überschrieben**. 
Zum Berechnen des Hashes wird die bei der Konstruktion (`cache_new`) übergebene Funktion `hash` verwendet. 

Falls beim Einritt in die Funktion der Befüllungsgrad größer dem durch `max_load_factor` gegebenen Wert liegt, wird unmittelbar mittels der Funktion `cache_resize` die aktuelle Feldgröße mit dem Faktor `2.0` multipliziert.

Parameter:

- `self`: Zeiger auf eine dynamisch allozierte Tabelle.
- `value`: Zeiger auf den einzufügenden Wert (Wertepaar).

Rückgabewert: `false` **falls für den Hashwert bereits ein Wert hinterlegt war und überschrieben wurde**, und `true` falls für den Hashwert noch kein Eintrag vorhanden war und dieser angelegt wurde.

