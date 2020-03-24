#include <iostream>
#include <vector>
#include <string>
#include <fstream>

void computeLPSArray(std::string &pat, int M, int* lps);

void KMPSearch(std::string &pat, std::string &txt){  /// КМП алгоритм

    std::ofstream outFile;
    outFile.open("./outProg");
    
    int M = (int) pat.length();
    int N = (int )txt.length();

    int *lps = new int [M];                 /// массив длин префиксов

    computeLPSArray(pat, M, lps);           /// заполнение массива длин префиксов
    

    int i = 0;                              /// индекс, для перемещения по строке поиска
    int j = 0;                              /// индекс, для перемещению по подстроке
   
    while (i < N) {         /// считываем строку поиска посимвольно, пока не конец
        
        if (pat[j] == txt[i]) {                  /// если символы  i символ подстроки и j смвол подстроки равны
            j++;                            /// то увеличиваем j и i и считываем следющий символ
            i++;
        }

        if (j == M) {                       /// если j  равна длине подстроки, то строка является циклическим сдвигом
            std::cout << i - j;             /// выводим индекс начала строки
            outFile << i -j;
            return;
        
        } else if (i < N && pat[j] != txt[i]) {              /// иначе если не конец строки поиска и символы не совпадают
         
            if (j != 0)                                     /// если j не 0, то задаем j значения предыдущего значения массива длин префикса
                j = lps[j - 1];
            else{                                           /// иначе считываем следующий символ
                i++;
            }
        }
    }
    
    std::cout << -1;            /// если подстрока не найдена, то строка не является циклическим сдвигом
    outFile << -1;
}


void computeLPSArray(std::string &pat, int M, int* lps) { /// заполнение массива длин префиксов

    int len = 0;

    lps[0] = 0;                                         /// первый элемент всегда 0

    int i = 1;
   
    while (i < M) {                                     /// заполняем от 1 до размер массива -1
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;                               /// задаем i элементу значение len
            i++;
        
        } else {                                        // (pat[i] != pat[len])

            if (len != 0) {
                len = lps[len - 1];                     /// если len не 0, то задаем len значения предыдущего значения массива длин префикса
            } else {                                    // if (len == 0)
                lps[i] = 0;                             /// задаем i элементу массиву 0
                i++;
            }
        }
    }
}


int main()
{
    
    std::string pat;


    std::string txt;

    std::cin >> txt;
    std::cin >> pat;
    
    
    
    if (txt.length() != pat.length()) {     /// если длины строк не раыны, то строка не является циклическим сдвигом
        std::cout << -1;
        return 0;
    }
       
    txt += txt;                             /// склеиваем строку поиска
       
       
        
    KMPSearch(pat, txt);
       
      
    
    return 0;
}


