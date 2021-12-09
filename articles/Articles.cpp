#include<iostream>
#include<cstdio>
#include<string>
#include<fstream> 
#include<cstdlib>
#include<iomanip>

using namespace std;

struct Artikal  //definiranje na struktura artikal
{
	int sifra;
	string opis;
	float cena;
	int vlezna_kolicina, izlezna_kolicina;
	float danocna_stapka, iznos;
	int datum;
} artikli[100]; //deklariranje na niza od tip artikal so 100 elementi

struct Prihod //definiranje na struktura prihod
{
	float vlezen, izlezen, vkupen;
} prihodi[100]; //deklariranje na niza od tip prihod so 100 elementi


//------------------------------Prototipi na funkcii---------------------------------
void SifraVnes(int&, const Artikal[], int);
void DatumVnes(int&);
int BrCifri(int);
bool DaliEDatum (int);
void VleznaIzleznaKolicinaVnes(int&, int&, float&);
void Promena(Artikal&, Artikal&);
void Sortiranje(Artikal[], int);
void Dati (int , int&, int&, int&);
void PrihodPresmetka (Artikal, Prihod&);

// -------------------------------- MAIN ---------------------------------------------

int main()
{
	int br_artikli; //deklariranje na promenliva koja ke go cuva brojot na artikli vnesen od korisnikot
	float vkupen_prihod = 0; //deklariranje na promenliva vo koja ke se cuva vkupniot prihod od site artikli
	
	vnesbr: cout<<"Vnesete broj na artikli:\n";
	cin>>br_artikli; //vnesuvanje na broj na artikli
	
	if (br_artikli>100)
	goto vnesbr; /*dokolku brojot na artikli e pogolem od 100, 
	programata povtorno go prasuva korisnikot na vnese
	bidejki maksimalniot broj na artikli e 100*/
	
	//------------------------VNESUVANJE-----------------------------------------
	for (int i=0; i<br_artikli; i++)
	{
		cout<<"\n--------------------- Artikal broj "<<i+1<<" -----------------------\n";
		SifraVnes(artikli[i].sifra, artikli, i); //povikuvanje na funkcija so koja se vnesuva sifra za artikalot so reden broj i
		cout<<"Vnesete opis:\n";
		cin.ignore();
		getline(cin, artikli[i].opis);//vnesuvanje na opis za artikalot so reden broj i
		cout<<"Vnesete cena:\n";
		cin>>artikli[i].cena; //vnesuvanje na cena za i-tiot artikal
		VleznaIzleznaKolicinaVnes(artikli[i].izlezna_kolicina, artikli[i].vlezna_kolicina, artikli[i].danocna_stapka);
		// povikuvanje na funkcija so koja se vnesuva vlezna i izlezna kolicina za artikalot so reden broj i
		if (artikli[i].danocna_stapka)
		{
		cout<<"Vnesete danocna stapka:\n";
		cin>>artikli[i].danocna_stapka;
		}
		cout<<"Vnesete iznos:\n";
		cin>>artikli[i].iznos; //vnesuvanje na iznos za artikalot so reden broj i
		DatumVnes(artikli[i].datum); //povikuvanje na funkcija so koja se vnesuva datum za artikalot so reden broj i
	}
	ofstream vnes, sort; //otvaranje na logicikite datoteki vnes i sort za pisuvanje
	vnes.open("vnos.txt"); //Povrzuvanje na fizickata datoteka "vnos.txt" so logicnata datoteka vnes
	sort.open("sort_vlez.txt"); //Povrzuvanje na fizickata datoteka "sort_vlez.txt" so logicnata datoteka sort
	if (!vnes.is_open() || !sort.is_open())
	{
	cout<<"Neuspesen obid\n";
	return 1; //Dokolku otvaranjeto na datotekite e neuspesno f-jata main vrakja 1 so sto programata prestanuva so rabota
	}
	
	for (int i=0; i<br_artikli; i++)
	{
		vnes<<"\n--------------------- Artikal broj "<<i+1<<" -----------------------\n------------------------------------------------------------\n";		
		vnes<<"Sifra: \t\t\t"<<artikli[i].sifra<<"\n";
		vnes<<"Opis: \t\t\t"<<artikli[i].opis<<"\n";
		vnes<<"Cena: \t\t\t"<<showpoint<<fixed<<setprecision(2)<<artikli[i].cena<<"\n";
		vnes<<"Vlezna kolicina: \t"<<artikli[i].vlezna_kolicina<<"\n";
		vnes<<"Izlezna kolicina: \t"<<artikli[i].izlezna_kolicina<<"\n";
		vnes<<"Danocna stapka: \t"<<showpoint<<fixed<<setprecision(2)<<artikli[i].danocna_stapka<<"\n";
		vnes<<"Iznos: \t\t\t"<<showpoint<<fixed<<setprecision(2)<<artikli[i].iznos<<"\n";
		vnes<<"Datum: \t\t\t";
		switch (BrCifri(artikli[i].datum))
		{ 
		case 3: vnes<<"000"<<artikli[i].datum<<"\n"; break;
		case 4: vnes<<"00"<<artikli[i].datum<<"\n"; break;
		case 5: vnes<<"0"<<artikli[i].datum<<"\n"; break;
		default: vnes<<artikli[i].datum<<"\n"; break;
		/*So pomos na switch se odreduva kolku nuli kje se napisat pred datumot na artikalot bidejki toj e od tip int
		a int ne prima nuli pred vrednosta. Pa taka, dokolku datumot e (primer) 001012, promenlivata ima vrednost 1012
		odnosno 4 cifri, pa programot zapisuva dve nuli pred nejzinata vrednost za site datumi da imaat isti prikaz vo datotekata */
		}
	}
	
	Sortiranje(artikli, br_artikli); //povikuvanje na f-ja koja gi sortira artiklite	
	
	for(int i=0; i<br_artikli; i++)
	{
	PrihodPresmetka (artikli[i], prihodi[i]); //povikuvanje na f-ja koja go presmetuva prihodot na artikalot so reden broj i
	vkupen_prihod+=prihodi[i].vkupen; //zgolemuvanje na promenlivata vkupen_prihod za prihodot na artikalot so reden broj i
	}
	
	//------------------------VNESUVANJE vo datoteka sort--------------------------
	for (int i=0; i<br_artikli; i++)
	{
		sort<<"\n--------------------- Artikal broj "<<i+1<<" -----------------------\n------------------------------------------------------------\n";
		sort<<"Sifra: \t\t\t"<<artikli[i].sifra<<"\n";
		sort<<"Opis: \t\t\t"<<artikli[i].opis<<"\n";
		sort<<"Cena: \t\t\t"<<showpoint<<fixed<<setprecision(2)<<artikli[i].cena<<"\n";
		sort<<"Vlezna kolicina: \t"<<artikli[i].vlezna_kolicina<<"\n";
		sort<<"Izlezna kolicina: \t"<<artikli[i].izlezna_kolicina<<"\n";
		sort<<"Danocna stapka: \t"<<showpoint<<fixed<<setprecision(2)<<artikli[i].danocna_stapka<<"\n";
		sort<<"Iznos: \t\t\t"<<showpoint<<fixed<<setprecision(2)<<artikli[i].iznos<<"\n";
		sort<<"Datum: \t\t\t";
		switch (BrCifri(artikli[i].datum))
		{ 
		case 3: sort<<"000"<<artikli[i].datum<<"\n"; break;
		case 4: sort<<"00"<<artikli[i].datum<<"\n"; break;
		case 5: sort<<"0"<<artikli[i].datum<<"\n"; break;
		case 6: sort<<artikli[i].datum<<"\n"; break;
		/*So pomos na switch se odreduva kolku nuli kje se napisat pred datumot na artikalot bidejki toj e od tip int
		a int ne prima nuli pred vrednosta. Pa taka, dokolku datumot e (primer) 001012, promenlivata ima vrednost 1012
		odnosno 4 cifri, pa programot zapisuva dve nuli pred nejzinata vrednost za site datumi da imaat isti prikaz vo datotekata */
		}
		sort<<"Prihod: \t\t"<<setprecision(2)<<fixed<<showpoint<<prihodi[i].vkupen<<"\n";
	}
	sort<<"\n\nVKUPEN PRIHOD: \t\t"<<showpoint<<setprecision(2)<<fixed<<vkupen_prihod;
	return 0;
}

