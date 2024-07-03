#ifndef DATABASE_H
#define DATABASE_H

#include "db_levels.h"
#include "db_modules.h"
#include "db_status_events.h"

MODULE select_m(FILE *db, int id);
int delete_m(int id, char *path);
int insert_m(FILE *db, MODULE *entity);
int update_m(FILE *db, int id, MODULE *entity);

LEVEL select_l(FILE *db, int id);
int delete_l(int id, char *path);
int insert_l(FILE *db, LEVEL *entity);
int update_l(FILE *db, int id, LEVEL *entity);

STATUS_EVENT select_s(FILE *db, int id);
int delete_s(int id, char *path);
int insert_s(FILE *db, STATUS_EVENT *entity);
int update_s(FILE *db, int id, STATUS_EVENT *entity);

#endif
