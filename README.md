# **Devoirs en Langage C**

Voici un ensemble de programmes réalisés en langage C pour répondre à plusieurs problématiques, dans le cadre de devoirs. Chaque programme est détaillé avec ses fonctionnalités, les options disponibles, et des exemples d'exécution.


---

## **Exercice 1 : Calcul et Composition de Fonctions**

### **Description**
Ce programme calcule les fonctions suivantes en fonction des arguments donnés :  
- **f(n) = 2^n**
- **g(n) = 2 * n**

Il permet aussi de composer ces fonctions dans l'ordre souhaité :  
- **fog(n) = f(g(n))**
- **gof(n) = g(f(n))**

### **Options**
- `-f entier` : Calcule \( 2^n \) avec un entier \( n \).
- `-g entier` : Calcule \( 2 \times n \) avec un entier \( n \).
- Si les deux options sont utilisées ensemble, le programme calcule la composition de fonctions selon l'ordre des options.

### **Exemples**
```bash
# Calcul de 2^3
./prog -f 3

# Calcul de 2 * 3
./prog -g 3

# Calcul de fog(3) = 2^(2*3)
./prog -f 3 -g

# Calcul de gof(3) = 2*(2^3)
./prog -g 3 -f
```
 
## **Exercice 2 : Sauvegarde et Lecture de Matrices**

### **Description**

Ce programme permet de gérer des matrices carrées au format **binaire** ou **texte**. Vous pouvez créer une matrice aléatoire, la sauvegarder dans un fichier, et afficher son contenu.

### **Options**

*   `-c` : Crée une matrice aléatoire.
*   `-a` : Affiche le contenu du fichier.
*   `-d entier` : Spécifie la dimension de la matrice (exemple : `-d 10` pour une matrice \( 10 \times 10 \)).
*   `-b` : Sauvegarde au format **binaire** (par défaut).
*   `-t` : Sauvegarde au format **texte**.
*   `-f nomfichier` : Spécifie le nom du fichier à lire ou écrire.

### **Exemples**

```bash
# Création d'une matrice 10x10 sauvegardée en binaire
./matrix -c -d 10 -f fichiermatrice.bin

# Création d'une matrice 10x10 sauvegardée en texte
./matrix -c -d 10 -f fichiermatrice.txt -t

# Affichage d'une matrice en binaire
./matrix -a -d 10 -f fichiermatrice.bin

# Affichage d'une matrice en texte
./matrix -a -d 10 -f fichiermatrice.txt -t
```

## **Exercice 3 : Split et Join de Fichiers**

### **Description**

Ce programme permet de découper un fichier en plusieurs morceaux avec une taille donnée, puis de reconstituer le fichier original à partir des morceaux.

### **Commandes**

#### **Split and Join **
permet de découper un fichier en plusieurs morceaux avec une taille donnée `split` , puis de reconstituer le fichier original à partir des morceaux `join`.

#### **Join**

```bash
./split nomfichier taille
./join nomfichier part1 part2 part3 ...
```
## **Exercice 4 : Threads avec Sémaphores**

### **Description**

Ce programme utilise deux threads pour effectuer des incréments et des décréments synchronisés grâce à des sémaphores.  
- Le **Thread 1** incrémente une valeur de 1 à \( +n \).  
- Le **Thread 2** décrémente cette valeur de 0 à \( -n \).  

Le résultat est une séquence oscillant entre \( -n \) et \( +n \).

### **Exécution**

```bash
./thread_prog n
```
## **Exercice 5 : Exécution Linéaire de Threads**

### **Description**

Ce programme exécute \( n \) threads dans un ordre linéaire et cyclique :  
**Thread1, Thread2, ..., Threadn, Thread1, ...**

Chaque thread affiche un message pour indiquer son exécution.

### **Exécution**

```bash
./thread_order n
