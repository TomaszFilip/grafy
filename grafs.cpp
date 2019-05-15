#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#define INFINITY 2147483647;
using namespace std;



struct ElementListy
{
  ElementListy *next;
  int dest;
  int wgh;
};



class grafl
{
public:
  int n; //rozmiar
  ElementListy ** listas;
  grafl(int iloscwierzcholkow)
  {
    n=iloscwierzcholkow;
    listas= new ElementListy * [n];
    for(int i=0;i<n;i++){listas[i]=NULL;}
  };
  ElementListy*  &operator[](int i) {return listas[i];};
};


class grafm
{
public:
  int n; //rozmiar
  int **macierz;
  grafm(int iloscwierzcholkow)
  {
    n=iloscwierzcholkow;
    macierz = new int *[n];
    for(int i=0;i<n;i++)
      {
	macierz[i]=new int[n];
	for(int j=0;j<n;j++)
	  {
	    macierz[i][j]=-1;
	  }
      }
  };
  int* &operator[](int i) {return macierz[i];} 
};

int wyswietldroge(int ilewierzcholkow, int poprz[], int koszty[])
{
  int* Stos= new int[ilewierzcholkow];
  int wierz=0;
  int i=0;
  for(i = 0; i < ilewierzcholkow; i++)
    {
      cout << i << ": ";
      
      for(int w = i; w > -1; w = poprz[w])
	Stos[wierz++] = w;
      //wyswietl przebyte wierzcholki
      while(wierz)
	cout << Stos[--wierz] << " ";
      //wyswietl koszt
      int inf=INFINITY;
       if(koszty[i]==inf)
	 cout << "brak mozliwej sciezki (graf nie jest spojny)"<<endl;
	else
	  cout << "koszt:" << koszty[i] << endl;
    }
}
int zapiszdoplikudroge(int ilewierzcholkow, int poprz[], int koszty[], string nplikudocel)
{
  
  int* Stos= new int[ilewierzcholkow];
  int wierz=0;
  ofstream plikdoc(nplikudocel);
 for(int i = 0; i < ilewierzcholkow; i++)
    {
      plikdoc << i << ": ";
      
      for(int w = i; w > -1; w = poprz[w])
	Stos[wierz++] = w;
      //wyswietl przebyte wierzcholki
      while(wierz)
	plikdoc << Stos[--wierz] << " ";
      //wyswietl koszt
      int inf=INFINITY;
      if (koszty[i]==inf)
	plikdoc << "brak mozliwej sciezki (graf nie jest spojny)"<<endl;
	else
	  plikdoc << "koszt:" << koszty[i] << endl;
    }
  plikdoc.close();
 
}


void djikstral(grafl graf, int wierzstart, string nplikudocel)
  {
    int i,j,u;
  //Przygotowanie tablic
  int *koszty = new int [graf.n];
  int *poprz = new int [graf.n];
  bool *NS= new bool [graf.n];
  
   for (int i=0; i<graf.n; i++)
    {
      koszty[i]=INFINITY;
      poprz[i]=-1;
      NS[i]=false;
    }
   
  koszty[wierzstart]=0;
  
  for(i=0;i<graf.n;i++)
    {
      for(j=0; NS[j];j++);
      for(u=j++;j<graf.n;j++)
	if(!NS[j]&&(koszty[j]<koszty[u]))
	  u=j;
      NS[u]=true;
      
 
  ElementListy *krawedz;
  krawedz= new ElementListy;
  for(krawedz=graf[u];krawedz;krawedz=krawedz->next)
    if(!NS[krawedz->dest]&&(koszty[krawedz->dest]>koszty[u]+krawedz->wgh))
      {
	koszty[krawedz->dest]=koszty[u]+krawedz->wgh;
	poprz[krawedz->dest]=u;
      }
    }
  //wyswietldroge(graf.n, poprz, koszty);
  zapiszdoplikudroge(graf.n, poprz, koszty,nplikudocel);
  
    }


void djikstram(grafm graf, int wierzstart, string nplikudocel)
{
  int i, j ,u, m, h;
  //Przygotowanie tablic
  int *koszty = new int [graf.n];
  int *poprz = new int [graf.n];
  bool *NS= new bool [graf.n];
  int* Stos= new int[graf.n];
  int wierz=0;

  
   for (int i=0; i<graf.n; i++)
    {
      koszty[i]=INFINITY;
      poprz[i]=-1;
      NS[i]=false;
    }
   
  koszty[wierzstart]=0;

  for(i=0;i<graf.n;i++)
    {
      for(j=0;NS[j];j++);
      for(u=j++;j<graf.n;j++)
	if(!NS[j]&&(koszty[j]<koszty[u]))
	  u=j;
      NS[u]=true;

      
    
  h=0;
  //tworzenie tablicy wszystkich sasiadow wierzcholka u
  int* sasiedzi=new int[graf.n];
  
  for(int m=0;m<graf.n;m++)
    {
      if(graf[u][m]>-1)
	{
	  sasiedzi[h]=m;
	  h++;
	}
    }
  h--;
  for(h;h>=0;h--)
    if(!NS[sasiedzi[h]]&&(koszty[sasiedzi[h]]>koszty[u]+graf[u][sasiedzi[h]]))
      {
	koszty[sasiedzi[h]]=koszty[u]+graf[u][sasiedzi[h]];
	poprz[sasiedzi[h]]=u;
      }
    }
  //wyswietldroge(graf.n, poprz, koszty);
  zapiszdoplikudroge(graf.n, poprz, koszty,nplikudocel);
    }
