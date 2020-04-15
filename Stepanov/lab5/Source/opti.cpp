#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

# define COUNT_OF_SYM 5
int deep = 0;

struct vertex {
    int next[COUNT_OF_SYM];     // массив указателей на вершину, в которую ведёт ребро по символам
    bool leaf;                  // является ли концом строки
    int numStr;                 // индекс строки
    int p;                      // вершина предок
    char pch;                   // символ, по которому перешли из вершины предка
    int link;                   // суффиксная ссылка
    int go[COUNT_OF_SYM];       // переходы в автомате по каждому из символов
};

struct saveString {             // структура для хранения подстроки
    std::string stroc;          // подстрока
    std::vector<int> ind;       // индекс в строке
};

void printSpace (){
    for (int i = 0; i < deep; i++){
        std::cout << " ";
    }
}

bool cmpAnswer (int a, int b){    // компаратор, для сортировки вывода ответа
    return a < b;
}


int indOfSym (char sym){                // функция, которая возвращате индекс соответствующего символа
    switch (sym) {
        case 'A':
            return 0;
        case 'C':
            return 1;
        case 'G':
            return 2;
        case 'T':
            return 3;
        case 'N':
            return 4;
        default:
            return -1;
    }
}



void addString (const std::string & s, std::vector <vertex> & t, int i) {
    
    int v = 0;              // начинаем добавление из корня
    size_t sz = t.size();      // количество вершин бора

    
    for (int i = 0; i < s.length(); ++i) {      // проходимся по всей строке
        
        char c = indOfSym(s[i]);        // получаем индекс элемента
        
        
        if (t[v].next[c] == -1) {       // если перехода не сущетвует, то создаем его
            
            std::cout   <<"\tРебра " << s[i] << " из "<< v << " не существует" << std::endl
                        <<"\tСоздаем новое состояние " << sz+1 << std::endl;
            
            vertex a;
            t.push_back(a);
            
            for (int j = 0; j < COUNT_OF_SYM; j++){
                t[sz].next[j] = -1;
                t[sz].go[j] = -1;
            }
            
            t[sz].link = -1;
            t[sz].numStr = -1;
            t[sz].p = v;
            t[sz].pch = c;
            t[v].next[c] = (int) sz++;  // добавляем к старой вершине ребро до новой
        } else {
            std::cout <<"\tРебра " << s[i] << " из "<< v << " найдено" << std::endl;
        }
        
        std::cout <<"\tПереходим в состояние " << t[v].next[c] << std::endl;
        
        v = t[v].next[c];       // переходим в новую вершину
    }
    
    t[v].leaf = true;   // последняя вершмна является концом строки
    t[v].numStr = i;    // строки с индексом i
}

int go (int v, char c, std::vector <vertex> & t);
 
int getLink (int v, std::vector <vertex> & t) {
    
    deep++;
    printSpace();
    std::cout << "    |-------- Получение вершины по суффиксной ссылке"<<std::endl;
    
    if (t[v].link == -1){                // если еще не переходили
        if (v == 0 || t[v].p == 0)      // если находимся в корне или предок корень
            t[v].link = 0;
        else                                                    // переходим по суффиксной ссылки родителя
            t[v].link = go (getLink (t[v].p, t), t[v].pch, t);  // пытаемся получить состояние, которое можно получить по символу
        printSpace();
        std::cout << "    |\tДобавляем состоянию " << v <<" суффиксную ссылку на " << t[v].link << std::endl;
    }
    printSpace();
    std::cout << "    *---- Вершина найдена" << std::endl;
    deep--;
        return t[v].link;                                           // по которому пришли из родителя
}
 
int go(int v, char c, std::vector <vertex> & t) {
    deep++;
    printSpace();
    std::cout << "    |-------- Получение перехода оп символу " << c <<std::endl;
    if (t[v].go[c] == -1){                                      // если еще не совершали переход по символу с
        if (t[v].next[c] != -1)                                 // если в боре существует переход по символу с
            t[v].go[c] = t[v].next[c];                          // записываем переход
        else                                                    // иначе не существует перехода в боре
            t[v].go[c] = v == 0 ? 0 : go (getLink (v,t), c, t); // пытаемся перейти в вершине, доступной по ссуфиксной ссылке
        printSpace();
        std::cout << "    |\t Добавление нового перехода" << std::endl;
    }
    
    printSpace();
    std::cout <<"    *-------- Вершина найдена" << std::endl;
    deep--;
    return t[v].go[c];
}


