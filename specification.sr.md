# 7. Bioskop 2D

Napraviti 2D grafičku aplikaciju za upravljanje sedištima u bioskopu.  

Na ekranu je prikazana ptičja perspektiva bioskopske sale sa najmanje 50 sedišta. Ulaz u salu se nalazi na gornjem levom delu ekrana, a bioskopsko platno u vidu horizontalnog belog pravougaonika na gornjem delu ekrana. Preko celog ekrana postoji tamnosivi pravougaonik sa providnošću 0,5.  

Na početku su sva sedišta obojena u plavo, odnosno imaju status Slobodno. Levim klikom miša na bilo koje od sedišta, sedište postaje žute boje, odnosno ima status Rezervisano. Ukoliko se opet levim klikom miša stisne na neko rezervisano sedište, rezervacija se otkaže i sedište opet ima status Slobodno.  

Klikom na tastere od 1 do 9 se mogu kupiti karte. Kada se klikne broj N, potrebno je krenuti od najdešnjeg sedišta u poslednjem redu i, kada se nađe prvih N susednih sedišta koja imaju status Slobodno i ona postaju crvene boje, odnosno dobijaju status Kupljeno.  

Klikom na taster Enter se simulira početak projekcije i tada se vrata sale otvaraju i nestaje veliki providni tamnosivi pravougaonik. Sedišta više ne menjaju status, u salu ulaze ljudi, prikazani sličicom čovečuljka, a ima ih najviše onoliko koliko ima ukupno rezervisanih i kupljenih sedišta (npr. moguće je da je rezervisano 5 mesta i kupljeno 7 a da uđe 10 ljudi, broj treba da bude random). Svaka osoba koja uđe se konstantnom brzinom kreće do jednog od mesta, tako što prvo ide vertikalno do svog reda, a zatim horizontalno do svog sedišta.  

Kada su svi ljudi ušli i seli na svoja sedišta, vrata se zatvaraju i film počinje. Film traje 20 sekundi, a za to vreme se bioskopsko platno menja na sledeći način: menja se u različitu nasumičnu boju na svakih 20 frejmova. Nakon što prođe 20 sekundi, platno postaje bele boje, vrata se otvore i ljudi kreću da izlaze istom putanjom kojom su došli do sedišta. Kada svi izađu, vrata se zatvore i vrati se tamnosivi pravougaonik, odnosno, program se vraća na stanje s početka programa (ponovo je moguća rezervacija i kupovina).  

Kursor treba da ima izgled filmske kamere.  

# 7. Bioskop 3D

Napraviti 3D grafičku aplikaciju za upravljanje sedištima u bioskopu.  

**Gruba specifikacija:**  
Okvirno iste funkcionalnosti kao u 2D. Sala je u 3 dimenzije i stolice su formirane od teksturisanih kvadara. Svaki sledeći red (krećući se od platna) je za jedan stepenik više. Platno je pravougaonik nalepljen na zid i na početku je bele boje. Filter koji predstavlja mrak ne treba implementirati (za sada!). Ljudi koji ulaze na projekciju se penju uz stepenice da bi došli do svojih mesta i predstavljeni su kao kvadri (za sada!). Kada krene projekcija, na bioskopskom platnu se ne smenjuju boje, već bar 20 različitih tekstura koje predstavljaju frejmove filma.  

Kamera gleda u projekciji perspektive, kreće se na strelice u pravcu pogleda (a ne na fiksnoj y koordinati) i menja pogled na miš. Kretanje kamere je limitirano zidovima, podom i plafonom sale. Rezervacija sedišta se vrši kliktanjem miša dok kamera gleda u to sedište.  

**Detaljna specifikacija:**  
Svi gledaoci su predstavljeni modelima humanoidnih karaktera (koji smeju da se ponavljaju, ali da ih bude bar 15 različitih). Na sceni se nalazi izvor svetlosti sa proizvoljnom bojom, jačinom i pozicijom, koje osvetljava sva tela na sceni i koje je isključeno dok je sala zatvorena i dok projekcija traje. Dok projekcija traje, na samom platnu postoji izvor svetlosti.  