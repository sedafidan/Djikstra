#include <iostream>//Standart giris/cikis fonksiyonlarinin prototiplerini icerir
#include <vector>  //eleman eklendikce boyutu ekleme esnasinda artan diziler olarak tanýmlamak icin
#include <string>
#include <list>//standart kütüphane tasiyicilarini saglayan siniflari icerir.Tasiyicilar programin çalismasi sirasinda verileri saklamak icin kullanilir
#include <limits>//her bilgisayar platformu üzerindeki sayisal veri tiplerinin limitlerini belirleyen siniflari içerir
#include <set>
#include <utility>//Bir cok standart kütüphane oncu dosyasinin kullandigi siniflarý ve fonksiyonlari icerir.
#include <algorithm>//Standart kütüphane tasiyicilarindaki bilgi üzerinde islem yapan fonksiyonlari icerir.
#include <iterator>//Standart kütüphane tasiyicilari icindeki veriye ulasmak icin kullanilan siniflari icerir

typedef int Dugum;
typedef double Agirlik;
using namespace std;

const Agirlik maksimumAgirlik = std::numeric_limits<double>::infinity();

struct komsu {
    Dugum hedef;
    Agirlik agirlik;
    komsu(Dugum hedef1, Agirlik agirlik1)
        : hedef(hedef1), agirlik(agirlik1) { }
};
typedef std::vector<std::vector<komsu> > DugumListesi;

void Dijkstra_Yol_Hesaplama(Dugum kaynak,
                          const DugumListesi &dugumListesi,
                          std::vector<Agirlik> &minimumUzaklik,
                          std::vector<Dugum> &onceki)
{
    int n = dugumListesi.size();
    minimumUzaklik.clear();
    minimumUzaklik.resize(n, maksimumAgirlik);//vektorun buyuklugunu n tarafindan belirlenen degere gore degistirir.Vektorun uzatilmasý gerekirse n tarafindan belirtilen degere sahip elemanlar sona eklenir
    minimumUzaklik[kaynak] = 0;
    onceki.clear();//vektorden tum elemanlari siler
    onceki.resize(n, -1);
    std::set<std::pair<Agirlik, Dugum> > dugumKuyruk;
    dugumKuyruk.insert(std::make_pair(minimumUzaklik[kaynak], kaynak));//make_pair, herhangi bir turdeki iki veri ögeleri iceren bir çift yapisi olusturur

    while (!dugumKuyruk.empty())//uyarýcý vektor bos degil ise
    {
        Agirlik uzaklik = dugumKuyruk.begin()->first;//begin(), vektorun baslangicini gosteren bir iterator dondurur
        Dugum u = dugumKuyruk.begin()->second;
        dugumKuyruk.erase(dugumKuyruk.begin());//erase, belirtilen konumdan bir eleman cikarir

        // "U" herbir kenari ziyaret etmek icin kullaniliyor
	const std::vector<komsu> &komsular = dugumListesi[u];
        for (std::vector<komsu>::const_iterator komsu_yineleyici= komsular.begin();
             komsu_yineleyici != komsular.end();
             komsu_yineleyici++)
        {
            Dugum v = komsu_yineleyici->hedef;
            Agirlik agirlik = komsu_yineleyici->agirlik;
            Agirlik mesafe_icinden_u = uzaklik + agirlik;

	    if (mesafe_icinden_u < minimumUzaklik[v]) {
	        dugumKuyruk.erase(std::make_pair(minimumUzaklik[v], v));
	        minimumUzaklik[v] = mesafe_icinden_u;
	        onceki[v] = u;
	        dugumKuyruk.insert(std::make_pair(minimumUzaklik[v], v));
	    }
        }
    }
}
std::list<Dugum> Dijkstra_En_Kisa_Yol(
    Dugum dugum, const std::vector<Dugum> &onceki)
{
    std::list<Dugum> harita;
    for ( ; dugum != -1; dugum = onceki[dugum])
        harita.push_front(dugum+1);
    return harita;
}
int main()
{

    int dugumSayisi=0;
    int komsuSayisi=0;
    int gidilecekDugum=0;

    cout << "\n Dugum sayisini giriniz : "<< endl;
    cin >> dugumSayisi;

    DugumListesi dugumListesi(dugumSayisi);


    for (int i=0;i<dugumSayisi;i++)
    {
        cout <<"\n "<<i+1<<". Dugumun Komsu Sayisi : "<<endl;
        cin >>komsuSayisi;
             for(int j=0;j<komsuSayisi;j++)
         {
             int komsuyaUzaklik,komsuNumarasi;
             cout << "\n "<<j+1<<". Komsusunun numarasini giriniz : "<<endl;
             cin >> komsuNumarasi;
             komsuNumarasi=komsuNumarasi-1;
             cout <<"\nUzaklik : "<<endl;
             cin >>komsuyaUzaklik;
             dugumListesi[i].push_back(komsu(komsuNumarasi,komsuyaUzaklik));//Veriyi   vektorun arkasina ekler
         }
    }
    std::vector<Agirlik> minimumUzaklik;
    std::vector<Dugum> onceki;

    cout << "\nGidilecek dugum numarasini giriniz : "<< endl;
    cin >> gidilecekDugum;


    Dijkstra_Yol_Hesaplama(0, dugumListesi, minimumUzaklik, onceki);

    std::cout << "1. Dugumden "<<gidilecekDugum<<". Dugume Uzaklik : " << minimumUzaklik[gidilecekDugum-1] << std::endl;
    std::list<Dugum> harita = Dijkstra_En_Kisa_Yol(gidilecekDugum-1, onceki);
    std::cout << "Harita : ";
    std::copy(harita.begin(), harita.end(), std::ostream_iterator<Dugum>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}
