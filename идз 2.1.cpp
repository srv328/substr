//Входные данные :
//1) текстовый файл, в первой строке – целое число n - количество строк файла(10 ≤ n ≤ 1000000), каждая из последующих строк содержит данные заданной предметной области(см.свой вариант задания),
//разделенные 1 пробелом.Все данные во входном файле корректные(проверять на корректность не нужно);
//2) шаблон поиска(или список шаблонов, если один из алгоритмов предполагает поиск нескольких шаблонов);
//3) k - число - указывает сколько раз заданный шаблон должен встречаться в заданном поле поиска(или сколько из заданных шаблонов должно быть найдено в заданном поле поиска).
//Выходные данные : 2 текстовых файла, в первой строке - время, затраченное на поиск, остальные строки содержат записи входного файла в табличном виде, удовлетворяющие условиям поиска(в первом файле - записи, которые были найдены
//    с использованием первого алгоритма поиска, во втором - вторым).
//1. На вход алгоритму поиска подается одно поле структуры элемента массива
//2. Каждый поиск оформляется в виде отдельной подпрограммы
//3. Типы полей элементов массива должны соответствовать типу данных в предметной области(все что является числом, должно храниться в виде числа, а не строки)
//Шевелёв Роман - шаблон содержится хотя бы в одном поле не менее k - раз, алгоритмы: Ахо – Корасик, Бойера – Мура

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 1e5 + 5;
const int MAXS = 2e6 + 5;

struct TrieNode {
    int ch[26];
    int fail;
    int end;
    bool visited;
};

struct Flight_Number {
    std::string sym;
    int num;
};

struct Date {
    int number;
    int month;
    int year;
};

struct Passenger {
    Flight_Number flight_number;
    std::string fio;
    std::string fio_commander;
    Date date;
};

Date parseDate(std::string input) {
    Date date;
    int dots_cnt = 0;
    for (int i = 0; input.length(); i++) {
        if (input[i] == '.') {
            dots_cnt++;
            continue;
        }
        else {
            if (dots_cnt == 0) {
                date.number = stoi(input.substr(i, 2));
                i++;
            }
            else if (dots_cnt == 1) {
                date.month = stoi(input.substr(i, 2));
                i++;
            }
            else {
                date.year = stoi(input.substr(i, 4));
                break;
            }
        }
    }
    return date;
};

std::vector<Passenger*> readData(std::string path) {
    setlocale(LC_ALL, "Russian");
    std::ifstream fin;
    std::vector<Passenger*>data;
    fin.open(path);
    int n; fin >> n;
    std::string s, fa, im, ot;
    for (int i = 0; i < n; i++)
    {
        Passenger* person = new Passenger;
        fin >> s;
        person->flight_number.sym = s.substr(0, 2);
        person->flight_number.num = stoi(s.substr(2, 4));
        fin >> fa; fin >> im; fin >> ot;
        person->fio = fa + ' ' + im + ' ' + ot;
        fin >> s;
        person->date = parseDate(s);
        fin >> fa; fin >> im; fin >> ot;
        person->fio_commander = fa + ' ' + im + ' ' + ot;
        data.push_back(person);
    }
    fin.close();
    return data;
}

