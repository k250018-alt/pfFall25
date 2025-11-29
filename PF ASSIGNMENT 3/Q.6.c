#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME 100
#define MAX_BATCH 20
#define MAX_DATE 11
#define FILENAME "members.dat"

typedef struct {
    int id;
    char name[MAX_NAME];
    char batch[MAX_BATCH];
    char memType[10];
    char regDate[MAX_DATE];
    char dob[MAX_DATE];
    char interest[20];
} Stud;

typedef struct {
    Stud* arr;
    int cnt;
    int cap;
} DB;

DB* createDB();
void freeDB(DB* db);
int loadDB(DB* db, const char* fn);
int saveDB(const DB* db, const char* fn);
int addStud(DB* db, Stud s, const char* fn);
int updStud(DB* db, int id);
int delStud(DB* db, int id, const char* fn);
void viewAll(const DB* db);
void viewBatch(const DB* db);
int findStud(const DB* db, int id);
void getDate(char* buf);
int validDate(const char* dt);
void clearBuf();
void regStud(DB* db);
void stressTest(DB* db);


DB* createDB() {
    DB* db = malloc(sizeof(DB));
    if (!db) {
        fprintf(stderr, "Memory error\n");
        return NULL;
    }

    db->arr = malloc(10 * sizeof(Stud));
    if (!db->arr) {
        fprintf(stderr, "Memory error\n");
        free(db);
        return NULL;
    }

    db->cnt = 0;
    db->cap = 10;
    return db;
}

void freeDB(DB* db) {
    if (!db) return;
    free(db->arr);
    free(db);
}