// -------------------------------- F-II ---------------------------------------------

void SifraVnes(int& a, const Artikal artikli[], int n) //f-ja za vnesuvanje na sifra
{
	/* Vo promenlivata a se vnesuva sifra koja potoa treba da i bide predadena na poleto sifra na artiklot 
	pa zatoa taa promenliva se prenesuva po referenca. Promenite vo a kje bidat i vo poleto sifra 
	
	Nizata od artikli se prenesuva kako konstanta bidejki taa sluzi samo za sporedba na vnesenata sifra so
	sifrite na drugite artikli, vo slucaj korisnikot na vnese ista sifra
	
	So n e oznacen redniot broj na artiklot vo nizata 
	*/
	
	vnes1: cout<<"Vnesete sifra:\n";
	cin>>a; //Vnesuvanje na sifrata
	bool ista=false; /*deklariranje na promenliva od tip bool koja sluzi za proverka dali sifrata koja e vnesena
	od strana na korisnikot e ista so sifra na drug artikal. Pocetnata vrednost e false bidejki pretpostavuvame
	deka sifrata ne e ista. Vo slucaj ova da e greska, taa kje ja promeni vrednosta vo true */
	
	for (int i=0; i<n; i++)
		if (a==artikli[i].sifra)
			ista=true; 
	/* So pomos na for ciklusot sifrata koja e vnesena se sporeduva so site sifri pocnuvajki od prvata pa se do
	artiklot vo koj momenatlno se vnesuvaat podatoci */
	
	if (/*povikuvanje na f-ja koja presmetuva kolku cifri ima argumentot*/BrCifri(a)>5 || ista) 
	goto vnes1; /* Dokolku sifrata ima povekje od 5 cifri ili sifrata e ista so nekoja prethodna sifra,
	programta kje go prasa korisnikot povtorno da vnese sifra */
}

