#include "WordFreq.h"
#include <vector>
#include<fstream>
#include<iostream>
#include<map> //gerekli kütüphaneler eklendi
#include<string>
//ORHAN GÜNER - 152120201073 | ABDÜLKERÝM PEKÝNCE 152120201021
///-----------------------------------------------------------------
/// Process the given text file and return the most frequent "k" words
///
vector<WordFreq> GetMostFrequentKWords(string filename, int k) {
    vector<WordFreq> result;
    fstream myFile; //fstream deðiþkeni tanýmlandý. 
    map<string, int> words; //map tanýmlandý.
    myFile.open(filename, ios::in); //dosya okuma modunda açýldý.
    int frequence = 0; //sýklýk default 0 ile tanýmlandý 
    if (myFile.is_open()) //dosyanýn açýlmýþ olma koþulu
    {
        string line;
        char ch;
        while (myFile >> ch >> noskipws) //atlama yapmadan bütün karakterler okundu
        {
            if (ch != ' ' && ch != '\n') { //boþluk karakteri ya da alt satýra geçilmemiþ olma koþulu
                if (ch != '.' && ch != ',' && ch != '!' && ch != '?' && ch != '$' && ch != '-' && ch != '_') {//noktalama iþaretleri dikkate alýnmayacak
                    line.push_back(ch); //karakterleri string deðiþkeni olan line a atýyoruz

                }

            }
            else {
                if (line.size() > 2) { // it, a , to gibi 3 harften az olan kelimeleri kullanmýyoruz
                    map<string, int>::iterator it;
                    it = words.find(line);
                    if (words.size() == 0) {  // ilk kelimeyse 1 sýklýk ile map a ekledik.
                        words.insert({ line,1 });
                        line.clear(); // karakterleri tuttuðumuz line deðiþkenini her map a atama yaptýktan sonra temizliyoruz
                    }

                    else if (it != words.end()) {
                        if (line == it->first) { // kelimemiz daha önce bulunuyorsa sýklýðýn tutulduðu second deðerini 1 arttýrýyoruz
                            it->second++;
                            line.clear();//karakterleri tuttuðumuz line deðiþkenini her map a atama yaptýktan sonra temizliyoruz
                        }
                    }
                    else {
                        words.insert({ line,1 });
                        line.clear();
                    }
                }
                else {

                    line.clear();
                }
            }


        } //son kelimeyi tutabilmek için aþaðýdaki yapýlarý kullandýk 
        if (line.size() > 2) {//kelimenin en az 3 harfli olma koþulu
            map<string, int>::iterator it;
            it = words.find(line);
            if (words.size() == 0) {
                words.insert({ line,1 });
                line.clear();
            }

            else if (it != words.end()) {
                if (line == it->first) {
                    it->second++;
                    line.clear();
                }
            }
            else {
                words.insert({ line,1 });
                line.clear();
            }
        }
        else {

            line.clear();
        }

        myFile.close(); //dosya okuma iþlemini sonlandýrdýk
    }
    map<string, int>::iterator it2;
    it2 = words.begin();
    for (int i = 0; i < words.size(); i++) { //mapte tuttuðumuz kelimeleri vector olan result deðiþkenine atýyoruz

        WordFreq w(it2->first);
        w.freq = it2->second;
        it2++;
        result.push_back(w);

    }
    return result; // fonksiyon result deðiþkenin son halini döndürüyor.
}