int main () {
    
    std::string text;               // текст поиска
    int k;                          // количество строк
    std::vector<int> answers;       // вектор для формирования ответа
    std::vector<vertex> t;          // вектор, в котором храниться бор
    
    std::string str;                // строка с джокерами
    char joker;                     // джокер
    char contSym;                   // символ, который не может быть джокером
    
//------------------------------------- Считывание

    std::cin >> text;
    std::cin >> str;
    std::cin >> joker;
    std::cin >> contSym;

    std::vector <int> C(text.length()); // вектор для записи количества вхождений подстрок
    std::vector <saveString> arr;       // вектор для хранения подстрок
    
    saveString c;                       // добавляем символ  contSym как подстроку
    c.stroc.push_back(contSym);
    arr.push_back(c);
    
    std::cout <<  "Разбиваем строку на подстроки" << std::endl;

    for (int j = 0; j < str.length(); j++){         // разделение строки на подстроки
        
        if (str[j] != joker){
            
            std::string s;
            int saveJ = j;
            k++;
            
            for (j; str[j] != joker && j < str.length(); j++){
                s.push_back(str[j]);
            }
            
            std::cout << "  Найдена построка: " << s << std::endl;
            
            bool inArr = false;
            
            int i = 0;
            
            for (i; i < arr.size(); i++){
                
                if (arr[i].stroc == s) {
                    inArr = true;
                    break;
                }
            }
           
            if (inArr == false){
                
                saveString ss;
                
                ss.stroc = s;
                ss.ind.push_back(saveJ);
                
                arr.push_back(ss);
                std::cout << "\tСохраняем новую подстроку " << s
                << " и ее индекс " << saveJ << std::endl;
                
            } else {
                arr[i].ind.push_back(saveJ);
                std::cout << "\tПодстрока " << s
                << " уже существует, добавляем индекс " << saveJ << std::endl;
                
            }
        }
        
        if (str[j] == joker)
        arr[0].ind.push_back(j);
    }
    
    
//------------------------------------- Создание бора
    vertex a;
    t.push_back(a);                             // добавление корня

    for (int i = 0; i < COUNT_OF_SYM; i++){
        t[0].next[i] = -1;
        t[0].go[i] = -1;
    }

    for (int i = 0; i < arr.size(); i++) {               // добавление строк в бор
        addString(arr[i].stroc, t, i);

    }

     for (int i = 0; i < COUNT_OF_SYM; i++){    // создание петли из корня в корень
         if (t[0].next[i] == -1)                // для сиволов, которые не имеют ребра с корнем
         t[0].next[i] = 0;

       }
//------------------------------------- Поиск


    int curr = 0;                               // начинаем поиск из корня

    for (int i = 0; i < text.length(); i++){    // проходимся по всему тексту
        
        std::cout << "------------------------" << std::endl
        << "Ищем вершину для перехода из " << curr << " по " << text[i] << std::endl;
        
        curr = go(curr, indOfSym(text[i]), t);  // получение следующей вершины

        std::cout <<" Переходим в "  << curr << std::endl;
        
        for (int next = curr; next != 0; next = getLink(next, t)){  // проеверяем данную вершину и все вершины
                                                                    // по которым можно перейти по суффиксным ссылкам
            std::cout << "  Проверяем вершину " << next << std::endl;
                                                                    // если вершина является концом какой-то строки
            if (t[next].leaf) {                                     // то записываем номер строки и положение в ответ
                
                int indInText = i - arr[t[next].numStr].stroc.length()+1;   // индекс подстроки в тексте
                
                for (int j = 0; j < arr[t[next].numStr].ind.size(); j++){   // проходимся по всем индексам вхождения подстроки в строку
                    int indInStr = arr[t[next].numStr].ind[j];              // индекс подстроки в строке
                    
                    if ((indInText - indInStr >= 0)){
                        
                        if (contSym != text[i]) {                // если это не contSym
                            C[indInText - indInStr]++;          // то увеличиваем счетчик
                            std::cout << "Найдено вхождение подстрки " << arr[t[next].numStr].stroc
                            << ", увеличиваем ячейку с индексом "  << indInText - indInStr +1<< std::endl;
                        } else {
                            C[indInText - indInStr]--;          // иначе уменьшаем
                            std::cout << "Найдено вхождение символа, который не может быть джокером, уменьшаем ячейку с индексом "  << indInText - indInStr +1<< std::endl;
                        }
                    }
                }
            }
        }
    }


//------------------------------------- Вывод


    for (int i = 0; i <= text.length() - str.length(); i++){    // проходимся по всевозможным вхождениям

        if (C[i] == k){                                         // если строка входит в текст начиная с индекса i
            answers.push_back(i+1);                             // то в ячейке i должно быть число равное кол-ву подстрок
        }
    }

     std::sort(answers.begin(), answers.end(), cmpAnswer);      // сортируем ответ


    for (int i = 0; i < answers.size(); i++){
           std::cout << answers[i]<< std::endl;
       }

}