void DatumVnes(int& datum) //F-ja so koja se vnesuva datum vo artikalot 
{
	vnes2: cout<<"Vnesete datum:\n";
	cin>>datum; //Vnesuvanje na datum
	if (!DaliEDatum(datum)) 
	goto vnes2;	//Dokolku brojot ne odgovara na formatot GGMMDD togas programot go prasuva korisnikot povtorno da vnese datum
}

int BrCifri(int broj) //F-ja koja presmetuva kolku cifri ima daden broj
{
	int brojac=0; //promenliva brojac koja kje broi koi cifri ima brojot
	for (brojac; broj!=0; brojac++) /*ciklusot pocnuva od vrednost 0 za brojacot i se zgolemuva za 1 
	vo sekoj nov ciklus se dodeka brojot ne dostigne vrednost 0 */
	broj/=10; //brojot se deli na 10 so sto se krati za edna cifra
	return brojac; //F-jata ja vrakja vrednost na brojacot
}

bool DaliEDatum (int datum) //F-ja koja proveruva dali broj od tip int e datum vo forma GGMMDD ili ne
{
	if (BrCifri(datum)>6 || BrCifri(datum)<3)
	return false; 
	/* Dokolku brojot ima povekje od 6 cifri ili pomalku od 3 cifri togas toj sigurno ne e datum pa
	f-jata vrakja vrednost false. Datumot moze da ima i 3 cifri vo slucaj na 2000 godina i mesec 
	pomal od 10 bidejki toj e od tip int, a int ne cuva nuli pred brojot. Duri i korisnikot da vnese
	(primer)000315 promenlivata datum kje dobie vrednost 315. */
	else
	{
	int god, mesec, den; //deklariranje promenlivi koi kje ja dobijat vrednosta na mesecot, denot i godinata
	Dati(datum, den, mesec, god); /*Se povikuva f-jata Dati na koja i se prenesuvaat promenlivite den, mesec
	i godina po referenca za da ja dobijat vrednosta pri presmetkata koja se slucuva vo f-jata i promenlivata
	datum po vrednost bidejki ne e potrebno i ne se pravat promeni */
	if (god>19 || mesec>12 || mesec<1 || den<1 || den>31) /*Dokolku godinata e pogolema od 19 ili
	mesecot ne e vo opsegot 1..12 ili mesecot ne e vo opsegot 1..31, togas f-jata vrakja false*/
		return false;
	else if (den==31 && (mesec==2 || mesec==6 || mesec==4 || mesec==9 || mesec==11)) /*Dokolku denot ima vrednost 31
	a mesecot ne e ednakov na eden od slednive:1, 4, 6, 9, 11, togas f0jata vrakja false */
		return false;
	else if (den==30 && mesec==2) //Dokolku denot e 30 a mesecot 2, f-jata vrekja false
		return false;
	else //Dokolku nitu eden od prethodnite uslovi ne e ispolnet, togas datumot e pravilno napisan pa f-jata vrakja true
	return true;
	}
}

