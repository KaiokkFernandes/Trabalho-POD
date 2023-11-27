#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COURSES 1000
#define MAX_NAME_LENGTH 100

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char uf[3]; 
} Course;

Course courses[MAX_COURSES];
int total_courses = 0;

void merge(Course arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Course L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (strcmp(L[i].name, R[j].name) <= 0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Course arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void readCoursesFromFile(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    while(fscanf(file, "%d,%99[^,],%2s", &courses[total_courses].id, courses[total_courses].name, courses[total_courses].uf) == 3) {
        total_courses++;
        if (total_courses >= MAX_COURSES) break;
    }

    fclose(file);
}

int main() {
    readCoursesFromFile("microdados2021_arq1.txt");
    readCoursesFromFile("microdados2021_arq3.txt");

    mergeSort(courses, 0, total_courses - 1);

    
    for (int i = 0; i < total_courses; i++) {
        printf("ID: %d, Name: %s, UF: %s\n", courses[i].id, courses[i].name, courses[i].uf);
    }

    return 0;
}