int generujplikizgrafami(int ilwierz, double gestosc, int ilegrafow)
{
  int ilkraw=ilwierz*(ilwierz-1)*gestosc;
  int wierzcholekstartalg=2;
  for (int z=0; z<ilegrafow;z++)
    {
      int** istniejace=new int*[ilwierz];
      for(int i=0;i<ilwierz;i++)
	{
	  istniejace[i]=new int[ilwierz];
	for(int j=0;j<ilwierz;j++)
	  {
	    istniejace[i][j]=0;
	  }
	}
      ostringstream ss;
      ss << z;
      string numer = ss.str();
      string nazwapliku="graf"+numer+".txt";
      ofstream plik(nazwapliku);
      plik<<ilkraw<<" "<<ilwierz<<" "<<wierzcholekstartalg<<endl;
      int wierzchstart=0;
      for(int kraw=0; kraw<ilkraw;kraw++)
	{
	  wierzchstart=wierzchstart%ilwierz;
	  int wierzchend=rand()%ilwierz;
	  int flag=0;
	  if(wierzchstart==wierzchend)
	    flag=-1;
	  if(istniejace[wierzchstart][wierzchend]==1)
	    { flag=-1;
	    }
	  while (wierzchend==wierzchstart||flag==-1)
	    {
	      wierzchend=(wierzchend+1)%ilwierz;
	    if((istniejace[wierzchstart][wierzchend]==0)&&wierzchstart!=wierzchend)
	    {
	       flag=0;
	    }
	    }
	  
	  istniejace[wierzchstart][wierzchend]=1;
	  
	  int waga=rand()%1000+1;
	  plik<<wierzchstart<<" "<<wierzchend<<" "<<waga<<endl;
	  wierzchstart++;
	}
	  delete istniejace;
      plik.close();
    }
}
int main()
{
  int ilegrafow=100,ilewierzch=100;
  double gestosc=1;
  char agree;
  cout<<"START"<<endl;
  cout<<"UWAGA! Program moze wygenerowac duza ilosc plikow z grafami w swoim katalogu, jesli sie NIE ZGADZASZ, nacisnij n i zakoncz jego dzialanie, jesli sie ZGADZASZ wprowadz inny znak"<<endl;
    cin>>agree;
  if(agree=='n')
    return -2;
  cout<<"Program automatycznie generuje grafy o podanych w dwoch pierwszych linijkach main() parametrach,efekt dzialania programu (sciezki znalezione przy pomocy algorytmu Dijikstry) zapisywany jest do pliku o nazwie droga[nrgrafu].txt"<<endl;
  cout<<"generowanie grafow..."<<endl;
  generujplikizgrafami(ilewierzch,gestosc,ilegrafow);
  cout<<"Grafy wygenerowano."<<endl;
  int start, end, weight;
  double czasydzialania[100];
  cout.precision(8);
  char list_or_matrix;
  cout<<"Wybierz: l-lista sasiedztwa m-macierz sasiedztwa"<<endl;
  cin>>list_or_matrix;
  cout<<"Praca algorytmu, po jej zakonczeniu zostanie wyswietlony jego sredni czas dzialania"<<endl;
  int ilosc_krawedzi, ilosc_wierzcholkow, wierzcholek_startowy;
   for (int ktorygraf=0; ktorygraf<ilegrafow; ktorygraf++)
     {
    ostringstream ss;
    ss << ktorygraf;
    string numer = ss.str();
    string nazwapliku="graf"+numer+".txt";
    string nplikudocel="droga"+numer+".txt";
    fstream plik;
    plik.open(nazwapliku);
      
  if(plik.good())
    {
      plik>>ilosc_krawedzi;
      plik>>ilosc_wierzcholkow;
      plik>>wierzcholek_startowy;
   switch (list_or_matrix)
    {
    case 'l':
      {
	grafl graf(ilosc_wierzcholkow);
	for(int i=0; i<ilosc_krawedzi;i++)
	  {
	    plik>>start>>end>>weight;
	    ElementListy *krawedz;
	    krawedz= new ElementListy;
	    krawedz->dest=end;
	    krawedz->wgh=weight;
	    krawedz->next=graf[start];
	    graf[start]=krawedz;
	  }
	//POMIARCZASU_START//
	double roznica; 
	cout.setf(ios::fixed); //notacja zwykla
	clock_t start, koniec; //inicjacja zmiennych zegarowych	
	start=clock(); //zapisanie czasu startu mierzenia
	
	djikstral(graf,wierzcholek_startowy, nplikudocel);

	//POMIARCZASU_KONIEC//
	koniec=clock();//zapisanie konca mierzenia	
	roznica=(koniec-start)/(double)CLOCKS_PER_SEC;
	czasydzialania[ktorygraf]=roznica;
	
	break;
      }
    case 'm':
      {
	grafm graf(ilosc_wierzcholkow);
	for(int i=0; i<ilosc_krawedzi;i++)
	  {
	    plik>>start>>end>>weight;
	    graf[start][end]=weight;
	  }
	//POMIARCZASU_START//
	double roznica; 
	cout.setf(ios::fixed); //notacja zwykla
	clock_t start, koniec; //inicjacja zmiennych zegarowych	
	start=clock(); //zapisanie czasu startu mierzenia
	
	djikstram(graf, wierzcholek_startowy, nplikudocel);
	
	//POMIARCZASU_KONIEC//
	koniec=clock();//zapisanie konca mierzenia	
	roznica=(koniec-start)/(double)CLOCKS_PER_SEC;
	czasydzialania[ktorygraf]=roznica;
      break;
      }
    }
   plik.close();
    }
   }
   double lacznyczas=0;
   for(int count=0;count<100;count++)lacznyczas+=czasydzialania[count];
   double sredniczas=lacznyczas/100;
   cout<<"wierzchołków: "<<ilewierzch<<" "<<"gestosc: "<<gestosc<<" "<<"sredni czas: "<<sredniczas<<endl;
  return 0;
}
