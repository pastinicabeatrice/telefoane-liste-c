# Telefoane - vector și listă

Telefoane citite din fișier într-un vector, apoi mutate într-o listă simplu înlănțuită.

## Funcționalități

- citirea telefoanelor din `fisier.txt` într-un vector
- inserarea în listă, inclusiv inserare sortată după preț
- prețul mediu
- afișarea telefoanelor cu memorie RAM peste un minim dat
- dezalocarea vectorului și a listei

## Structura de date

`Telefon`: memorie RAM, producător, preț.

## Rulare

```
gcc main.c -o telefoane
./telefoane
```

Fișierul `fisier.txt` trebuie să fie în directorul de lucru.