void generateFile(int n, std::string path) {
    try {
        std::ofstream fout;
        fout.open(path);
        fout << n << '\n';
        std::string surnames[126] = { "Antonov", "Zinovev", "Kuropatkin", "Matanalizov", "Algoritmov", "Sortirovkov", "Ivanova", "Kulibina", "Liternaya", "Bloha", "Babaj", "Bazar", "Bibik", "Gadyuchka", "Dohlik", "Zhujvoda", "Nepejvoda", "Moska", "Golobev", "Drakula", "Kosheev", "Sova", "Sliva", "Intraligator", "Kisel", "Zazherilo",
        "Aliferov", "Andreev", "Annenkov", "Barbayanov", "Bashinskij", "Bereznickij", "Bessonov", "Bobrovskij", "Bogatev", "Bozhok", "Bondarenko", "Buhalihin", "Van", "Vayaj", "Vinogradov", "Vissarionov", "Vlasov", "Vlasov", "Gandzyuk", "Gerus", "Gogoleva", "Gorbaryov", "Davydov", "Danishimaev", "Di", "Egorova", "Enshin", "Eryomenko",
        "Ermak", "Eroshenko", "Zelenin", "Ivanov", "Karpachyov", "Kasyanenko", "Kiyanov", "Kozachko", "Kolpakova", "Koryaushkin", "Kosenko", "Kosilov", "Kostyuchenko", "Kochetkov", "Kropochev", "Kuzmin", "Kutuzov", "Lagunova", "Lazarev", "Lebedinskij", "Litovchenko", "Lukin", "Makogon", "Mareev", "Martyn", "Matushkin", "Mashkin", "Mihajlov", "Moiseev",
        "Mulyava", "Myznikov", "Nalimov", "Nechepurenko", "Olejnikova", "Osipenko", "Ohlopkov", "Pavlov", "Pak", "Pasko", "Perepechaev", "Podolinskij", "Polovnikov", "Popov", "Procenko", "Pyavka", "Razdobarov", "Rasputnyj", "Seliverstov", "Sivceva", "Sporyshev", "Starcev", "Stoletnij", "Sutugin", "Tarasov", "Tahavov", "Teryohin",
        "Timofeev","Tregubova", "Turovskij", "Tyukova", "Uvarov", "Hegaj", "Hmelevskij", "Hramcova", "Caregorodcev", "Cyplakov", "Chechyotkin", "Shevelyov", "Sheshenya", "Shibanov", "Shmidt", "Yakuba" };
        std::string names[65] = { "Agnes", "Adolf", "Adrian", "Boris", "Valentin", "Vasilij", "Vitalij", "Georgij", "Grigorij", "Daniil", "Denis", "Dmitrij", "Evgenij", "Egor", "Ivan", "Igor", "Konstantin", "Leonid", "Maksim", "Matvej", "Nikita", "Nikolaj", "Oleg", "Pavel", "Pyotr", "Roman", "Ruslan", "Sergej", "Stepan", "Timur", "Fyodor", "Yurij",
            "Yaroslav", "Alisa", "Aleksandra", "Alyona", "Alla", "Anastasiya", "Anzhelika", "Valentina", "Veronika", "Viktoriya", "Galina", "Darya", "Diana", "Elizaveta","Zhanna", "Inna", "Irina", "Karina", "Kristina", "Kseniya", "Margarita", "Mariya", "Milana", "Natalya", "Nika", "Oksana", "Olga", "Ruslana", "Svetlana", "Sofiya", "Sofya", "Tamara", "Zhanna" };
        std::string patronymic[36] = { "Aleksandrovich", "Alekseevich", "Anatolevich", "Arkadevich", "Bogdanovich", "Borisovich", "Valerevich", "Viktorovich", "Vladimirovich", "Volfovich", "Gennadievich", "Grigorevich", "Denisovich", "Evgenevich", "Efimovich", "Ignatevich", "Iosifovich", "Kirillovich", "Lvovich", "Matveevich", "Nikolaevich", "Pavlovich", "Petrovich",
            "Robertovich", "Romanovich","Sanych","Severinovich","Stanislavovich","Tarasovich","Timofeevich","Fedorovich","Filippovich","Eduardovich","Yurevich","Yakovlevich","Yaroslavovich" };
        srand((unsigned)time(NULL));
        for (int i = 0; i < n; i++)
        {
            std::string mon, date;
            int month = rand() % 12 + 1;
            if (month < 10) mon = '0' + std::to_string(month);
            else mon = std::to_string(month);
            int dat = rand() % 31 + 1;
            if (dat < 10) date = '0' + std::to_string(dat);
            else date = std::to_string(dat);
            fout << char('A' + rand() % ('Z' - 'A')) << char('A' + rand() % ('Z' - 'A')) << std::to_string(rand() % 9000 + 1000) + ' '\
                + surnames[rand() % 126] + ' ' + names[rand() % 65] + ' ' + patronymic[rand() % 36] + ' ' + date\
                + '.' + mon + '.' + std::to_string(rand() % 92 + 1930) + ' ' + surnames[rand() % 126] + ' ' + names[rand() % 65] + ' ' + patronymic[rand() % 36] + '\n';
        }
        fout.close();
    }
    catch (std::exception e) {
        std::cout << e.what() << '\n';
    }
}

