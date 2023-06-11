#include <iostream>                 // biblioteca de transferencia de dados (bytes)
#include <fstream>                  // biblioteca padrão 
#include <string>                   // biblioteca de tipos string
#include <cstring>
#include <vector>                   // biblioteca de arrays e vetores
#include <algorithm>                // biblioteca de containers e operações algoritimicas
#include <random>                   // biblioteca geração de numeros randomicos
#include <chrono>                   // biblioteca para medição de tempo
#include <iomanip>                  // biblioteca 
#include <ctime>                    // biblioteca para medição do tempo 
#include <sstream>
#include <windows.h>                // biblioteca para obter informações sobre o consumo de memória
#include <cstdlib>
#include <psapi.h>


// Variaveis globais

int          n    = 0;        // valor de n 
std::string  sortTipo;        // Nome do algoritmo de sort

// Vetores para geração de n valores 
// A quantidade está definidda na variável n, que por sua vez é obtida a parti do arquivo de entrada
std::vector<int> sequence;
std::vector<int> reverseSequence;
std::vector<int> randomSequence;
std::vector<int> randomSequence1;
std::vector<int> randomSequence2;
std::vector<int> randomSequence3;
std::vector<int> randomSequence4;
std::vector<int> randomSequence5;

// Tempo de execução e uso de memória
std::string executionTimeResult;
std::string memoryUsageResult;
// Variável global para armazenar o consumo de memória em bytes
SIZE_T peakMemoryUsage;  


// Bubble Sort
// Referência: https://www.geeksforgeeks.org/bubble-sort/
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();                            // O(1)
    for (int i = 0; i < n - 1; i++) {              // O(n)
        bool swapped = false;                      // O(1)

        for (int j = 0; j < n - i - 1; j++) {      // O(n-1)
            if (arr[j] > arr[j + 1]) {             // O(n-1)-1
                std::swap(arr[j], arr[j + 1]);     // O(n)
                swapped = true;                    // O(1)
            }
        }

        if (!swapped)                              // O(1)
            break;                                 // O(1)
    }
}



int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];                      // O(1)
    int i = low - 1;                            // O(1)

    for (int j = low; j <= high - 1; j++) {     // O(n)
        if (arr[j] < pivot) {                   // O(1)
            i++;                                // O(1)
            std::swap(arr[i], arr[j]);          // O(1)
        }
    }

    std::swap(arr[i + 1], arr[high]);           // O(1)
    return i + 1;                               // O(1)
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {                           // O(1)
        int pi = partition(arr, low, high);     // O(n)
        quickSort(arr, low, pi - 1);            // O(log n)
        quickSort(arr, pi + 1, high);           // O(log n)
    }
}

void quickSort(std::vector<int>& arr) {
    int n = arr.size();                         // O(1)
    quickSort(arr, 0, n - 1);                   // O(n log n)
}


// Merge Sort
// Referência: https://www.geeksforgeeks.org/merge-sort/
void merge(std::vector<int>& arr, int low, int mid, int high) {
    int n1 = mid - low + 1;                 // O(1)
    int n2 = high - mid;                    // O(1)

    std::vector<int> left(n1);              // O(n1)
    std::vector<int> right(n2);             // O(n2)

    for (int i = 0; i < n1; i++)            // O(n1)
        left[i] = arr[low + i];             // O(1)
    for (int j = 0; j < n2; j++)            // O(n2)
        right[j] = arr[mid + 1 + j];        // O(1)

    int i = 0;                              // O(1)
    int j = 0;                              // O(1)
    int k = low;                            // O(1)

    while (i < n1 && j < n2) {              // O(n1 + n2)
        if (left[i] <= right[j]) {          // O(1)
            arr[k] = left[i];               // O(1)
            i++;                            // O(1)
        } else {
            arr[k] = right[j];              // O(1)
            j++;                            // O(1)
        }
        k++;                                // O(1)
    }

    while (i < n1) {                        // O(n1)
        arr[k] = left[i];                   // O(1)
        i++;                                // O(1)
        k++;                                // O(1)
    }

    while (j < n2) {                        // O(n2)
        arr[k] = right[j];                  // O(1)
        j++;                                // O(1)
        k++;                                // O(1)
    }
}




void mergeSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {                           // O(1)
        int mid = low + (high - low) / 2;       // O(1)
        mergeSort(arr, low, mid);               // Recursão para a primeira metade do array
        mergeSort(arr, mid + 1, high);          // Recursão para a segunda metade do array
        merge(arr, low, mid, high);             // Mescla as duas metades ordenadas
    }
}

void mergeSort(std::vector<int>& arr) {
    int n = arr.size();                     // Mescla as duas metades ordenadas
    mergeSort(arr, 0, n - 1);               // Chama a função de merge sort inicial
}





void lerArq(const std::string& arq) {
    // Abrindo o arquivo
    std::ifstream file(arq);  

    // Verificando se o arquivo foi aberto com sucesso
    if (file.is_open()) {  
        std::string line;
        int lineCount = 0;

        // Lendo as duas primeiras linhas
        while (getline(file, line) && lineCount < 2) {  
            if (lineCount == 0) {
                // Convertendo a primeira linha para um valor inteiro
                n = std::stoi(line);  
            } else {
                // Armazenando a segunda linha em uma string
                sortTipo = line;  
            }
            lineCount++;
        }

        file.close();  // Fechando o arquivo

        // Imprimindo os valores lidos
        std::cout << "Algoritmo : " << sortTipo << std::endl;
        std::cout << "n         : " << n << std::endl;

    } else {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
    }
}



void randomizaVector(std::vector<int>& arr){
    arr.resize(n);
    std::iota(arr.begin(), arr.end(), 1);
    std::random_device rd;
    std::size_t seed;
    if (rd.entropy())
        seed = rd();
    else
        seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 g(seed);
    std::shuffle(arr.begin(), arr.end(), g);
}


// Funcao para gerar os vetores com o melhor, pior e o caso medio.
void preencheVetores(int n) {

    // limpa os vetores 
    sequence.clear();
    reverseSequence.clear();
    randomSequence.clear();
    randomSequence1.clear();
    randomSequence2.clear();
    randomSequence3.clear();
    randomSequence4.clear();
    randomSequence5.clear();

    // Preenchendo o primeiro vetor com uma sequência de 1 até n
    for (int i = 1; i <= n; i++) {
        sequence.push_back(i);
    }

    // Preenchendo o segundo vetor com uma sequência inversa de n até 1
    for (int i = n; i >= 1; i--) {
        reverseSequence.push_back(i);
    }

    // Caso médio
    // Preenchendo os 5 vetores  com uma sequência aleatória de 1 até n
    randomizaVector(randomSequence1);
    randomizaVector(randomSequence2);
    randomizaVector(randomSequence3);
    randomizaVector(randomSequence4);
    randomizaVector(randomSequence5);

}




// Grava Arquivo
void gravaCSV(const std::string& filename, const std::string& algorithm, const std::string& tipoCaso, int n, const std::string& executionTime, const std::string& memoryUsage) {
    std::ofstream file;
    // Abrir o arquivo no modo de append
    file.open(filename, std::ios_base::app);

    // Testa se existe
    if (file.is_open()) {

        // Obtem data e hora
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);

        // data e hora atual formatada
        std::tm* current_time = std::localtime(&now_c);
        std::stringstream ss;
        ss << std::put_time(current_time, "%Y-%m-%d-%H:%M:%S");

        // Escrever a linha no arquivo CSV
        file << ss.str() << "," << algorithm << "," << n << "," << tipoCaso << "," << executionTime << "," << memoryUsage << "\n";

        file.close();
    } else {
        std::cout << "Falha ao abrir o arquivo " << filename << std::endl;
    }
}


// Função para pegar a quantidade de uso de memoria em megabytes
void getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc), sizeof(pmc));
    peakMemoryUsage = pmc.PeakWorkingSetSize;

    // Convertendo o consumo de memória para string
    memoryUsageResult = std::to_string(peakMemoryUsage /(1024 * 1024)) ; // 

}


