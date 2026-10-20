#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICES 10
#define MAX_EDGES 20
#define INF 999999

typedef struct {
    int matrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

void dfs_check(int u, int matrix[MAX_VERTICES][MAX_VERTICES], int visited[]) {
    visited[u] = 1;
    for (int v = 0; v < MAX_VERTICES; v++) {
        if (matrix[u][v] != 0 && !visited[v]) {
            dfs_check(v, matrix, visited);
        }
    }
}

int is_connected(int matrix[MAX_VERTICES][MAX_VERTICES]) {
    int visited[MAX_VERTICES] = { 0 };
    dfs_check(0, matrix, visited);
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (visited[i] == 0) return 0;
    }
    return 1;
}

void generate_graph(Graph* g) {
    while (1) {
        for (int i = 0; i < MAX_VERTICES; i++) {
            for (int j = 0; j < MAX_VERTICES; j++) {
                g->matrix[i][j] = 0;
            }
        }

        int connected[MAX_VERTICES] = { 0 };
        connected[0] = 1;
        int current_edges = 0;

        for (int i = 1; i < MAX_VERTICES; i++) {
            int u;
            do {
                u = rand() % MAX_VERTICES;
            } while (connected[u] == 0);

            int weight = (rand() % 100) + 1;
            g->matrix[u][i] = weight;
            g->matrix[i][u] = weight;
            connected[i] = 1;
            current_edges++;
        }

        while (current_edges < MAX_EDGES) {
            int u = rand() % MAX_VERTICES;
            int v = rand() % MAX_VERTICES;

            if (u != v && g->matrix[u][v] == 0) {
                int weight = (rand() % 100) + 1;
                g->matrix[u][v] = weight;
                g->matrix[v][u] = weight;
                current_edges++;
            }
        }

        if (is_connected(g->matrix)) {
            break;
        }
    }
}

void print_graph_edges(Graph* g) {
    printf("Graph\n");
    printf("Vertices : %d\n", MAX_VERTICES);
    printf("Edges    : %d\n\n", MAX_EDGES);
    printf("Edges\n");
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = i + 1; j < MAX_VERTICES; j++) {
            if (g->matrix[i][j] != 0) {
                printf("(%d, %d) Weight: %d\n", i, j, g->matrix[i][j]);
            }
        }
    }
    printf("\n");
}

void print_path(int next[MAX_VERTICES][MAX_VERTICES], int u, int v) {
    printf("%d", u);
    while (u != v) {
        u = next[u][v];
        printf(" -> %d", u);
    }
    printf("\n");
}

void find_all_shortest_paths(Graph* g) {
    int dist[MAX_VERTICES][MAX_VERTICES];
    int next[MAX_VERTICES][MAX_VERTICES];

    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            if (i == j) {
                dist[i][j] = 0;
                next[i][j] = -1;
            }
            else if (g->matrix[i][j] != 0) {
                dist[i][j] = g->matrix[i][j];
                next[i][j] = j;
            }
            else {
                dist[i][j] = INF;
                next[i][j] = -1;
            }
        }
    }

    for (int k = 0; k < MAX_VERTICES; k++) {
        for (int i = 0; i < MAX_VERTICES; i++) {
            for (int j = 0; j < MAX_VERTICES; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
    }

    printf("Shortest Paths\n\n");
    int pair_count = 0;

    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = i + 1; j < MAX_VERTICES; j++) {
            printf("%d -> %d\n", i, j);
            printf("Path     : ");
            print_path(next, i, j);
            printf("Distance : %d\n\n", dist[i][j]);
            pair_count++;
        }
    }

    printf("Total vertex pairs : %d\n", pair_count);
}

int main() {
    srand((unsigned int)time(NULL));

    Graph g;
    generate_graph(&g);
    print_graph_edges(&g);
    find_all_shortest_paths(&g);

    return 0;
}