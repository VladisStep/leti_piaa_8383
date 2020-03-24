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
    
    std::cout << "*Ищем подстроку в строке"<< std::endl;
    std::cout << "|Обрабатываем символ: " << txt[0] << std::endl;
    
    int i = 0;                              /// индекс, для перемещения по строке поиска
    int j = 0;                              /// индекс, для перемещению по подстроке
   
    while (i < N) {         /// считываем строку поиска посимвольно, пока не конец
        std::cout << "|  Индекс строки i = " << i << " Индекс подстроки j = " << j << std::endl;
        if (pat[j] == txt[i]) {                  /// если символы  i символ подстроки и j смвол подстроки равны
            j++;                            /// то увеличиваем j и i и считываем следющий символ
            i++;
            std::cout << "| Символы совпадают" << std::endl;
            std::cout << "|Обрабатываем символ: " << txt[i] << std::endl;
        }

        if (j == M) {                       /// если j  равна длине подстроки, то строка является циклическим сдвигом
            std::cout << "* Строка является циклическим сдвигом" << std::endl;
            std::cout << i - j;             /// выводим индекс начала строки
            outFile << i -j;
            return;
        
        } else if (i < N && pat[j] != txt[i]) {              /// иначе если не конец строки поиска и символы не совпадают
            std::cout << "| Символы НЕ совпадают"<< std::endl;

            if (j != 0)                                     /// если j не 0, то задаем j значения предыдущего значения массива длин префикса
                j = lps[j - 1];
            else{                                           /// иначе считываем следующий символ
                i++;
                std::cout << "|Обрабатываем символ: " << txt[i] << std::endl;
            }
        }
    }
    
    std::cout << -1;            /// если подстрока не найдена, то строка не является циклическим сдвигом
    outFile << -1;
    std::cout << "* Строка НЕ является циклическим сдвигом" << std::endl;

}


void computeLPSArray(std::string &pat, int M, int* lps) { /// заполнение массива длин префиксов

    int len = 0;

    lps[0] = 0;                                         /// первый элемент всегда 0

    int i = 1;
    
    std::cout << "*Заполняем массив префиксов" << std::endl;
    std::cout << "|Первый эелемент массива = 0"  << std::endl;
   
    while (i < M) {                                     /// заполняем от 1 до размер массива -1
        std::cout << "|Обрабатываем символ: " << pat[i] << std::endl;
        std::cout << "|  len = " << len << " i = " << i << std::endl;
        if (pat[i] == pat[len]) {
            
            std::cout << "|  Совпадение символа суффикса и префикса" << std::endl;
            len++;
            lps[i] = len;                               /// задаем i элементу значение len
            i++;
            
        
        } else {                                        // (pat[i] != pat[len])
            std::cout << "|   Не совпадение символа суффикса и префикса" << std::endl;
            if (len != 0) {
                len = lps[len - 1];                     /// если len не 0, то задаем len значения предыдущего значения массива длин префикса
                std::cout << "|  Т.к. len не 0, то задамеи значине lps[len-1] = " << len << std::endl;
            } else {                                    // if (len == 0)
                lps[i] = 0;                             /// задаем i элементу массиву 0
                i++;
                std::cout << "|  Т.к. len равно 0, то обрабатываем следующий символ"<< std::endl;
            }
        }
    }
    
    std::cout << "*Заполнение массива префиксов завершено" << std::endl;
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
    std::cout << "Склеиваем строку А и ищем в ней подстроку В"<< std::endl;

    KMPSearch(pat, txt);
       
      
    
    return 0;
}


