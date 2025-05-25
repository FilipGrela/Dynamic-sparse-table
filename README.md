# Dynamiczna Tablica Rzadka

Implementacja drzewa typu „trie” do przechowywania wartości indeksowanych rzadko występującymi kluczami z uniwersum N, zapewniająca ograniczony czas dostępu w najgorszym przypadku.

---

## Opis

Dla kluczy rozłożonych rzadko na dużym zakresie standardowe tablice haszowane mogą mieć nieprzewidywalne czasy dostępu w najgorszym przypadku. Rozwiązaniem jest użycie dwupoziomowego drzewa:

1. **Poziom 0 (korzeń)**: ma **n** węzłów potomnych.
2. **Poziom 1**: każdy z tych węzłów ma **k** węzłów potomnych.

Każdy węzeł może przechować co najwyżej jeden klucz (i opcjonalnie wartość — tutaj tylko klucz). Operacje:

* **Wstawianie (`I x`)**: Zaczynamy od korzenia. Jeśli jest wolny, zapisujemy `x` i kończymy. W przeciwnym razie obliczamy kolejno `div = x mod n`, wybieramy odpowiednie dziecko, potem `div = div mod k` i schodzimy niżej, aż znajdziemy pusty węzeł.
* **Wyszukiwanie (`L x`)**: Analogicznie przechodzimy od korzenia, używając `mod n` i `mod k`, aż znajdziemy `x` lub napotkamy pusty węzeł.
* **Usuwanie (`D x`)**: Lokalizujemy węzeł zawierający `x`. Jeśli ma potomków, szukamy najbardziej lewego węzła zewnętrznego (liścia), kopiujemy jego klucz do usuwanego węzła i usuwamy liść. Jeśli nie ma potomków, po prostu czyścimy węzeł.
* **Wypisywanie (`P`)**: Wypisujemy wszystkie klucze w kolejności inorder (lewy, węzeł, prawy).

## Parametry struktury

* **n**: liczba dzieci korzenia
* **k**: liczba dzieci każdego węzła z poziomu 1

## Komendy

* `I x` — wstawia klucz `x`; jeśli już istnieje, wypisuje:

  ```
  x exist
  ```
* `L x` — sprawdza obecność `x`; wypisuje albo:

  ```
  x exist
  ```

  albo

  ```
  x not exist
  ```
* `D x` — usuwa `x`; jeśli brak klucza, wypisuje:

  ```
  x not exist
  ```
* `P` — wypisuje wszystkie klucze w kolejności inorder, oddzielone spacjami i zakończone spacją.

## Format wejścia

1. Liczba testów **t** (komend).
2. Dwie liczby: **min** i **max** — zakres możliwych kluczy.
3. Dwie liczby: **n** i **k** — parametry drzewa.
4. Pusta linia.
5. **t** wierszy z komendami (`I x`, `L x`, `D x` lub `P`).

## Format wyjścia

Wyniki komend drukowane w kolejności ich wykonania. Operacje zakończone sukcesem bez dodatkowej informacji (`I` lub `D`) nie generują linii.

## Przykład

**Wejście:**

```text
29
0 511
8 4

I 3
I 31
I 150
I 190
I 130
I 174
I 81
I 30
I 203
P
L 32
L 30
L 150
D 150
L 150
I 150
L 150
D 3
L 3
I 3
L 3
D 3
L 3
D 30
L 30
I 30
L 30
D 30
L 30
```

**Wyjście:**

```text
3 81 130 203 150 174 190 30 31 
32 not exist
30 exist
150 exist
150 not exist
150 exist
3 not exist
3 exist
3 not exist
30 not exist
30 exist
30 not exist
```

## Źródła

* [Storing a Sparse Table](https://example.com/storing-a-sparse-table)
