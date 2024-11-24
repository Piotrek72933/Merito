#include <iostream>
#include <filesystem>
#include <fstream>
#include <locale>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
namespace fs = filesystem;

//zad1 kod jest poniżej

/*
Funkcja find służy do wyszukiwania
pierwszego wystąpienia podciągu w łańcuchu znaków. Zwraca pozycję pierwszego
wystąpienia lub std::string::npos, jeśli nie znaleziono.

Wyszukiwanie słowa "Word";
size_t pos = text.find("World");

Funkcja substr zwraca podciąg łańcucha znaków.
Można określić pozycję początkową oraz długość podciągu.

Pobieranie podciągu od pozycji 7, o długości 5 znaków
 std::string sub = text.substr(7, 5);


*/
// zad1
void zad1(string tekst)
{
    //std::string text = "Hello, World!";

    std::cout << "Przed zmianą: " << tekst << std::endl;
    tekst.replace(7, 5, "C++");
    std::cout << "Po zmianie: " << tekst << std::endl;
}

//zad2

/*
get():

Wczytuje pojedynczy znak (możesz także używać go do wczytania całych linii, ale bez usuwania znaków nowej linii).
Nie ignoruje białych znaków ani nowych linii, co oznacza, że możesz wczytać nawet pojedyncze znaki, w tym znak nowej linii.

getline():

Wczytuje całą linię (do napotkania znaku nowej linii), automatycznie usuwa znak nowej linii.
Jest użyteczne, gdy chcesz wczytać dane zawierające spacje.

read():

Wczytuje określoną liczbę bajtów z wejścia (zwykle w postaci binarnej).
Nie przetwarza znaków, nie ignoruje nowych linii, nie jest powszechnie używane do wczytywania tekstu.

Operator >>:

Wczytuje dane z wejścia do zmiennych o określonym typie (np. int, double, string).
Automatycznie pomija białe znaki (w tym nowe linie, spacje) przed wczytywaniem danych.
*/


void zad2() {
    char c;
    std::string str;
    int num;

    std::cout << "get(): ";
    std::cin.get(c);  // Wczytanie pojedynczego znaku
    std::cout << "Wczytano: " << c << "\n";

    std::cin.ignore();  // Ignorowanie nowej linii po wczytaniu znaku
    std::cout << "getline(): ";
    std::getline(std::cin, str);  // Wczytanie całej linii tekstu
    std::cout << "Wczytano: " << str << "\n";

    std::cout << ">>: ";
    std::cin >> num;  // Wczytanie liczby
    std::cout << "Wczytano: " << num << "\n";

    std::cin.ignore();  // Ignorowanie nowej linii po wczytaniu liczby
    char buffer[10];
    std::cout << "read(): ";
    std::cin.read(buffer, 10);  // Wczytanie 10 bajtów
    std::cout << "Wczytano: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << buffer[i];  // Wypisanie wczytanych bajtów
    }
    std::cout << "\n";


}


//zad3
int zad3(int argc, char* argv[]) {
    // Ustawienie lokalizacji globalnej w celu obsługi międzynarodowych znaków (np. polskich znaków)
    std::locale::global(std::locale(""));

    // Sprawdzanie, czy użytkownik podał dwa argumenty (katalog i plik)
    if (argc != 3) {
        std::cout << "Użycie: " << argv[0] << " <katalog> <plik>" << std::endl;
        return 1;
    }

    // Pobieranie ścieżek katalogu i pliku z argumentów wiersza poleceń
    fs::path directoryPath = argv[1];
    fs::path filePath = argv[2];

    // Sprawdzanie, czy katalog istnieje. Jeśli nie, to go tworzymy.
    // ??? Sprawdzamy, czy katalog już istnieje, jeśli nie, tworzymy go
    if (!fs::exists(directoryPath)) {
        if (fs::create_directory(directoryPath)) {  // Tworzenie katalogu
            std::cout << "Utworzono katalog: " << directoryPath << std::endl;
        }
        else {
            std::cout << "Nie udało się utworzyć katalogu." << std::endl;
            return 1;  // Zakończenie programu w przypadku niepowodzenia
        }
    }
    else {
        std::cout << "Katalog już istnieje." << std::endl;
    }

    // Tworzenie i zapis do pliku za pomocą ofstream
    // ??? Tworzymy plik i zapisujemy do niego dane
    std::ofstream outputFile(filePath);  // Otwieramy plik do zapisu
    if (outputFile.is_open()) {  // Sprawdzamy, czy plik został otwarty pomyślnie
        outputFile << "To jest zawartość pliku." << std::endl;  // Zapisujemy tekst do pliku
        outputFile.close();  // Zamykamy plik po zapisaniu
        std::cout << "Utworzono plik: " << filePath << std::endl;
    }
    else {
        std::cout << "Nie udało się utworzyć pliku." << std::endl;
        return 1;  // Zakończenie programu, jeśli nie udało się otworzyć pliku
    }

    // Kopiowanie pliku do nowej lokalizacji
    // ??? Kopiujemy plik do nowego katalogu, nadpisując istniejący plik
    fs::path copiedFilePath = directoryPath / "skopiowany_plik.txt";  // Tworzymy pełną ścieżkę dla skopiowanego pliku
    try {
        fs::copy_file(filePath, copiedFilePath, fs::copy_options::overwrite_existing);  // Kopiujemy plik, nadpisując, jeśli już istnieje
        std::cout << "Skopiowano plik do: " << copiedFilePath << std::endl;
    }
    catch (const fs::filesystem_error& e) {  // Obsługa wyjątków, jeśli wystąpią błędy podczas kopiowania
        std::cout << "Błąd podczas kopiowania pliku: " << e.what() << std::endl;
        return 1;  // Zakończenie programu w przypadku błędu
    }

    // Wyświetlanie zawartości katalogu
    // ??? Wyświetlamy wszystkie pliki i katalogi w wskazanym katalogu
    std::cout << "Zawartość katalogu:" << std::endl;
    for (const auto& entry : fs::directory_iterator(directoryPath)) {  // Iteracja po wszystkich plikach w katalogu
        std::cout << entry.path().filename() << std::endl;  // Wyświetlanie nazw plików
    }

    // Sprawdzanie atrybutów pliku
    // ??? Wyświetlamy atrybuty pliku: rozmiar i czas ostatniej modyfikacji
    std::cout << "Atrybuty pliku " << filePath << ":" << std::endl;
    if (fs::exists(filePath)) {  // Sprawdzamy, czy plik istnieje
        std::cout << "Rozmiar: " << fs::file_size(filePath) << " bajtów" << std::endl;  // Wyświetlamy rozmiar pliku
        std::cout << "Czas ostatniej modyfikacji: " << fs::last_write_time(filePath).time_since_epoch().count() << std::endl;  // Wyświetlamy czas ostatniej modyfikacji pliku
    }
    else {
        std::cout << "Plik nie istnieje." << std::endl;  // Informacja, jeśli plik nie istnieje
    }


}

