#include "WordFreq.h"
#include <vector>
#include<fstream>
#include<iostream>
#include<map> //gerekli k�t�phaneler eklendi
#include<string>
//ORHAN G�NER - 152120201073 | ABD�LKER�M PEK�NCE 152120201021
///-----------------------------------------------------------------
/// Process the given text file and return the most frequent "k" words
///
vector<WordFreq> GetMostFrequentKWords(string filename, int k) {
    vector<WordFreq> result;
    fstream myFile; //fstream de�i�keni tan�mland�. 
    map<string, int> words; //map tan�mland�.
    myFile.open(filename, ios::in); //dosya okuma modunda a��ld�.
    int frequence = 0; //s�kl�k default 0 ile tan�mland� 
    if (myFile.is_open()) //dosyan�n a��lm�� olma ko�ulu
    {
        string line;
        char ch;
        while (myFile >> ch >> noskipws) //atlama yapmadan b�t�n karakterler okundu
        {
            if (ch != ' ' && ch != '\n') { //bo�luk karakteri ya da alt sat�ra ge�ilmemi� olma ko�ulu
                if (ch != '.' && ch != ',' && ch != '!' && ch != '?' && ch != '$' && ch != '-' && ch != '_') {//noktalama i�aretleri dikkate al�nmayacak
                    line.push_back(ch); //karakterleri string de�i�keni olan line a at�yoruz

                }

            }
            else {
                if (line.size() > 2) { // it, a , to gibi 3 harften az olan kelimeleri kullanm�yoruz
                    map<string, int>::iterator it;
                    it = words.find(line);
                    if (words.size() == 0) {  // ilk kelimeyse 1 s�kl�k ile map a ekledik.
                        words.insert({ line,1 });
                        line.clear(); // karakterleri tuttu�umuz line de�i�kenini her map a atama yapt�ktan sonra temizliyoruz
                    }

                    else if (it != words.end()) {
                        if (line == it->first) { // kelimemiz daha �nce bulunuyorsa s�kl���n tutuldu�u second de�erini 1 artt�r�yoruz
                            it->second++;
                            line.clear();//karakterleri tuttu�umuz line de�i�kenini her map a atama yapt�ktan sonra temizliyoruz
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


        } //son kelimeyi tutabilmek i�in a�a��daki yap�lar� kulland�k 
        if (line.size() > 2) {//kelimenin en az 3 harfli olma ko�ulu
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

        myFile.close(); //dosya okuma i�lemini sonland�rd�k
    }
    map<string, int>::iterator it2;
    it2 = words.begin();
    for (int i = 0; i < words.size(); i++) { //mapte tuttu�umuz kelimeleri vector olan result de�i�kenine at�yoruz

        WordFreq w(it2->first);
        w.freq = it2->second;
        it2++;
        result.push_back(w);

    }
    return result; // fonksiyon result de�i�kenin son halini d�nd�r�yor.
}