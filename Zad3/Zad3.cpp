#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>

// ввод матрицы смежности с клавиатуры
std::vector<std::vector<int>> inputAdjacencyMatrixFromKeyboard(int summit_num)
{
    std::cout << "Введите количество вершин графа: ";
    std::cin >> summit_num;

    std::vector<std::vector<int>> Matrix(summit_num, std::vector<int>(summit_num));
    std::cout << "Введите матрицу смежности (строка за строкой):\n";
    for (int i = 0; i < summit_num; i++)
    {
        for (int j = 0; j < summit_num; j++)
            std::cin >> Matrix[i][j];
    }

    return Matrix;
}

// ввод матрицы смежности из файла
std::vector<std::vector<int>> inputAdjacencyMatrixFromFile(int summit_num, const std::string filename)
{
    std::ifstream file("..\\" + filename + ".txt");
    if (!file.is_open()) 
    {
        std::cout << "Ошибка при открытии файла!\n";
        return {};
    }

    file >> summit_num;
    std::vector<std::vector<int>> Matrix(summit_num, std::vector<int>(summit_num));
    for (int i = 0; i < summit_num; ++i)
    {
        for (int j = 0; j < summit_num; ++j) 
            file >> Matrix[i][j];
    }

    file.close();

    std::cout << "Матрица вычитана\n";

    return Matrix;
}

// вывод матрицы инцидентности
void printIncidenceMatrix(const std::vector<std::vector<int>> Matrix)
{
    // кол-во вершин графа
    size_t summit_num = Matrix.size();

    std::vector<std::vector<int>> incMatrix;
    int edges = 0;

    // считаем количество рёбер и строим матрицу инцидентности
    for (int i = 0; i < summit_num; i++)
    {
        for (int j = i; j < summit_num; j++)
        {
            // если 1, значит между вершинами есть ребро
            if (Matrix[i][j] == 1)
            {
                // высчитываем кол-во рёбер
                edges++;
                
                // ребро
                std::vector<int> edgeInc(summit_num, 0);
                edgeInc[i] = 1;
                edgeInc[j] = 1;

                // ребро закидываем в список рёбер
                incMatrix.push_back(edgeInc);
            }
        }
    }

    std::cout << "\nМатрица инцидентности:\n";
    for (int i = 0; i < summit_num; i++)
    {
        for (int j = 0; j < edges; j++) 
        {
            std::cout << incMatrix[j][i] << " ";
        }
        std::cout << std::endl;
    }
}

// вывод списка смежности
void printAdjacencyList(const std::vector<std::vector<int>> Matrix)
{
    size_t summit_num = Matrix.size();
    std::cout << "Список смежности:\n";
    for (int i = 0; i < summit_num; i++)
    {
        std::cout << i + 1 << ": ";
        for (int j = 0; j < summit_num; j++)
        {
            // проверка, связаны ли вершины графа
            if (Matrix[i][j] == 1)
            {
                std::cout << j + 1 << " ";
            }
        }
        std::cout << std::endl;
    }
}

// вывод списка инцидентности
void printIncidenceList2(const std::vector<std::vector<int>> Matrix)
{
    std::unordered_map<int, std::vector<int>> incidentEdges;

    size_t summit_num = Matrix[0].size();
    for (int i = 0; i < summit_num; i++)
    {
        for (int j = 0; j < summit_num; j++)
        {
            if (Matrix[i][j] != 0)
                incidentEdges[i].push_back(j);
        }
    }

    std::cout << "Список инцидентности:" << std::endl;
    for (const auto& kv : incidentEdges) {
        std::cout << "Ребро: " << kv.first + 1 << std::endl;
        for (int vertex : kv.second) 
            std::cout << "\tИнцидентная вершина: " << vertex + 1 << std::endl;
    }
}

// меню программы
void menu() 
{
    std::vector<std::vector<int>> Matrix;
    int summit_num = 0;
    int action;

    do 
    {
        // вывод меню
        std::cout << "\nМеню:\n";
        std::cout << "1. Ввести граф с клавиатуры\n";
        std::cout << "2. Ввести граф из файла\n";
        std::cout << "3. Вывести матрицу инцидентности\n";
        std::cout << "4. Вывести списки смежности\n";
        std::cout << "5. Вывести списки инцидентности\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> action;

        // управление меню через свич-кейс
        switch (action)
        {
            case 1: 
            {
                // ввод с клавитуры
                Matrix = inputAdjacencyMatrixFromKeyboard(summit_num);
                break;
            }
            case 2: 
            {
                // ввод с файла
                std::string filename;
                std::cout << "Введите имя целевого файла: ";
                std::cin >> filename;
                Matrix = inputAdjacencyMatrixFromFile(summit_num, filename);
                break;
            }
            case 3: 
            {
                // матрица инциденций
                if (Matrix.empty())
                    std::cout << "Не введен граф\n";
                else
                    printIncidenceMatrix(Matrix);
                break;
            }
            case 4: 
            {
                if (Matrix.empty())
                    std::cout << "Не введен граф\n";
                else
                    printAdjacencyList(Matrix);
                break;
            }
            case 5: 
            {
                if (Matrix.empty())
                    std::cout << "Не введен граф\n";
                else
                    printIncidenceList2(Matrix);
                break;
            }
            case 0:
                std::cout << "Выход\n";
                break;
            default:
                std::cout << "Несуществующий ключ\n";
        }
    } 
    while (action != 0);
}

int main() 
{
    setlocale(0, "");
    menu();
    return 0;
}