// Função para execução do algoritmo e medição do tempo
std::string measureExecutionTime(const std::string& algorithm, std::vector<int>& arr, int low, int high) {
    auto start = std::chrono::steady_clock::now();

    getMemoryUsage();  // Obtém o consumo de memória antes da ordenação

    // Chamada das funções de ordenação
    if (algorithm == "quickSort") {
        quickSort(arr, low, high);
    } else if (algorithm == "bubbleSort") {
        bubbleSort(arr);
    } else if (algorithm == "mergeSort") {
        mergeSort(arr, low, high);
    }
    std::cout << "terminou " << std::endl;
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::stringstream ss;
    ss << duration ;

    getMemoryUsage();  // Obtém o consumo de memória após a ordenação

    return ss.str();

}



int main() {

    // Lendo o arquivo de texto
    std::string filename = "entrada.txt";  
    lerArq(filename);


    // Preenche os vetores com a quantidade n
    preencheVetores(n);

  
    // Melhor caso
    //--------------------------------------------------------------------------------------------------
    std::cout << "Melhor caso " << std::endl;
    executionTimeResult = measureExecutionTime(sortTipo, sequence, 0, sequence.size() - 1);
    // Grava o resultado no arquivo .csv
    gravaCSV("Resultado.csv", sortTipo, "melhor", n, executionTimeResult, memoryUsageResult);
    

    // Pior caso
    std::cout << "Pior caso " << std::endl;
    //--------------------------------------------------------------------------------------------------
    executionTimeResult = measureExecutionTime(sortTipo, reverseSequence, 0, reverseSequence.size() - 1);
    // Grava o resultado no arquivo .csv
    gravaCSV("Resultado.csv", sortTipo, "pior", n, executionTimeResult, memoryUsageResult);
    

    // Caso Médio
    //--------------------------------------------------------------------------------------------------
    //Guarda a media dos processamentos
    int executionTimeResultSoma = 0;
    int memoryUsageResultSoma = 0;

    float executionTimeResultMedia = 0;
    float memoryUsageResultMedia = 0;

    // Executa primeira lista randomica
    std::cout << "Caso Medio 1" << std::endl;
    executionTimeResult = measureExecutionTime(sortTipo, randomSequence1, 0, randomSequence1.size() - 1);   
    executionTimeResultSoma = executionTimeResultSoma + stoi(executionTimeResult);
    memoryUsageResultSoma = memoryUsageResultSoma + stoi(memoryUsageResult);

    std::cout << "Caso Medio 2" << std::endl;
    executionTimeResult = measureExecutionTime(sortTipo, randomSequence2, 0, randomSequence2.size() - 1);   
    executionTimeResultSoma = executionTimeResultSoma + stoi(executionTimeResult);
    memoryUsageResultSoma = memoryUsageResultSoma + stoi(memoryUsageResult);

    std::cout << "Caso Medio 3" << std::endl;
    executionTimeResult = measureExecutionTime(sortTipo, randomSequence3, 0, randomSequence3.size() - 1);   
    executionTimeResultSoma = executionTimeResultSoma + stoi(executionTimeResult);
    memoryUsageResultSoma = memoryUsageResultSoma + stoi(memoryUsageResult);

    std::cout << "Caso Medio 4" << std::endl;
    executionTimeResult = measureExecutionTime(sortTipo, randomSequence4, 0, randomSequence4.size() - 1);   
    executionTimeResultSoma = executionTimeResultSoma + stoi(executionTimeResult);
    memoryUsageResultSoma = memoryUsageResultSoma + stoi(memoryUsageResult);

    std::cout << "Caso Medio 5" << std::endl;
    executionTimeResult = measureExecutionTime(sortTipo, randomSequence5, 0, randomSequence5.size() - 1);   
    executionTimeResultSoma = executionTimeResultSoma + stoi(executionTimeResult);
    memoryUsageResultSoma = memoryUsageResultSoma + stoi(memoryUsageResult);

    // Calcula as médias
    executionTimeResultMedia = executionTimeResultSoma /5;
    memoryUsageResultMedia = memoryUsageResultSoma / 5;

    // Atualiza as médias
    executionTimeResult = std::to_string(executionTimeResultMedia);
    memoryUsageResult   = std::to_string(memoryUsageResultMedia);

    // Grava o resultado no arquivo .csv
    gravaCSV("Resultado.csv", sortTipo, "medio", n, executionTimeResult, memoryUsageResult);
    
    std::cout << "Fim do processamento " << std::endl;

    return 0;
}

