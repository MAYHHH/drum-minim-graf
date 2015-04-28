# Introducere #

Acest algoritm determina drumurile de valoare minima dintre toate perechile de varfuri ale unui graf orientat G=(V,E) valorizat. Nu se inpun restrictii ale arcelor, ci doar a structurii grafului. Graful nu trebuie sa contina cicluri cu cost negativ. Algoritmul este in categoria algoritmilor de programare dinamica. Dupa o singura executie a algoritmului vor fi calculate toate drumurile minime dintre toate perechile de noduri.
<br />

# Construirea matricilor #

## Matricea drumurilor optime ##

d<sub>i</sub><sub>j</sub> ia valoarea:
  * d(v<sub>i</sub>,v<sub>j</sub>), daca (v<sub>i</sub>,v<sub>j</sub>) ∈ E si i!=j
  * 0, daca i=j
  * ∞, in rest

## Matricea predecesorilor ##

p<sub>i</sub><sub>j</sub> ia valoarea:
  * ∅, daca i=j sau v<sub>i</sub><sub>j</sub>=∞
  * i, daca i!=j si v<sub>i</sub><sub>j</sub><∞
<br />

# Cod #
```
for(k=1; k<=n; k++)
   for(i=1; i<=n; i++)
      for(j=1; j<=n; j++)
         if(d[i][j]>d[i][k]+d[k][j]
         {
            d[i][j]=d[i][k]+d[k][j];
            p[i][j]=p[k][j];
         }
```
<br />

# Complexitate #
| **Cel mai rau caz** | Timp | **O(|V|<sup>3</sup>)** |
|:--------------------|:-----|:-----------------------|
| **Cel mai bun caz** | Timp | **Ω(|V|<sup>3</sup>)** |
| **Cel mai rau caz** | Memorie | **Θ(|V|<sup>2</sup>)** |