//zad4



void zad4() {
    // 1. Sprawdzanie, czy plik istnieje
    fs::path file = "tekst.txt";
    if (fs::exists(file))
        std::cout << "Plik '" << file << "' istnieje." << std::endl;
    else {
        std::cout << "Plik '" << file << "' nie istnieje." << std::endl;
    }

    // 2. Tworzenie katalogu
    fs::path dir = "nowy_katalog";
    if (fs::create_directory(dir)) {
        std::cout << "Katalog '" << dir << "' został utworzony." << std::endl;
    }
    else {
        std::cout << "Nie udało się utworzyć katalogu '" << dir << "'." << std::endl;
    }

    // 3. Akutalna sciezka pliku
    cout << "aaa" << endl;
    cout << fs::current_path() << endl;
}

// zad5
int zad5(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Podaj nazwy plików jako argumenty wywołania programu." << std::endl;
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        std::ifstream file(argv[i]);
        if (!file) {
            std::cerr << "Nie można otworzyć pliku: " << argv[i] << std::endl;
            continue;
        }

        std::cout << "Zawartość pliku: " << argv[i] << std::endl;
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }

        file.close();
        std::cout << std::endl;
    }

    return 0;
}

// zad6
void zad6() {
    std::string filename = "liczba.txt";

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku: " << filename << std::endl;
        return;
    }

    int suma = 0;
    double srednia = 0.0;
    int ilosc = 0;
    int liczba = 0;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        while (iss >> liczba) {
            suma += liczba;
            ilosc++;
        }
    }

    if (ilosc > 0) {
        srednia = static_cast<double>(suma) / ilosc;
    }

    file.close();

    std::cout << "Suma liczb: " << suma << "\n";
    std::cout << "Średnia liczb: " << srednia << "\n";
}

// zad7
void zad7(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku: " << filename << std::endl;
        return;
    }

    int liczbaZnakow = 0;
    int liczbaSlow = 0;
    int liczbaLinii = 0;
    std::string line;

    while (std::getline(file, line)) {
        liczbaLinii++;

        std::istringstream stream(line);
        std::string word;
        while (stream >> word) {
            liczbaSlow++;
        }

        liczbaZnakow += line.length();
    }

    file.close();

    std::cout << "Liczba linii: " << liczbaLinii << std::endl;
    std::cout << "Liczba słów: " << liczbaSlow << std::endl;
    std::cout << "Liczba znaków: " << liczbaZnakow << std::endl;
}

// zad8
void zad8() {
    std::string filename = "liczby.txt";

    std::ifstream file("liczba2.txt");

    string line;
    string str;
    int suma;

    while (std::getline(file, line)) {
        istringstream iss(line);

        while (iss >> str) {
            suma = 0;
            char ostatni = str[str.length() - 1];
            cout << str << "\n";

            if ((ostatni - '0') % 2 == 0) {
                cout << "Podzielne przez 2 " << "Liczba parzysta" << "\n";
            }
            else if ((ostatni - '0') % 5 == 0) {
                cout << "Podzielne przez 5 " << "Liczba nieparzysta" << "\n";
            }
            else {
                cout << "Liczba nieparzysta" << endl;
            }
        }
    }
}

//zad 9 za trudne dla mnie







int main(int argc, char* argv[]) {

    //zad1("Hello, World!");
    // zad2();
   //zad3(argc, argv);
    //zad4();
    zad5(argc, argv);
    //zad6();
    std::string filename = "tekst.txt";  
    //zad7(filename);
    //zad8();
    

    return 0;
}