void VleznaIzleznaKolicinaVnes(int& izlezna, int& vlezna, float& dan_stapka) 
{
	vnes3: cout<<"Dali sakate da vnesete vlezna kolicina ili izlezna?\n";
	cout<<"1 -----> Vlezna\n2 -----> Izlezna\n";
	int pom; /*Pomosna promenliva so pomos na koja kje se odredi dali korisnikot saka da vnese
	vlezna kolicina ili izlezna */
	cin>>pom;
	if (pom==1) //Dokolku korisnikot vnel 1 mu se dava da vnese vlezna kolicina
	{
	cout<<"Vnesete vlezna kolicina:\n";
	cin>>vlezna;
	izlezna=0;	//Izleznata kolicina dobiva vrednost 0
	dan_stapka=0.0; //Danocnata stapka dobiva vrednost 0
	}
	else if(pom==2) //Dokolku korisnikot vnel 2 mu se dava da vnese izlezna kolicina
	{
	cout<<"Vnesete izlezna kolicina:\n";
	cin>>izlezna;
	vlezna=0; //Vleznata kolicina dobiva vrednost 0
	dan_stapka=1.0; /*Danocnata stapka dobiva vrednost 1 koja podocna kje se promeni. Moze da dobie i drug broj
	no vazno e da bide razlicen od 0 */
	}
	else
	goto vnes3; //Dokolku korisnikot ne vnel 1 ili nula, programata kje mu pobara povtorno da vnese izbor
}

