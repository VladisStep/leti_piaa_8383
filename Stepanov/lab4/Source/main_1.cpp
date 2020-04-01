#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <variant>


void computeLPSArray(std::string &pat, int M, int* lps);

std::variant<std::vector <int>> KMPSearch(std::string &pat)  /// КМП алгоритм
{
    std::variant<std::vector <int>> answer;
    
    int M = (int) pat.length();

    int lps[M];                             /// массив длин префиксов

    computeLPSArray(pat, M, lps);           /// заполнение массива длин префиксов
    
    std::cin.get();
    char c = std::cin.get();

    int i = 0;                              /// индекс, для перемещения по строке поиска
    int j = 0;                              /// индекс, для перемещению по подстроке
   
    while (c != '\n' && c != EOF) {         /// считываем строку поиска посимвольно, пока не конец
        
        if (pat[j] == c) {                  /// если символы i символ подстроки и j смвол подстроки равны
            j++;                            /// то увеличиваем j и i и считываем следющий символ
            i++;
            c = std::cin.get();
        }

        if (j == M) {                       /// если j  равна длине подстроки
           // answer.push_back(i-j);
           
           (std::get<std::vector <int>>(answer)).push_back(i-j);
            j = lps[j - 1];
        
        } else if (c != '\n'  && c != EOF && pat[j] != c) { /// иначе если не конец строки поиска и символы не совпадают
         
            if (j != 0)                                     /// если j не 0, то задаем j значения предыдущего значения массива длин префикса
                j = lps[j - 1];
            else{                                           /// иначе считываем следующий символ
                i = i + 1;
                c = std::cin.get();
            }
        }
    }
           return answer;
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
    
    std::ofstream outFile;
    outFile.open("./outProg");
    
    std::cin >> pat;
     
    std::variant<std::vector <int>> answer = KMPSearch(pat);
    
    
    for (int k = 0; k < (std::get<std::vector <int>>(answer)).size(); k++) {       /// вывод результатов работы лагоритма

        std::cout << (std::get<std::vector <int>>(answer))[k];
        outFile << (std::get<std::vector <int>>(answer))[k];

        if (k != (std::get<std::vector <int>>(answer)).size()-1){
            std::cout <<",";
            outFile <<",";
        }
    }

    if ((std::get<std::vector <int>>(answer)).empty()){
        std::cout << -1;
        outFile << -1;
    }
    
    return 0;
}

