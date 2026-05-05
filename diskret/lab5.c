#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

int graph[MAX][MAX];  // матрица смежности
int visited[MAX];     // массив посещенных вершин
int n;                // количество вершин

// Прототипы функций
void inputGraph();
void printGraph();
void DFS(int v, int component[], int *compSize);
void findComponents();
void DFSUtil(int v, bool visited[]);
void transposeGraph(int trans[MAX][MAX]);
void fillOrder(int v, bool visited[], int stack[], int *top);
void findStrongComponents();
int menu();

int main() {
    printf("Введите начальное количество вершин: ");
    scanf("%d", &n);
    
    // Инициализация матрицы нулями
    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < MAX; j++)
            graph[i][j] = 0;
    
    printf("\nВведите матрицу смежности (%d x %d):\n", n, n);
    inputGraph();
    
    while(1) {
        switch(menu()) {
            case 1: // Вывод матрицы
                printGraph();
                break;
            case 2: // Редактирование матрицы
                inputGraph();
                break;
            case 3: // Изменение количества вершин
                printf("Введите новое количество вершин (1-%d): ", MAX);
                scanf("%d", &n);
                if(n < 1) n = 1;
                if(n > MAX) n = MAX;
                printf("Введите новую матрицу смежности (%d x %d):\n", n, n);
                inputGraph();
                break;
            case 4: // Поиск компонент слабой связности
                findComponents();
                break;
            case 5: // Поиск компонент сильной связности (для ориентированного)
                findStrongComponents();
                break;
            case 6: // Выход
                printf("Выход из программы.\n");
                return 0;
            default:
                printf("Неверный выбор! Попробуйте снова.\n");
        }
    }
    return 0;
}

// Ввод матрицы смежности
void inputGraph() {
    printf("Введите элементы матрицы (0 или 1):\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
            if(graph[i][j] != 0 && graph[i][j] != 1) graph[i][j] = 0;
        }
    }
}

// Вывод матрицы
void printGraph() {
    printf("\nМатрица смежности (%d x %d):\n", n, n);
    printf("   ");
    for(int i = 0; i < n; i++) printf("%2d ", i+1);
    printf("\n");
    for(int i = 0; i < n; i++) {
        printf("%2d ", i+1);
        for(int j = 0; j < n; j++) {
            printf("%2d ", graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// DFS для обычной (слабой) связности
void DFS(int v, int component[], int *compSize) {
    visited[v] = 1;
    component[(*compSize)++] = v + 1; // +1 для вывода номеров с 1
    
    for(int i = 0; i < n; i++) {
        // Проверяем ребро в любом направлении (для неориентированного графа)
        if((graph[v][i] == 1 || graph[i][v] == 1) && !visited[i]) {
            DFS(i, component, compSize);
        }
    }
}

// Поиск компонент слабой связности
void findComponents() {
    // Сбрасываем visited
    for(int i = 0; i < n; i++) visited[i] = 0;
    
    int component[MAX];
    int compCount = 0;
    
    printf("\n=== КОМПОНЕНТЫ СЛАБОЙ СВЯЗНОСТИ ===\n");
    
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            int compSize = 0;
            DFS(i, component, &compSize);
            compCount++;
            
            printf("Компонента %d: { ", compCount);
            for(int j = 0; j < compSize; j++) {
                printf("%d", component[j]);
                if(j < compSize - 1) printf(", ");
            }
            printf(" }\n");
        }
    }
    
    printf("Всего компонент слабой связности: %d\n", compCount);
    printf("==================================\n\n");
}

// Вспомогательная DFS для сильной связности (неориентированная по ребрам)
void DFSUtil(int v, bool visited[]) {
    visited[v] = true;
    for(int i = 0; i < n; i++) {
        if(graph[v][i] == 1 && !visited[i]) {
            DFSUtil(i, visited);
        }
    }
}

// Транспонирование графа
void transposeGraph(int trans[MAX][MAX]) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            trans[i][j] = graph[j][i];
        }
    }
}

// Заполнение стека порядком завершения DFS
void fillOrder(int v, bool visited[], int stack[], int *top) {
    visited[v] = true;
    for(int i = 0; i < n; i++) {
        if(graph[v][i] == 1 && !visited[i]) {
            fillOrder(i, visited, stack, top);
        }
    }
    stack[(*top)++] = v;
}

// Поиск компонент сильной связности (алгоритм Косарайю)
void findStrongComponents() {
    bool visited[MAX];
    int stack[MAX];
    int top = 0;
    int trans[MAX][MAX];
    int compCount = 0;
    
    // Шаг 1: Инициализация
    for(int i = 0; i < n; i++) visited[i] = false;
    
    // Шаг 2: Заполнение стека порядком обхода
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            fillOrder(i, visited, stack, &top);
        }
    }
    
    // Шаг 3: Транспонирование графа
    transposeGraph(trans);
    
    // Шаг 4: Обход в порядке стека на транспонированном графе
    for(int i = 0; i < n; i++) visited[i] = false;
    
    printf("\n=== КОМПОНЕНТЫ СИЛЬНОЙ СВЯЗНОСТИ ===\n");
    
    while(top > 0) {
        int v = stack[--top];
        
        if(!visited[v]) {
            // DFS для поиска компоненты
            int component[MAX];
            int compSize = 0;
            int queue[MAX], front = 0, rear = 0;
            
            queue[rear++] = v;
            visited[v] = true;
            
            while(front < rear) {
                int cur = queue[front++];
                component[compSize++] = cur + 1;
                
                for(int i = 0; i < n; i++) {
                    if(trans[cur][i] == 1 && !visited[i]) {
                        visited[i] = true;
                        queue[rear++] = i;
                    }
                }
            }
            
            compCount++;
            printf("Компонента %d: { ", compCount);
            for(int j = 0; j < compSize; j++) {
                printf("%d", component[j]);
                if(j < compSize - 1) printf(", ");
            }
            printf(" }\n");
        }
    }
    
    printf("Всего компонент сильной связности: %d\n", compCount);
    printf("===================================\n\n");
}

// Меню программы
int menu() {
    int choice;
    printf("\n========== МЕНЮ ==========\n");
    printf("1. Вывести матрицу смежности\n");
    printf("2. Редактировать матрицу смежности\n");
    printf("3. Изменить количество вершин\n");
    printf("4. Найти компоненты СЛАБОЙ связности\n");
    printf("5. Найти компоненты СИЛЬНОЙ связности\n");
    printf("6. Выход\n");
    printf("==========================\n");
    printf("Ваш выбор: ");
    scanf("%d", &choice);
    return choice;
}