void writeData(std::vector<Passenger*>data, std::string path, long long microseconds) {
    std::ofstream fout;
    fout.open(path);
    fout << microseconds << '\n';
    for (int i = 0; i < data.size(); i++)
    {
        fout << data[i]->flight_number.sym << data[i]->flight_number.num << ' ';
        fout << data[i]->fio << ' ';
        std::string mon;
        if (data[i]->date.month < 10) mon = '0' + std::to_string(data[i]->date.month);
        else mon = std::to_string(data[i]->date.month);
        std::string dat;
        if (data[i]->date.number < 10) dat = '0' + std::to_string(data[i]->date.number);
        else dat = std::to_string(data[i]->date.number);
        fout << dat << '.' << mon << '.' << data[i]->date.year << ' ' << data[i]->fio_commander << '\n';
    }
    fout.close();
}

TrieNode trie[MAXN];
int cnt = 0;

void insertTrie(const string& s) {
    int u = 0;
    for (int i = 0; i < s.size(); i++) {
        int c = s[i] - 'a';
        if (!trie[u].ch[c]) { trie[u].ch[c] = ++cnt; }
        u = trie[u].ch[c];
    }
    trie[u].end++;
}

void buildAC() {
    queue<int> q;
    for (int i = 0; i < 26; i++) { if (trie[0].ch[i]) { q.push(trie[0].ch[i]); } }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            int v = trie[u].ch[i];
            if (!v) { trie[u].ch[i] = trie[trie[u].fail].ch[i]; }
            else {
                trie[v].fail = trie[trie[u].fail].ch[i];
                q.push(v);
            }
        }
    }
}

int search(const string& s) {
    int u = 0;
    int ans = 0;
    for (int i = 0; i < s.size(); i++) {
        int c = s[i] - 'a';
        u = trie[u].ch[c];
        int v = u;
        while (v && trie[v].visited == false) {
            ans += trie[v].end;
            trie[v].visited = true;
            v = trie[v].fail;
        }
    }
    for (int i = 0; i <= cnt; i++) { trie[i].visited = false; }
    return ans;
}

vector<int> preprocess(string pattern) {
    int m = pattern.size();
    vector<int> bad_char(256, m);
    for (int i = 0; i < m - 1; i++) { bad_char[pattern[i]] = m - i - 1; }
    return bad_char;
}

int searchBM(string text, string pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<int> bad_char = preprocess(pattern);
    int count = 0;
    for (int i = 0; i <= n - m;) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[i + j]) { j--; }
        if (j < 0) {
            count++;
            i++;
        }
        else { i += bad_char[text[i + j]]; }
    }
    return count;
}


std::vector<Passenger*> Aho_Corasik(int k, std::vector<Passenger*>data) {
    std::vector<Passenger*> res;
    buildAC();
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < data.size(); i++) { if ((search(data[i]->fio) >= k) || (search(data[i]->fio_commander) >= k)) { res.push_back(data[i]); } }
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
    writeData(res, "AHO_CORASIK.txt", microseconds);
    return res;
}

std::vector<Passenger*> BM(int k, std::vector<string>shablons,std::vector<Passenger*>data) {
    std::vector<Passenger*> res;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < data.size(); i++) {
        int count1 = 0;
        int count2 = 0;
        for (int j = 0; j < shablons.size(); j++) {
            count1 += searchBM(data[i]->fio, shablons[j]);
            count2 += searchBM(data[i]->fio_commander, shablons[j]);
        }
        if (count1 >= k || count2>=k) { res.push_back(data[i]); }
    }
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
    writeData(res, "BOJUER_MURR.txt", microseconds);
    return res;
}

void start(std::vector<Passenger*>data) {
    setlocale(LC_ALL, "Russian");
    int n;
    cout << "Введите количество шаблонов: ";
    cin >> n;
    cout << endl;
    std::vector<string>shablons;
    for (int i = 0; i < n; i++) {
        string s;
        cout << "Введите шаблон " << i + 1 << ": ";
        cin >> s;
        insertTrie(s);
        shablons.push_back(s);
    }
    cout << "Введите k - число вхождений шаблонов в каждую строку: ";
    int k;
    cin >> k;
    Aho_Corasik(k,data);
    BM(k, shablons, data);
}

int main()
{
	//int n = 10000;
	//generateFile(n, "input.txt");
    std::vector<Passenger*>data = readData("input.txt");
    start(data);
	return 0;
}
