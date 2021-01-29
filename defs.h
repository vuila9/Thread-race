#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <curses.h>

#define START_POS    35
#define END_POS       2
#define PATH_1       10
#define PATH_2       14
#define MAX_HEALTH   50
#define MAX_RUNNERS  20
#define MAX_DORCS    50
#define MAX_STR      16
#define MAX_BUF      80

#define HEALTH_ROW    0
#define HEALTH_COL   30
#define STATUS_ROW    4
#define STATUS_COL   30

#define C_TRUE        1
#define C_FALSE       0

#define DORC_FREQ     3

typedef struct {
  pthread_t thr;
  char avatar[MAX_STR];
  int  currPos; // row
  int  path; // column
} EntityType;

typedef struct {
  EntityType ent;
  char name[MAX_STR];
  int  health;
  int  dead;
} RunnerType;

typedef struct {
  int numRunners;
  RunnerType *runners[MAX_RUNNERS];
  int numDorcs;
  EntityType *dorcs[MAX_DORCS];
  char winner[MAX_STR];
  int  statusRow;
  sem_t mutex;
} RaceInfoType;

void initNcurses();

void cleanupNcurses(int);

void scrPrt(char*, int, int);

int  randm(int);

void *goRunner(void*);

void *goDorc(void*);

RaceInfoType *race;

void initRaceInfoType();

void initRunnerType(RunnerType*, char*, char*, int);

void createRunner(RunnerType*, char*, char*, int);

void addRunner(RunnerType*);

RunnerType* runnerAt(int);

EntityType* dorcAt(int);

void initDorcs(EntityType*);

void addDorc(EntityType*);

void initGUI();

int updateDead();

int updateFinisher();

void updateRunnerDisplay(RunnerType*, int);

void updateDorcDisplay(EntityType*, int, int);

void cleanUp();





