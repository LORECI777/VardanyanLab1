#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Структура для трубы
struct Pipe {
    string name;
    double length;
    double diameter;
    bool inRepair;

    void readFromConsole() {
        cout << "Vvedite name trubi: ";
        cin.ignore();
        getline(cin, name);
        cout << "Vvedite dlinu trubi (km): ";
        cin >> length;
        cout << "Vvedite diametr trubi (m): ";
        cin >> diameter;
        cout << "Truba v remonte? (1 - yes, 0 - no): ";
        int repair;
        cin >> repair;
        inRepair = (repair == 1);
    }

    void printToConsole() const {
        cout << "Name trubi: " << name << endl;
        cout << "Dlina trubi: " << length << " km" << endl;
        cout << "Diametr trubi: " << diameter << " m" << endl;
        cout << "Truba v remonte?: " << (inRepair ? "Yes" : "No") << endl;
    }

    void editRepair() {
        cout << "Truba v remonte? (1 - yes, 0 - no): ";
        int repair;
        cin >> repair;
        inRepair = (repair == 1);
    }
};

// Структура для компрессорной станции
struct CompressorStation {
    string name;
    int totalDepartments;
    int workingDepartments;
    double efficiency;

    void readFromConsole() {
        cout << "Vvedite name KC: ";
        cin.ignore();
        getline(cin, name);
        cout << "Obshee kolichestvo cehov: ";
        cin >> totalDepartments;
        cout << "Kolichestvo rabotayushih cehov: ";
        cin >> workingDepartments;
        cout << "Effectivnost KC (procent): ";
        cin >> efficiency;
    }

    void printToConsole() const {
        cout << "Name KC: " << name << endl;
        cout << "Obshee kolichestvo cehov: " << totalDepartments << endl;
        cout << "Kolichestvo rabotayushih cehov: " << workingDepartments << endl;
        cout << "Effectivnost KC: " << efficiency << "%" << endl;
    }

    void startStopDepartment() {
        cout << "Zapustit or ostanovit ceh? (1 - zapustit, 0 - ostanovit): ";
        int action;
        cin >> action;
        if (action == 1) {
            if (workingDepartments < totalDepartments) {
                workingDepartments++;
                cout << "Ceh zapushen." << endl;
            }
            else {
                cout << "Vse cexi zapusheni." << endl;
            }
        }
        else if (action == 0) {
            if (workingDepartments > 0) {
                workingDepartments--;
                cout << "Ceh ostanovlen." << endl;
            }
            else {
                cout << "Net rabotayushih cehov." << endl;
            }
        }
        else {
            cout << "Nnekorectniy vvod." << endl;
        }
    }
};

// Функция для сохранения данных в файл
void saveToFile(const vector<Pipe>& pipes, const vector<CompressorStation>& stations, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "Pipes:" << endl;
        for (const auto& pipe : pipes) {
            file << pipe.name << " " << pipe.length << " " << pipe.diameter << " " << (pipe.inRepair ? 1 : 0) << endl;
        }
        file << "Compressor Stations:" << endl;
        for (const auto& station : stations) {
            file << station.name << " " << station.totalDepartments << " " << station.workingDepartments << " " << station.efficiency << endl;
        }
        file.close();
        cout << "Dannie sohraneni v file." << endl;
    }
    else {
        cout << "Ne udalos otkrit file dlya zapisi." << endl;
    }
}

