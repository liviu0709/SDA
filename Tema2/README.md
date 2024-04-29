# Tema 2 SDA

## Cerinta 1

Construim arborele de sufixe si afisam parcurgerea in latime, folosind:
### Parcurgerea in latime
### Procesarea unui cuvant (adaugarea '$' la sfarsit si generare sufixe)
### Introducere sufix arbore

## Cerinta 2

Construim arborele de sufixe in mod analog.
Ne folosim de cate o functie pentru fiecare statistica ceruta:
### Nr noduri frunza

Calculam numarul nodurilor cu 0 fii.

### Nr sufixe de dimensiune k

Apelam recursiv functia nrSufixe in adancime. La fiecare apel dimensiunea sufixului scade. Cand ajunge la 0, verificam daca nodul are fiul '$'. Daca il are, am gasit un sufix.

### Numar maxim descendenti directi

Apelam recursiv o functie care returneaza numarul maxim de fii dintr un arbore.

## Cerinta 3

Construim arborele de sufixe in mod analog.
Apelam o functie la fiecare sufix, pentru a verifica daca se afla in arbore.<br>
Functia cautaSufArbFull adauga la sufix caracterul $ si apeleaza functia cautaSufArb pentru fiecare fiu al radacinii. Comparam prima litera din sir cu cea din nod. Daca sunt egale, apelam recursiv functia pentru urmatoarea litera din sir si urmatoarele nod. Daca ajungem la finalul sirului, am gasit sufixul. <br>Daca nu sunt egale => conditie oprire



## Cerinta 4

Construim arborele de sufixe in mod analog. Apelam functia de compresie a arborelui si parcurgerea in latime. <br>
### Functia de compresie
* Este implementata recursiv. <br>
* Pentru a putea efectua compresia, nodul trebuie sa aiba un singur fiu. In plus, nodurile cu '$' nu trebuie comprimate. <br>
* Cand aceste conditii sunt indeplinite, se concateneaza sirul din nodul fiu in cel curent. Se modifica legaturile nodului curent cu cele ale fiului. Nodul fiu este sters. <br>
* Se apeleaza functia pentru nodurile copii ale nodului curent.