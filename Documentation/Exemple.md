# Classe d'Exemple

Description de la classe et de ce qu'elle fait.

---

## Attributs

- **AttributType**:`type` -> Description de cet attribut
- **AttributExemple**:`String` -> Sert à faire un exemple
- **AttributStatic**:`int` _(static)_ -> On peut rajouter des spécifications (static), (private), etc... dans la définition de l'attribut

---

## Méthodes

- [**méthodeType**](#méthodeType):`type retour` | `arg1:type1`, `arg2:type2` -> Description résumé de cette Méthode
- [**méthodeExemple**](#méthodeExemple): _(static)_ `int` | `x:int`, `y:int` -> Somme x et y, pour faire un exemple
- [**méthodeAvecSurcharge**](#méthodeAvecSurcharge): `int` | `x:int`  
.......................................... `float` | `y:float` ------>  Méthode avec surcharge; Les points sont là pour que les types de retours soient alignés dans la vue markdown.  
.......................................... `int` | `x:int`, `y:int` 

---

### méthodeType
**Retourne** : `type retour`  

**Arguments** : 
- arg1:`type1` -> Description Arg1
- arg2:`type2` -> Description Arg2

**Description:**  
Explication de la fonction

**Exemples:**
```cpp
méthodeType(1, "test") = 6;
```
% Cette section est optionelle %

### méthodeExemple
_Static_   

**Retourne** : `int`  

**Arguments** :
- x:`int` -> Le premier nombre
- y:`int` -> Le deuxième nomrbe

**Description:**  
Calcule et retourne la somme des nombres entiers x et y.
Si x et y sont égaux, il retourne 0.

**Exemples:**
```cpp
méthodeExemple(1, 2) = 3;
méthodeExemple(1, 1) = 0;
```

### méthodeAvecSurcharge

**Retourne** : `int`  

**Arguments** :  

Surcharge 1:
- x:`int` -> Le nombre utilisé (entier)

Surcharge 2:
- y:`float` -> Le nombre utilisé (non entier)

Surcharge 3:
- x:`int` -> Le premier nombre
- y:`int` -> Le deuxième nomrbe

**Description:**  
Fait pleins de choses avec pleins de surcharges différentes !!!