int loadDB(DB* db, const char* fn) {
    if (!db || !fn) return 0;

    FILE* f = fopen(fn, "rb");
    if (!f) {
        printf("No existing database.\n");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (sz <= 0) {
        fclose(f);
        return 1;
    }

    int cnt = sz / sizeof(Stud);
    if (cnt <= 0) {
        fclose(f);
        return 1;
    }

    if (cnt > db->cap) {
        Stud* newArr = realloc(db->arr, cnt * sizeof(Stud));
        if (!newArr) {
            fclose(f);
            return 0;
        }
        db->arr = newArr;
        db->cap = cnt;
    }

    size_t read = fread(db->arr, sizeof(Stud), cnt, f);
    fclose(f);

    if (read != cnt) {
        fprintf(stderr, "Error: Corrupted file\n");
        return 0;
    }

    db->cnt = cnt;
    printf("Loaded %d records\n", cnt);
    return 1;
}

int saveDB(const DB* db, const char* fn) {
    FILE* f = fopen(fn, "wb");
    if (!f) {
        fprintf(stderr, "File write error\n");
        return 0;
    }

    size_t written = fwrite(db->arr, sizeof(Stud), db->cnt, f);
    fclose(f);

    if (written != db->cnt) {
        fprintf(stderr, "Write error\n");
        return 0;
    }

    return 1;
}

int findStud(const DB* db, int id) {
    for (int i = 0; i < db->cnt; i++) {
        if (db->arr[i].id == id)
            return i;
    }
    return -1;
}

int addStud(DB* db, Stud s, const char* fn) {
    if (findStud(db, s.id) != -1) {
        fprintf(stderr, "ID exists\n");
        return 0;
    }

    if (db->cnt >= db->cap) {
        int newCap = db->cap * 2;
        Stud* newArr = realloc(db->arr, newCap * sizeof(Stud));
        if (!newArr) {
            fprintf(stderr, "Memory error\n");
            return 0;
        }
        db->arr = newArr;
        db->cap = newCap;
    }

    db->arr[db->cnt++] = s;

    if (!saveDB(db, fn)) {
        db->cnt--;
        return 0;
    }

    printf("Student added.\n");
    return 1;
}

int updStud(DB* db, int id) {
    int idx = findStud(db, id);
    if (idx == -1) {
        printf("ID not found\n");
        return 0;
    }

    printf("1.Update Batch 2.Update Membership 3.Update Interest\nChoice: ");
    int ch;
    if (scanf("%d", &ch) != 1) {
        clearBuf();
        return 0;
    }
    clearBuf();

    if (ch == 1) {
        printf("New Batch: ");
        fgets(db->arr[idx].batch, MAX_BATCH, stdin);
        db->arr[idx].batch[strcspn(db->arr[idx].batch, "\n")] = 0;
    }
    else if (ch == 2) {
        printf("New Membership: ");
        fgets(db->arr[idx].memType, 10, stdin);
        db->arr[idx].memType[strcspn(db->arr[idx].memType, "\n")] = 0;
    }
    else if (ch == 3) {
        printf("New Interest: ");
        fgets(db->arr[idx].interest, 20, stdin);
        db->arr[idx].interest[strcspn(db->arr[idx].interest, "\n")] = 0;
    }
    else {
        printf("Invalid\n");
        return 0;
    }

    saveDB(db, FILENAME);
    printf("Updated.\n");
    return 1;
}

int delStud(DB* db, int id, const char* fn) {
    int idx = findStud(db, id);
    if (idx == -1) {
        printf("ID not found\n");
        return 0;
    }

    for (int i = idx; i < db->cnt - 1; i++)
        db->arr[i] = db->arr[i + 1];

    db->cnt--;
    saveDB(db, fn);

    printf("Deleted.\n");
    return 1;
}

void viewAll(const DB* db) {
    if (db->cnt == 0) {
        printf("No records.\n");
        return;
    }

    printf("\nID      Name                           Batch     MemType   RegDate     DOB         Interest\n");
    printf("-------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < db->cnt; i++) {
        printf("%-7d %-30s %-10s %-10s %-12s %-12s %-10s\n",
               db->arr[i].id,
               db->arr[i].name,
               db->arr[i].batch,
               db->arr[i].memType,
               db->arr[i].regDate,
               db->arr[i].dob,
               db->arr[i].interest);
    }
}

void viewBatch(const DB* db) {
    if (db->cnt == 0) {
        printf("No records.\n");
        return;
    }

    char batch[MAX_BATCH];
    char interest[20];

    printf("Batch: ");
    fgets(batch, MAX_BATCH, stdin);
    batch[strcspn(batch, "\n")] = 0;

    printf("Interest (All/IEEE/ACM/Both): ");
    fgets(interest, 20, stdin);
    interest[strcspn(interest, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < db->cnt; i++) {
        if (strcmp(db->arr[i].batch, batch) == 0) {
            if (strcmp(interest, "All") == 0 ||
                strcmp(interest, db->arr[i].interest) == 0) {

                printf("%d %s %s %s\n",
                       db->arr[i].id,
                       db->arr[i].name,
                       db->arr[i].memType,
                       db->arr[i].interest);
                found++;
            }
        }
    }

    if (!found) printf("No results.\n");
}

void getDate(char* buf) {
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    sprintf(buf, "%04d-%02d-%02d",
            tm->tm_year + 1900,
            tm->tm_mon + 1,
            tm->tm_mday);
}

int validDate(const char* dt) {
    if (strlen(dt) != 10) return 0;
    if (dt[4] != '-' || dt[7] != '-') return 0;

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (dt[i] < '0' || dt[i] > '9') return 0;
    }

    return 1;
}

void clearBuf() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void regStud(DB* db) {
    Stud s;

    printf("ID: ");
    if (scanf("%d", &s.id) != 1) {
        clearBuf();
        printf("Invalid.\n");
        return;
    }
    clearBuf();

    printf("Name: ");
    fgets(s.name, MAX_NAME, stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Batch: ");
    fgets(s.batch, MAX_BATCH, stdin);
    s.batch[strcspn(s.batch, "\n")] = 0;

    printf("Membership: ");
    fgets(s.memType, 10, stdin);
    s.memType[strcspn(s.memType, "\n")] = 0;

    getDate(s.regDate);

    printf("DOB (YYYY-MM-DD): ");
    fgets(s.dob, MAX_DATE, stdin);
    s.dob[strcspn(s.dob, "\n")] = 0;

    if (!validDate(s.dob)) {
        printf("Invalid date.\n");
        return;
    }

    printf("Interest: ");
    fgets(s.interest, 20, stdin);
    s.interest[strcspn(s.interest, "\n")] = 0;

    addStud(db, s, FILENAME);
}

void stressTest(DB* db) {
    printf("Stress test...\n");

    char* names[] = {"Ahmed Ali", "Sara Khan", "Ali Raza"};
    char* batches[] = {"CS", "SE", "AI", "CyberSec"};
    char* mem[] = {"IEEE", "ACM"};
    char* ints[] = {"IEEE", "ACM", "Both"};

    for (int i = 0; i < 30; i++) {
        Stud s;
        s.id = 1000 + i;
        strcpy(s.name, names[i % 3]);
        strcpy(s.batch, batches[rand() % 4]);
        strcpy(s.memType, mem[rand() % 2]);
        getDate(s.regDate);
        sprintf(s.dob, "200%d-0%d-%02d", rand() % 5, rand() % 9 + 1, (rand() % 28) + 1);
        strcpy(s.interest, ints[rand() % 3]);

        addStud(db, s, FILENAME);
    }

    saveDB(db, FILENAME);
    printf("Done.\n");
}

int main() {
    srand(time(NULL));

    DB* db = createDB();
    if (!db) return 1;

    loadDB(db, FILENAME);

    int run = 1;
    while (run) {
        printf("\n1.Register 2.Update 3.Delete 4.ViewAll 5.BatchReport 6.StressTest 7.Exit\nChoice: ");
        int ch;

        if (scanf("%d", &ch) != 1) {
            clearBuf();
            continue;
        }
        clearBuf();

        if      (ch == 1) regStud(db);
        else if (ch == 2) {
            int id;
            printf("ID: ");
            if (scanf("%d", &id) == 1) updStud(db, id);
            clearBuf();
        }
        else if (ch == 3) {
            int id;
            printf("ID: ");
            if (scanf("%d", &id) == 1) delStud(db, id, FILENAME);
            clearBuf();
        }
        else if (ch == 4) viewAll(db);
        else if (ch == 5) viewBatch(db);
        else if (ch == 6) stressTest(db);
        else if (ch == 7) {
            saveDB(db, FILENAME);
            run = 0;
        }
    }

    freeDB(db);
    return 0;
}
