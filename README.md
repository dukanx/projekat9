DOBRO DOSLI U MOJU GREP FUNKCIJU   :)


--Objasnimo za sta sluzi ova funckija:

Svrha ove komande je da iz tekstualnog fajla izvucemo linije teksta u kojima se nalazi rec ili recenica koju smo pretrazili.
Postoji vise opcija koje mozemo da odaberemo i personalizujemo izlaz komande.



--Kako koristiti funkciju:

Prvo napravimo tekstualni fajl sa linijama teksta(max 250 karaktera po liniji) u istom folderu u kom je projekat iz kog cemo izvlaciti linije.

Kada se prebacimo u lokaciju projekta u terminalu potrebno je u  napisati "make" koji ce nam napraviti izvrsni program pod nazivom grep.

Nakon toga treba upisati komandu u ovom formatu:

          ./grep [OPCIJE] OBRAZAC [FAJL...]

OPCIJE koje mozemo dati krecu sa "-" i onda slovom za komandu koju hocemo:

  -h     Prikazuje pomocnu poruku
  -v     Invertuje rezultate podudaranja(ispisuje sve linije koje ne sadrze match)
  -i     Ignorise razlike izmedju velikih i malih slova
  -c     Ispisuje samo broj linija koje sadrze match
  -m NUM Zaustavi se posle NUM odabranih linija(pise se u terminalu "./grep [OPCIJE] NUM OBRAZAC [FAJL...]")
  -n     Ispisuje broj linije uz izlazne linije
  -w     Podudara samo cele reci
  -x     Podudara samo cele linije


OBRAZAC je rec ili recenica pomocu koje trazimo linije koje je sadrze(recenica ili vise reci se moraju pisati pod navodnicima)

FAJL predstavlja tekstualni fajl iz kog izvlacimo linije(mozemo navoditi vise fajlova iz kojih zelimo da trazimo, samo je potrebno ukucati jedan za drugim)

Za pocetak koricenja mozemo samo napisati :
        ./grep -h 
 
 da nam izbaci pomocnu poruku.

 Nakon toga mozemo pretrazivati reci ili recenice.
 
  Takodje mozemo i napisati samo:

    ./grep OBRAZAC [FAJL...]


bez komandi, i linije koje sadrze taj obrazac ce biti ispisane.
 