Proiectul reprezinta un sistem de pariuri sportive realizat in C++ care calculeaza castigurile sau pierderile dupa punerea pariurilor.
Algoritmul citeste din fisier date despre meciuri si cote, apoi permite utilizatorului sa isi creeze pariuri pe baza acestora si a rezultatelor introduse.
Exista mai multe tipuri de pariuri, unul simplu, unul multiplu si unul de tip sistem, fiecare avand o logica diferita de calcul al castigului.
Datele despre rezultate sunt stocate intr-o clasa separata aflata in header, iar restul logicii este impartita in fisiere sursa si headere.
Structura proiectului este impartita in fisiere pentru pariuri, rezultate, exceptii si programul principal, iar comunicarea dintre ele se face prin obiecte si functii ale claselor.
Exista o clasa de baza pentru pariuri din care deriva cele trei tipuri de pariuri, iar toate folosesc aceleasi functii de baza dar cu implementari diferite.
Fiecare pariu poate contine unul sau mai multe meciuri, iar fiecare meci are actiuni precum rezultatul final, numarul de faulturi, cartonase galbene,
cartonase rosii sau cornere, in functie de ce alege utilizatorul.
In program se foloseste polimorfism, adica se lucreaza cu pointeri la clasa de baza pentru a putea trata toate tipurile de pariuri la fel, dar cu comportament diferit.
Obiectele sunt create dinamic si stocate intr-un vector, iar fiecare clasa are si o functie de copiere pentru a putea fi gestionate corect.
Sunt folosite si structuri STL precum vector, map si string pentru a tine evidenta meciurilor, cotelor si pariurilor.
Exista si un sistem de exceptii propriu pentru a trata situatii precum introducerea unor date gresite, erori la citirea fisierului sau incercarea de a paria cand utilizatorul nu are varsta minima.
Aceste exceptii sunt folosite in program pentru a opri executia atunci cand apar probleme.
Programul citeste datele din fisier, apoi utilizatorul introduce numele, varsta, suma pe care vrea sa o parieze si numarul de pariuri.
In functie de alegeri, sunt create obiecte diferite care sunt stocate si procesate ulterior.
Proiectul este gandit astfel incat sa poata fi extins usor, adica se pot adauga noi tipuri de pariuri fara sa se modifice codul existent, doar prin adaugarea unei noi clase derivate


REVIEW TEMA 2, AM ALES SA IL FAC COLEGULUI MEU DE GRUPA, GRUPA 133, TANASE ALEX-COSTIN.