// Функция для загрузки данных из файла
void loadFromFile(vector<Pipe>& pipes, vector<CompressorStation>& stations, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line == "Pipes:") {
                while (getline(file, line)) {
                    if (line.empty()) break;
                    size_t pos1 = line.find(' ');
                    size_t pos2 = line.find(' ', pos1 + 1);
                    size_t pos3 = line.find(' ', pos2 + 1);
                    size_t pos4 = line.find(' ', pos3 + 1);
                    if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos && pos4 != string::npos) {
                        Pipe pipe;
                        pipe.name = line.substr(0, pos1);
                        pipe.length = stod(line.substr(pos1 + 1, pos2 - pos1 - 1));
                        pipe.diameter = stod(line.substr(pos2 + 1, pos3 - pos2 - 1));
                        pipe.inRepair = (line.substr(pos3 + 1, pos4 - pos3 - 1) == "1");
                        pipes.push_back(pipe);
                    }
                }
            }
            else if (line == "Compressor Stations:") {
                while (getline(file, line)) {
                    if (line.empty()) break;
                    size_t pos1 = line.find(' ');
                    size_t pos2 = line.find(' ', pos1 + 1);
                    size_t pos3 = line.find(' ', pos2 + 1);
                    size_t pos4 = line.find(' ', pos3 + 1);
                    if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos && pos4 != string::npos) {
                        CompressorStation station;
                        station.name = line.substr(0, pos1);
                        station.totalDepartments = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
                        station.workingDepartments = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
                        station.efficiency = stod(line.substr(pos3 + 1, pos4 - pos3 - 1));
                        stations.push_back(station);
                    }
                }
            }
        }
        file.close();
        cout << "Dannie zagruzheni is fila." << endl;
    }
    else {
        cout << "Ne udalos open file dlya chtenia." << endl;
    }
}

int main() {
    vector<Pipe> pipes;
    vector<CompressorStation> stations;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Add trubu" << endl;
        cout << "2. Add KC" << endl;
        cout << "3. Prosmotr vseh obectov" << endl;
        cout << "4. Redactirovat trubu" << endl;
        cout << "5. Redactirovat KC" << endl;
        cout << "6. Sohranit dannie v file" << endl;
        cout << "7. Zagrusit dannie is fila" << endl;
        cout << "0. Vihod" << endl;
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            Pipe pipe;
            pipe.readFromConsole();
            pipes.push_back(pipe);
            break;
        }
        case 2: {
            CompressorStation station;
            station.readFromConsole();
            stations.push_back(station);
            break;
        }
        case 3: {
            cout << "Trubi:" << endl;
            for (const auto& pipe : pipes) {
                pipe.printToConsole();
                cout << endl;
            }
            cout << "Kompressornie stancii:" << endl;
            for (const auto& station : stations) {
                station.printToConsole();
                cout << endl;
            }
            break;
        }
        case 4: {
            if (pipes.empty()) {
                cout << "Net trub dlya redactirovania." << endl;
                break;
            }
            cout << "Viberite trubu dlya redactirovania (nomer trubi): ";
            int pipeIndex;
            cin >> pipeIndex;
            if (pipeIndex < 1 || pipeIndex > pipes.size()) {
                cout << "Neccorectniy nomer trubi." << endl;
                break;
            }
            pipes[pipeIndex - 1].editRepair();
            break;
        }
        case 5: {
            if (stations.empty()) {
                cout << "Net KC dlya redactirovania." << endl;
                break;
            }
            cout << "Viberite KC dlya redactirovania (nomer KC): ";
            int stationIndex;
            cin >> stationIndex;
            if (stationIndex < 1 || stationIndex > stations.size()) {
                cout << "Neccorectniy nomer KC." << endl;
                break;
            }
            stations[stationIndex - 1].startStopDepartment();
            break;
        }
        case 6: {
            cout << "Name fila dlya redactirovania: ";
            cin.ignore();
            string filename;
            getline(cin, filename);
            saveToFile(pipes, stations, filename);
            break;
        }
        case 7: {
            cout << "Name fila dlya zagruzki: ";
            cin.ignore();
            string filename;
            getline(cin, filename);
            loadFromFile(pipes, stations, filename);
            break;
        }
        case 0:
            return 0;
        default:
            cout << "Neccorectniy vibor! Povtorite popitku)" << endl;
        }
    }

    return 0;
}