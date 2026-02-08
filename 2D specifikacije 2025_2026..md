# 2D specifikacije 2025/2026.

## Opšte informacije (Odnosi se i na samostalne teme\!\!)

Odbrana 2D projekta biće realizovana u terminima vežbi u sedmici 8.12-12.12. Svaki student dolazi na odbranu u odgovarajućem terminu po grupi kojoj pripada, osim ako nije naglasio asistentu na vežbama da se zamenio sa drugim studentom. Na [linku](https://docs.google.com/spreadsheets/d/14drd7WRi-2CIdwObT0HpizuEzoLakZimq-Wwj19Ia_E/edit?gid=0#gid=0) su prikazani studenti koji su zamenili termine.

Projekat treba da bude napisan u jeziku C++ sa osloncem na biblioteku OpenGL.  
**OpenGL verzija mora biti najmanje 3 i mora se koristiti programabilni pajplajn\!\! Projekti urađeni u fiksnom pajplajnu neće biti ocenjivani\!\!**  
Projekat mora da sadrži sledeće tehnike pređene na vežbama: programiranje u šejderima, uniforme, providne boje i/ili teksture, unos s miša i/ili tastature i kursor sa nalepljenom slikom (za samostalne teme, kursor treba da nosi izgled nečega što je povezano sa temom, npr. kocka leda za frižider). Svako pisanje teksta ili brojeva se može realizovati teksturama ili korišćenjem biblioteke FreeType. Na svakom mestu gde je potrebno implementirati kretanje konstantnom brzinom, nije greška implementirati ubrzano kretanje, ako se studentu više dopadne (obrnuto ne važi\!\!).  
Projekat mora sadržati frame limiter sa 75 FPS, prekrivati ceo ekran (*full screen*) i u svakom trenutku mora biti moguće isključivanje na taster Escape. U proizvoljnom uglu ekrana potrebno je nalepiti poluprovidnu teksturu na kojoj je napisano ime, prezime i indeks studenta.

Studenti koji su smislili samostalne teme potrebno je da kontaktiraju asistenta mejlom (ako već nisu) na [vasilijem@uns.ac.rs](mailto:vasilijem@uns.ac.rs) kako bi teme bile odobrene. Na [linku](https://docs.google.com/spreadsheets/d/1F2rSl5HuyFs09BF37Qim11BdEqpcZsaRC7lULBQQ7DU/edit?gid=0#gid=0) su prikazani studenti koji imaju samostalne teme, zajedno sa nazivom teme.  
Samostalne teme koje do termina odbrane nisu odobrene mejlom neće biti ocenjivane\!\!\!

## **Stari studenti kojima nije dodeljena grupa ili su naknadno dobili grupu** će braniti projekat u posebnom terminu u **ponedeljak 8.12.2025 u 15:15**.

Projekat je potrebno poslati mejlom [vasilijem@uns.ac.rs](mailto:vasilijem@uns.ac.rs) do termina odbrane, ili u zipu, ili (još bolje\!\!) kao link do github repozitorijuma sa *public* nivoom pristupa.

2D projekat je položen ako je ostvareno \>50% bodova.

U daljem tekstu navedeno je 10 predefinisanih tema. Svakom studentu je dodeljena tema obeležena cifrom kojom se završava broj studentovog indeksa ne računajući godinu upisa (npr. studentu SV 15/2021 bi bila zadata tema broj 5).

# 0\. Brza hrana

Napraviti 2D grafičku aplikaciju za prikaz stanja porudžbine u restoranu brze hrane.

Na početku programa potrebno je da se prikaže dugme za poručivanje hamburgera. Kada se levim klikom miša klikne na dugme, na donjem delu ekrana se pojavi šporet, a u vazduhu živa pljeskavica rozikasto-smeđe boje. Na vrhu ekrana je prazan loading bar.

Pljeskavica se pomera na tastere WASD, i u trenucima kada dodiruje šporet, njena boja se polako menja ka smeđoj, a istovremeno se loading bar puni zelenom bojom sleva nadesno. Kada se loading bar napuni, pljeskavica je smeđe boje i prikaz ekrana se menja tako da na donjem delu nije šporet, nego sto, na kom se nalazi tanjir.

Na scenu se redom pojavljuju sledeći sastojci: donja zemička, pljeskavica s prethodnog dela, kečap, senf, iseckani krastavčići, kolut luka, list zelene salate, parče sira, kolut paradajza i gornja zemička. Svaki sastojak, kada se pojavi, se može kontrolisati tasterima WASD, i kad se stavi na tanjir (ili na prethodno poređani sastojak), na scenu se pojavljuje novi sastojak po prethodnom redosledu.

Za kečap i senf je potrebno prikazati flašicu okrenutu nadole koja se pomera na WASD, a cedi pritiskom na Space. Sastav je uspešno dodat na pljeskavicu ako je Space pritisnuto iznad tanjira, a ako je pritisnuto negde iznad stola, na tom mestu na stolu se pojavljuje barica odgovarajuće tečnosti koja ostaje tu do kraja rada programa.

Kada se na pljeskavicu doda gornja zemička, na ekranu se ispiše *Prijatno\!* i program se završava, jedina opcija za interakciju je izlaz tasterom Escape.

Kursor treba da ima oblik dijagonalne spatule, tako da je ravna metalna površina u gornjem levom uglu.

# 

# 1\. Mapa

Napraviti 2D grafičku aplikaciju za merenje kretanja na mapi.

Potrebno je učitati sliku mape nekog naselja sa rezolucijom (bar 2000 x 1000 piksela, npr. [ova](https://www.orangesmile.com/common/img_city_maps/novi-sad-map-0.jpg)). U programu postoje dva režima: režim hodanja i režim merenja razdaljine.

Na početku programa prikazan je režim hodanja. Na ekranu je vidljiv jedan deo velike mape (npr. jedna stotinka), a u sredini ekrana jedan pin kao na Gugl mapama. Pritiskanjem WASD, pin ostaje u sredini ekrana, ali se mapa pomera u odgovarajućem smeru u odnosu na pritisnute dugmiće. Dok se pomera, meri se pređena razdaljina i ispisuje se negde na ekranu.  
U proizvoljnom uglu erkana je nekim znakom potrebno dati korisniku do znanja da se nalazi u režimu hodanja, npr. oznakom čoveka koji hoda. Pritiskom na taster R ili klikom na malopre pomenuti znak program prelazi u režim merenja razdaljine.

U režimu merenja razdaljine se prikazuje cela slika mape. Levim klikom na neko mesto na mapi, pojavljuje se bela tačka i od nje kreće da se meri razdaljina. Svakim sledećim levim klikom se dodaje još jedna tačka na kliknutu poziciju i spaja se duž između nove i prethodno dodate tačke. Svaki put kada se kreira duž, dodaje se razdaljina te duži (tako da je ista razmera kao u režimu za hodanje) i negde na ekranu se ispisuje ukupna suma dužina svih duži.  
Kada je miš pozicioniran na nekoj od dodatih tačaka i stisne se levi klik, tačka i duži koje iz nje izlaze se brišu. Ukoliko obrisana tačka nije bila jedna od dve krajnje tačke putanje, dodaje se nova duž između njenog prethodnika i sledbenika. Kad god se obriše tačka, ukupna razdaljina se ažurira tako da iznosi sumu prisutnih duži.  
U proizvoljnom uglu erkana je nekim znakom potrebno dati korisniku do znanja da se nalazi u režimu merenja razdaljine, npr. oznakom lenjira. Pritiskom na taster R ili klikom na malopre pomenuti znak program prelazi u režim hodanja.

Stanja sačuvana u oba režima (pređena razdaljina i pozicija pina za hodanje, odnosno tačke i duži za merenje razdaljine) je potrebno čuvati kad se prelazi u drugi režim i vratiti stanje kada se režim opet prebaci.

Kursor treba da ima izgled kompasa, tako da crvena igla pokazuje na gornji levi ugao.

# 

# 2\. Akvarijum

Napraviti 2D grafičku aplikaciju za simulaciju akvarijuma.

Akvarijum treba ima pravougaoni oblik i da zauzima celu širinu ekrana i \>50% visine ekrana, tako da dodiruje donju ivicu ekrana. Donja, leva i desna ivica akvarijuma treba da budu označene crnim linijama sa debljinom od 10 piksela. Preko cele površine akvarijuma je prisutan četvorougao bele boje koji ima providnost 0,2.

U akvarijumu je potrebno napuniti dno teksturom peska. Na proizvoljnim mestima se nalaze bar dve stabljike morske trave koja rastu iz peska. Na proizvoljnom mestu na pesku se nalazi kovčeg koji je na početku programa zatvoren, a otvara se pritiskom na taster C. Kada je otvoren, u njemu se nalazi nekoliko zlatnih novčića i jedan dragulj, a moguće ga je zatvoriti pritiskom na isti taster.

U akvarijumu plivaju dve ribice: zlatna ribica i riba-klovn. Zlatna ribica se pomera po vodi pomoću WASD, a riba-klovn strelicama. Svaki put kada promeni smer kretanja levo-desno, tekstura ribice se izokrene kao u ogledalu (ovaj način kretanja važi za obe ribice). Pritiskom na taster Z, zlatna ribica ispusti tri mehurčića koji idu ka površini i nestanu kad izađu iz vode. Klovn-riba isto ovo radi, ali pritiskom na taster K.

Pritiskom na taster Enter, odgore (van ekrana) u vodu padne nekoliko čestica hrane za ribice: padaju konstantnom brzinom i zaustavljaju se kad dođu do peska. Dok su čestice u vodi, svaki put kada neka ribica pređe preko jedne čestice, ta čestica nestane, a visina poligona koja predstavlja ribicu (debljina ribice) koja je “pojela” česticu se poveća za 0,01.

Kursor treba da ima oblik sidra, tako da je vrh sidra u gornjem levom uglu, a kuke za prizemljenje u donjem levom i gornjem desnom uglu.

# 

# 3\. Lift

Napraviti 2D grafičku aplikaciju za prikaz rada lifta u višespratnoj zgradi.

Ekran je podeljen na dve polovine. Na levoj polovini je prikazan panel sa tasterima, dok su na desnoj polovini spratovi i lift koji se kreće gore-dole i zaustavlja na spratovima. Na desnoj polovini ima 8 spratova, a lift se kreće uz desnu ivicu ekrana. Na panelu su sledeći tasteri:  
Spratovi \- SU (suteren), PR (prizemlje), 1, 2, 3, 4, 5, 6 (ovim redom idu spratovi).  
Taster za zatvaranje vrata  
Taster za otvaranje vrata  
Taster za stopiranje lifta (STOP)  
Taster za ventilaciju

Lift se na početku programa nalazi na prvom spratu. Liftom se kreće osoba, koja se na početku programa nalazi u prizemlju, van lifta. Tasterima A i D se osoba kreće levo-desno. Kad god je osoba van lifta, ona može da pozove lift, tako što dodiruje levu ivicu lifta (otišla je najdešnje što može na svojoj putanji) i korisnik pritisne taster C. Tada se lift, ukoliko se ne nalazi na istom spratu, konstantnom brzinom kreće ka spratu na kom se osoba nalazi. Kada dođe do odgovarajućeg sparta i vrata se otvore (npr. pravougaonik koji predstavlja vrata se podigne). Osoba ima 5 sekundi da uđe u lift, nakon toga se vrata zatvaraju.

Dok je osoba u liftu, tasteri na levoj polovini se mogu pritiskati levim klikom miša. Ukoliko se pritisne neki taster za sprat, on postaje uokviren belom bojom, a lift krene da se konstantnom brzinom kreće do potrebnog sprata. Ukoliko je više spratova selektovano, oni ostaju pritisnuti dok lift ne obiđe sve spratove. Vrata se otvaraju na 5 sekundi svaki put kad lift stane na nekom spratu.

Dok su otvorena vrata od lifta, osoba može slobodno da ulazi i izlazi u lift, ali samo 5 sekundi koliko obično traje period dok su vrata otvorena. Ako je osoba u liftu dok su vrata otvorena, može da pritisne (mišem) taster za otvaranje vrata i taj period će se produžiti za 5 sekundi (ovo je moguće uraditi samo jednom dok su vrata otvorena). U istoj situaciji može da pritisne taster za zatvaranje vrata i ona će se odmah zatvoriti (period će isteći).

Kursor treba da ima izgled crnog propelera koji postane obojen u proizvoljnu boju dok je uključena ventilacija, sve dok lift ne stigne do prvog potrebnog sprata.

# 

# 4\. Pametni sat

Napraviti 2D grafičku aplikaciju za prikaz ekrana na pametnom satu.

Na sredini početnog ekrana se prikazuje vreme u HH:MM:SS formatu. Svake sekunde se povećava poslednja vrednost, dok ne pređe 60\. Tad poveća minut za 1 i sekunde se restuju na 00\. Kad minut pređe 60, resetuje se na 00, a sat se poveća za 1\. Kada sat pređe 24, resetuje se na 00\. Desno od sata se nalazi strelica koja pokazuje nadesno i koja, kad se klikne levim klikom miša, menja ekran na merenje otkucaja srca.

Na ekranu za merenje otkucaja srca se levo nalazi strelica koja pokazuje nalevo i koja levim klikom miša vodi nazad na ekran za vreme. U sredini ekranaza merenje otkucaja srca se nalazi EKG koji je animiran tako da se grafik kreće nalevo ali tako da pravougaonik u kom se nalazi ostaje u mestu. Grafik je predstavljen jednom teksturom na kojoj je nacrtana jedna dolja i jedan breg EKG grafika i koja se ponavlja nekoliko puta. Iznad grafika se nalazi broj otkucaja scra po minuti, koji se random funkcijom kreće između 60 i 80 BPM.

Dok se drži taster D, simulira se trčanje. BPM se polako povećava, a tekstura grafika se sužava, tako da će se stvarati efekat da će biti više i više otkucaja koji su vidljivi na monitoru. Dok je BPM preko 200, preko celog ekrana se prikazuje upozorenje da se korisnik zaustavi i odmori. Desno na ekranu za se nalazi strelica koja pokazuje desno i koja, kad se klikne levim klikom miša, menja ekran na prikaz baterije.

Na ekranu za prikaz baterije se u sredini nalazi oznaka baterije koja je na početku programa na 100% i napunjena je zelenom bojom, dok je procenat ispisan iznad nje. Dok program traje, na svakih 10 sekundi se baterija smanji za 1% i zeleni pravougaonik koji puni bateriju se sužava tako da reflektuje odgovarajući procenat i tako da je uvek zalepljen na desnu ivicu baterije. Ukoliko pređe 20%, pravougaonik postane žut, a ukoliko pređe 10%, postaje crven. Na levoj strani ekrana za prikaz baterije se nalazi strelica koja pokazuje nalevo i levim klikom miša vodi nazad na ekran za merenje otkucaja srca.

Stanja svih ekrana treba da ostanu sinhronizovana dok je neki drugi ekran aktivan.

Kursor treba da ima izgled srca.

# 

# 5\. Klima-uređaj

Napraviti 2D grafičku aplikaciju za prikaz rada klima-uređaja.

Na vrhu ekrana se nalazi beli pravougaonik koji predstavlja klima-uređaj, a na dnu ispod njega se nalazi providni lavor. Na početku programa, klima-uređaj je isključen i na dnu njegove površine je zatvorena prečaga iz koje bi inače duvao vazduh. U donjem desnom uglu uređaja je mala kružna lampica koja je takođe isključena. Takođe su na uređaju vidljiva tri ekrančića koja su isključena (crne boje).

Pritiskom levim klikom miša na lampicu, klima se uključuje. Lampica odmah postane crvena, a prečaga se konstantnom brzinom otvara. Takođe se pale tri ekrančića. Na prvom ekrančiću je napisana željena temperatura, koja je inicijalno podešena na 24°C. Na drugom ekranu je prikazana izmerena temperatura vazduha, koja je incijalno 30°C. Na trećem ekranu je nacrtana vatra ukoliko je željena temperatura veća od izmerene, pahulja ako je manja, a kukica (✅) ako su jednake. Dok god se dve temperature razlikuju, izmerena temperatura se vremenom povećava ili smanjuje dok ne dostigne željenu.

Pritiskom na taster strelica gore, željena temperatura se povećava za jedan stepen, odnosno smanjuje za 1°C pritiskom na strelicu dole. Opseg željene temperature se kreće između \-10°C i 40°C.

Svake sekunde se unutrašnjost lavora puni svetloplavim pravougaonikom koji predstavlja vodu. Pritiskom na taster Space se lavor ispražnjuje, odnosno visina svetloplavog pravougaonika se vraća na 0\. Ukoliko pravougaonik dostigne celokupnu zapreminu lavora, klima se isključuje i nije moguće uključiti je dok se lavor ne isprazni.

Klimu je takođe moguće isključiti levim klikom na lampicu. Kad se isključi, bilo da li klikom ili zbog napunjenog lavora, ekrani i lampica se gase odmah, a prečaga se zatvara istom brzinom kojom se otvorila.

Kursor treba da ima izgled daljinskog upravljača tako da mu je laserska lampica u gornjem levom uglu.

# 

# 6\. Autobus

Napraviti 2D grafičku aplikaciju za praćenje autobuske rute.

Na ekranu je prikazana putanja kojom se kreće autobus. Sačinjena je od krivih crvenih linija koje se nalaze između stanica i koje formiraju **nepravilan** oblik, koje su obeležene kao crveni krugovi sa belim brojem unutra. Stanica ima 10 i obeležene su od 0 do 9\. Autobus je prikazan sličicom autobusa i kreće se po putanji stanicama redom od 0 do 9, a putanja je zatvorena, odnosno, osim svake dve susedne, stanica 0 je takođe povezana sa stanicom 9\.

Autobus se od stanice do stanice kreće konstantnom brzinom. Kada dođe do stanice, on se zaustavi. Potrebno je na proizvoljnom uglu ekrana prikazati ikonicu vrata koja su zatvorena dok se autobus vozi, a otvorena su 10 sekundi dok je on na stanici (za ovo vreme se ikonica autobusa takođe zadrži na stanici).

U drugom proizvoljnom uglu ekrana pamti se broj putnika u autobusu, koji je na početku 0\. Dok su vrata autobusa otvorena na stanici, levim klikom miša na ekran ulazi po jedan putnik, odnosno broj se povećava za 1; dok desnim klikom miša na ekran izlazi po jedan putnik, odnosno broj se smanji za 1\. Opseg broja putnika se kreće od 0 do 50\.

Dok su vrata autobusa otvorena, pritiskom na taster K u autobus ulazi kontrola. Broj putnika se tada poveća za 1, i trećem proizvoljnom uglu ekrana se prikazuje oznaka kontrole (npr. slika saobraćajca u Monopolu) sve dok autobus ne dođe do sledeće stanice, kad kontrola izlazi i broj putnika se smanji za 1\. Na stanici na kojoj kontrola izlazi se generiše random vrednost između 0 i broja putnika \- 1 kojima je naplaćena kazna (- 1 jer je jedan od putnika kontrola) i sabira se sa ukupnim brojem naplaćenih kazni. Ovaj broj je inicijalno 0 i potrebno ga je uvek prikazivati pored broja trenutnih putnika. Moguće je da druga kontrola uđe na stanici na kojoj je prethodna kontrola izašla.

Kursor treba da ima izgled žutog rombastog saobraćajnog znaka (kao BUS STOP znak)  tako da je sam znak u gornjem levom uglu, a metalna šipka dijagonala slike.

# 

# 7\. Bioskop

Napraviti 2D grafičku aplikaciju za upravljanje sedištima u bioskopu.

Na ekranu je prikazana ptičja perspektiva bioskopske sale sa najmanje 50 sedišta. Ulaz u salu se nalazi na gornjem levom delu ekrana, a bioskopsko platno u vidu horizontalnog belog pravougaonika na gornjem delu ekrana. Preko celog ekrana postoji tamnosivi pravougaonik sa providnošću 0,5.

Na početku su sva sedišta obojena u plavo, odnosno imaju status Slobodno. Levim klikom miša na bilo koje od sedišta, sedište postaje žute boje, odnosno ima status Rezervisano. Ukoliko se opet levim klikom miša stisne na neko rezervisano sedište, rezervacija se otkaže i sedište opet ima status Slobodno.

Klikom na tastere od 1 do 9 se mogu kupiti karte. Kada se klikne broj N, potrebno je krenuti od najdešnjeg sedišta u poslednjem redu i, kada se nađe prvih N susednih sedišta koja imaju status Slobodno i ona postaju crvene boje, odnosno dobijaju status Kupljeno.

Klikom na taster Enter se simulira početak projekcije i tada se vrata sale otvaraju i nestaje veliki providni tamnosivi pravougaonik. Sedišta više ne menjaju status, u salu ulaze ljudi, prikazani sličicom čovečuljka, a ima ih najviše onoliko koliko ima ukupno rezervisanih i kupljenih sedišta (npr. moguće je da je rezervisano 5 mesta i kupljeno 7 a da uđe 10 ljudi, broj treba da bude random). Svaka osoba koja uđe se konstantnom brzinom kreće do jednog od mesta, tako što prvo ide vertikalno do svog reda, a zatim horizontalno do svog sedišta.

Kada su svi ljudi ušli i seli na svoja sedišta, vrata se zatvaraju i film počinje. Film traje 20 sekundi, a za to vreme se bioskopsko platno menja na sledeći način: menja se u različitu nasumičnu boju na svakih 20 frejmova. Nakon što prođe 20 sekundi, platno postaje bele boje, vrata se otvore i ljudi kreću da izlaze istom putanjom kojom su došli do sedišta. Kada svi izađu, vrata se zatvore i vrati se tamnosivi pravougaonik, odnosno, program se vraća na stanje s početka programa (ponovo je moguća rezervacija i kupovina).

Kursor treba da ima izgled filmske kamere.

# 

# 8\. Kandža

Napraviti 2D grafičku aplikaciju za vašarsku igru hvatanja plišanih životinja metalnom kandžom.

Na ekranu je prikazan automat sa staklenom kutijom (pravougaonik bele boje koji je delimično providan, npr. alfa vrednost 0,2) u kojoj visi zatvorena kandža i u kojoj se nalaze dve plišane životinje po izboru. Na desnoj strani dna kutije je rupa u koju je potrebno ubaciti plišanu životinju kada se uhvati kandžom. Na donjem delu automata, ispod staklene kutije, nalazi se slot za žeton, a direktno ispod rupe se nalazi prostor u koji će životinja pasti. Iznad kutije se nalazi lampica koja je na početku isključena. Kada se na slot za žeton klikne levim klikom miša, lampica krene da svetli plavo, kandža se otvori i program prelazi u režim igre.

U režimu igre kandža se pomera levo-desno na tastere A i D. Na pritisak tastera S, kandža krene da se spušta, odnosno konopac o koji kandža visi se produžava konstantnom brzinom. Ako kandža tokom spuštanja naleti na dno kutije, vraća se istom brzinom nagore u početno stanje. Ako kandža pak udari u plišanu životinju, životnja je ugrabljena i kandža se vraća nagore zajedno sa životinjom.

Kandža i dalje može da se kreće na tastere A i D, ali nosi životinju sa sobom. Kada se u ovom stanju pritisne taster S, kandža se otvori i ugrabljena životinja krene da **ubrzano** pada. Ukoliko udari dno kutije, padanje se zaustavlja i moguće je opet ugrabiti životinju kandžom. Ukoliko pak životinja upadne u rupu, kandža se zatvara (ne može da se otvori) i životinja nastavlja da pada dok ne dođe do prostora u kom će biti vidljiva korisniku i lampica kreće da se menja između zelenog i crvenog na svakih pola sekunde. Korisnik može levim klikom miša kliknuti na osvojenu životinju, koja će onda nestat,i a lampica će se ugasiti. Nakon toga je moguće opet kliknuti na slot za žeton i aktivirati režim igre.

Kursor treba da ima izgled žetona dok je automat isključen, a izgled poluge tako da je vrh u gornjem levom uglu ako je automat isključen.

# 

# 9\. Rolerkoster

Napraviti 2D grafičku aplikaciju za praćenje stanja hrabrih duša na rolerkosteru.

Na ekranu se vidi vertikalni prikaz pruge kojom se kreće rolerkoster, proizvoljnog oblika ali tako da je sačinjen od krivih linija i da ima bar tri “brega”, odnosno uzbrdica i nizbrdica. Na dnu rolerkostera se nalazi samo vozilo u kom se nalazi 8 praznih sedišta.

Na početku programa, na svaki pritisak tastera Space, po jedno mesto se popuni sličicom čovečuljka, tako da se prvo popunjavaju mesta koja su napred. Svaki put kad se mesto popuni, moguće je kliknuti čovečuljka levim klikom i preko njega će se nalepiti tekstura vezanog pojasa. Kada se pritisne taster Enter, ukoliko su svi putnici vezani (čak i ako ih nema 8), rolerkoster kreće **ubrzano** da se kreće po svojoj  putanji. Ako postoji putnik koji nije vezan u trenutku kad se pritisne Enter, ništa se ne desi. Kada vozilo dostigne neku zadatu brzinu, kreće se tom brzinom na ravnim površinama, **ubrzano** na nizbrdicama, a **usporeno** na uzbrdicama.

U toku putanje moguće je pritisnuti bilo koji taster od 1 do 8 simuliraće se signal da se nekom putniku slošilo: tada će se rolerkoster **usporeno** zaustaviti, a čovečuljak koji sedi na mestu koje je predstavljeno tim brojem će postati zelen (ako mesto čiji je broj pritisnut nije zauzeto, ništa se neće desiti). Vozilo će biti zaustavljeno 10 sekundi, posle čega će krenuti da se vraća na početak jako malom konstantnom brzinom.

Kako god se vozilo vratilo na početak svoje putanje, svi putnici će se automatski odvezati i klikom na svakog od njih će oni nestajati. Kada svi putnici iz jedne ture nestanu, moguće je dodavati nove putnike, kao na početku programa.

Kursor treba da ima izgled šina.