void Sortiranje(Artikal niza[], int n) //F-ja koja gi sortira artiklite so pomos na alogritamot bubble sort
{
	/* Sortiranjeto se vrsi na toj nacin sto 2 artikli so sporeduvaat i dokolku postariot se naogja na reden
	broj pogolem od ponoviot proizvod tie si gi zamenuvaat mestata. Vo slucaj na isti datum 
	sortiranjeto se vrsi po sifra od pomala kon pogolema */
	
	for (int i=0; i<n; i++) //Prviot ciklus zapocnuva od 0 do brojot na artikli
	for (int j=i+1; j<n; j++) //Vtoriot ciklus zapocnuva edno mesto ponapred od prviot ciklus
	{
		int den1, den2, mesec1, mesec2, god1, god2; //deklariranje na promenlivi den, mesec i godina za dvata artikli
		Dati(niza[i].datum, den1, mesec1, god1); 
		/* Povikluvanje na f-jata Dati na koja i se prenesuva datumot od artikalot so reden broj i
		i promenlivite den1, mesec1 i god1 po referenca koi treba da gi dobijat vrednostite na
		den mesec i godina soodvetno */
		Dati(niza[j].datum, den2, mesec2, god2);
		/* Povikluvanje na f-jata Dati na koja i se prenesuva datumot od artikalot so reden broj j
		i promenlivite den2, mesec2 i god2 po referenca koi treba da gi dobijat vrednostite na
		den mesec i godina soodvetno */
		if (god1>god2) /*dokolku godinata na artikalot so reden broj i e pogolema od godinata na artikalot 
		so reden broj j, toa znaci deka vtoriot artikal e postar pa tie treba da si gi promenat mestata */
		Promena(niza[i],niza[j]); //Povikuvanje na f-ja za promena na mestata na dvata artikli
		if(god1==god2) 
		{
		if (mesec1>mesec2) /* Vo slucaj koga godinata na dvata artikli e ista, se proveruva dali mesecot na
		artikalot so reden broj i e pogolem od mesecot na artikalot so reden broj j. Vo potvrden slucaj
		tie si gi menat mestata. */
		Promena(niza[i],niza[j]); //Povikuvanje na f-ja za promena na mestata na dvata artikli
		if (mesec1 == mesec2) 
			{
			if(den1>den2) /* Dokolku mesecot na artikalot so reden broj i i artikalot so reden broj j se isti
			se proveruva dali denot na artikalot so reden broj i e pogolem od artikalot so reden broj j. 
			Vo potvrden slucaj tie si gi menat mesta. */
			Promena(niza[i],niza[j]); //Povikuvanje na f-ja za promena na mestata na dvata artikli
			if (den1==den2 && niza[i].sifra>niza[j].sifra) /*Dokolku i denot na dvata artikli e isti togas tie 
			se sporeduvaat po sifra. Dokolku sifrata na artikalot so reden broj i e pogolema od 
			artikalot so reden broj j, tie si gi menat mestata. */
			Promena(niza[i],niza[j]); //Povikuvanje na f-ja za promena na mestata na dvata artikli
			}	
		}
	}
}

void Dati (int datum , int& den, int& mesec, int& god) //F-ja koja daden za daden datum presmetuva den, mesec i godina
{
	/*Promenlivata datum se prenesuva po vrednost, dodeka promenlivite den, mesec i godina se prenesuvaat po referenca.
	Datumot e od tip integer daden vo oblik GGMMDD*/
	god=datum/10000; //Godinata se presmetuva so celobrojno delenje na datumot so 10000. Na ovoj nacin se izdvojuvaat prvite 2 cifri
	mesec=(datum/100)%100; //Mesecot se dobiva so delenje na datumot na 100, a potoa kako ostatok pri celobrojno delenje so 100 
	den=datum%100; //Denot se dobiva kako ostatok pri delenje na brojot so 100.
}

void Promena(Artikal& prv, Artikal& vtor) //F-ja koja gi promenuva mestata na dve promenlivi od tip Artikal
{
	Artikal tret=prv;
	prv=vtor;
	vtor=tret;
}

void PrihodPresmetka (Artikal a, Prihod& p) //Funkcija koja presmetuva prihod na promenliva od tip Artikal i go smestuva vo promenliva od tip Prihod
{
// promenlivata od tip Prihod se prenesuva po refernca za sekoja promena vo polinjata da se slucuva direktno
	p.vlezen=a.vlezna_kolicina*a.cena;
	p.izlezen=a.cena-(a.cena*a.danocna_stapka/100) - a.izlezna_kolicina;
	p.vkupen=p.vlezen-p.izlezen;
}
