#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

# define COUNT_OF_SYM 5


int deep = 0;

struct vertex {
    int next[COUNT_OF_SYM];     // массив указателей на вершину, в которую ведёт ребро по символам
    bool leaf;                  // является ли концом строки
    
    int numStr;                  // индекс строки
   
    int p;                      // вершина предок
    char pch;                   // символ, по которому перешли из вершины предка
    int link;                   // суффиксная ссылка
    int go[COUNT_OF_SYM];       // переходы в автомате по каждому из символов
};

struct answer{                  // структра для хранения ответа
    int pos;
    int word;
};

bool cmpAnswer (answer a, answer b){    // компаратор, для сортировки вывода ответа
    if (a.pos == b.pos) return a.word < b.word;
    return a.pos < b.pos;
}

void printSpace (){
    for (int i = 0; i < deep; i++){
        std::cout << " ";
    }
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
    std::vector<answer> answers;    // вектор для формирования ответа
    std::vector<vertex> t;          // вектор, в котором храниться бор
    
//------------------------------------- Считывание

    std::cin >> text;

    std::cin >> k;

    std::string *arr = new std::string[k];

    for (int i = 0; i < k; i++){
        std::cin >> arr[i];
    }
//------------------------------------- Создание бора
    vertex a;
    t.push_back(a);                             // добавление корня
    
    for (int i = 0; i < COUNT_OF_SYM; i++){
        t[0].next[i] = -1;
        t[0].go[i] = -1;
    }
    
    for (int i = 0; i < k; i++) {               // добавление строк в бор
        std::cout <<"Добавляем строку: " << arr[i] << std::endl;
        addString(arr[i], t, i);
        std::cout << "  Строка добавлена" << std::endl;
    }

     for (int i = 0; i < COUNT_OF_SYM; i++){    // создание петли из корня в корень
         if (t[0].next[i] == -1)                // для сиволов, которые не имеют ребра с корнем
         t[0].next[i] = 0;

       }
//------------------------------------- Поиск


    int curr = 0;                               // начинаем поиск из корня

    for (int i = 0; i < text.length(); i++){    // проходимся по всему тексту
        
        if (indOfSym(text[i]) == -1) continue;
        
        std::cout << "------------------------" << std::endl
        << "Ищем вершину для перехода из " << curr << " по " << text[i] << std::endl;
        
        curr = go(curr, indOfSym(text[i]), t);  // переходим к следующей вершине
        
        std::cout <<" Переходим в "  << curr << std::endl;
        
        for (int next = curr; next != 0; next = getLink(next, t)){  // проеверяем данную вершину и все вершины
            std::cout << "  Проверяем вершину " << next << std::endl;
            
            if (t[next].leaf) {                                     // если вершина является концом какой-то строки
                answer a;                                           // то записываем номер строки и положение в ответ
                a.pos =  i - arr[t[next].numStr].size() + 2;
                a.word = t[next].numStr +1;
                answers.push_back(a);
                
                std::cout << "  Вершина явялется конечной, строка "<< t[next].numStr +1
                << " найдена на с индекса " << i - arr[t[next].numStr].size() + 2<< std::endl;
            }
            

        }
    }


//------------------------------------- Вывод
    
    std::sort(answers.begin(), answers.end(), cmpAnswer);           // сортируем овет
    
    for (int i = 0; i < answers.size(); i++){
           std::cout << answers[i].pos << " " << answers[i].word << std::endl;
       }
    
}

