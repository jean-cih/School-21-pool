#include "modules_db.h"

#include "database.h"
#include "db_levels.h"
#include "db_modules.h"
#include "db_status_events.h"

int main(void) {
    int operation, table_n, amount;
    char x;
    while (1) {
        menu();
        if (scanf("%d%c", &operation, &x) == 2 && x == '\n' && operation > 0 && operation < 11) {
            if(operation == 10){
                printf("You've left\n");
                break;
            }
            instruction(operation);
            if (scanf("%d%c", &table_n, &x) == 2 && x == '\n' && table_n > 0 && table_n < 4) {
                char *name_table;
                if (table_n == 1)
                    name_table = "../materials/master_modules.db";
                else if (table_n == 2)
                    name_table = "../materials/master_levels.db";
                else
                    name_table = "../materials/master_status_events.db";

                FILE *file;
                if (operation == 1) {
                    printf("Insert the number of records: ");
                    if (scanf("%d%c", &amount, &x) == 2 && x == '\n') {
                        file = fopen(name_table, "r+");
                        if (table_n == 1) {
                            int size1 = get_records_count_in_file_m(file);
                            if (size1 > amount) size1 = amount;
                            drawing(67);
                            printf("| %2s |%20s\t| %10s | %4s | %11s |\n", "Id", "Name of module", "Memory lvl", "Cell", "Delete flag");
                            drawing(67);
                            for (int i = 0; i < size1; i++) {
                                MODULE read1 = select_m(file, i);
                                printf("|%3d |%20s\t|%7d     |%4d  |%7d\t  |\n", read1.id, read1.name, read1.mem_n, read1.item_n,
                                       read1.flag_del);
                            }
                        } else if (table_n == 2) {
                            int size2 = get_records_count_in_file_l(file);
                            if (size2 > amount) size2 = amount;
                            drawing(59);
                            printf("| %10s | %24s | %15s |\n", "memory lvl", "Quantity of cells on lvl", "Flag of defence");
                            drawing(59);
                            for (int i = 0; i < size2; i++) {
                                LEVEL read2 = select_l(file, i);
                                printf("|%6d      | %14d\t        |  %8d       |\n", read2.level_n, read2.item_q, read2.flag_def);
                            }
                        } else {
                            int size3 = get_records_count_in_file_s(file);
                            if (size3 > amount) size3 = amount;
                            drawing(103);
                            printf("| %10s | %11s | %20s | %23s | %23s |\n", "Event's id", "Module's id", "New status of module", "Data of changing status", "Time of changing status");
                            drawing(103);
                            for (int i = 0; i < size3; i++) {
                                STATUS_EVENT read3 = select_s(file, i);
                                printf("|%6d      |%7d      |%12d\t  |%18s\t    |%16s\t      |\n", read3.id_hap, read3.id_mod, read3.new_status,
                                       read3.date_stat, read3.time_stat);
                            }
                        }

                        fclose(file);
                    } else
                        printf("Incorrect input data:\n");

                } else if (operation == 2) {
                    printf("Input data to write down the base data:\n");
                    file = fopen(name_table, "r+");
                    if (table_n == 1) {
                        MODULE write1;
                        insert_m(file, &write1);
                    } else if (table_n == 2) {
                        LEVEL write2;
                        insert_l(file, &write2);
                    } else {
                        STATUS_EVENT write3;
                        insert_s(file, &write3);
                    }

                    fclose(file);

                } else if (operation == 3) {
                    printf("Input the string id to change this struct\n");
                    file = fopen(name_table, "r+");
                    int id;
                    if (scanf("%d%c", &id, &x) == 2 && x == '\n') {
                        if (table_n == 1) {
                            MODULE write1;
                            if(id - 1 < get_records_count_in_file_m(file))
                                update_m(file, id - 1, &write1);
                            else
                                printf("This table doesn't have this id\n");
                        } else if (table_n == 2) {
                            LEVEL write2;
                            if(id - 1 < get_records_count_in_file_l(file))
                                update_l(file, id - 1, &write2);
                            else
                                printf("This table doesn't have this id\n");
                        } else {
                            STATUS_EVENT write3;
                            if(id - 1 < get_records_count_in_file_s(file))
                                update_s(file, id - 1, &write3);
                            else
                                printf("This table doesn't have this id\n");
                        }
                    } else
                        printf("Incorrect input data:\n");

                } else if (operation == 4) {
                    printf("Input the number of string: \n");
                    int id;
                    if (scanf("%d%c", &id, &x) == 2 && x == '\n') {
                        FILE *file = fopen(name_table, "r+");
                        if (table_n == 1)
                            delete_m(file, id, name_table);
                        else if (table_n == 2)
                            delete_l(file, id, name_table);
                        else
                            delete_s(file, id, name_table);

                        printf("Modules %d marked as deleted", id);

                        fclose(file);
                    } else
                        printf("Incorrect input data:\n");

                } else if (operation == 5) {
                    if (table_n == 1) {
                        file = fopen(name_table, "r+");
                        for (int i = 0; i < get_records_count_in_file_m(file); i++) {
                            MODULE status_act = read_record_from_file_m(file, i);
                            if (status_act.flag_del == 0)
                                printf("%d %s %d %d %d\n", status_act.id, status_act.name, status_act.mem_n,
                                       status_act.item_n, status_act.flag_del);
                        }

                        fclose(file);
                    } else
                        printf("Active statuses is given only from modules table\n");

                } else if (operation == 6) {
                    if (table_n == 2) {
                        printf("This table doesn't have any ids\n");
                    } else {
                        printf("Please input the id of the deleting modules: \n");
                        int id;
                        if (scanf("%d%c", &id, &x) == 2 && x == '\n') {
                            file = fopen(name_table, "r+");
                            if (table_n == 1)
                                delete_id_m(file, id, name_table);
                            else
                                delete_id_s(file, id, name_table);

                            printf("Modules %d marked as deleted", id);
                        } else
                            printf("Incorrect input data:\n");

                        fclose(file);
                    }
                } else if (operation == 7) {
                    if (table_n != 1 && table_n != 3) {
                        printf("Please input the id to set protected mode for module: \n");
                        file = fopen(name_table, "r+");
                        int id;
                        if (scanf("%d%c", &id, &x) == 2 && x == '\n') {
                            LEVEL change = read_record_from_file_l(file, id);
                            change.flag_def = 1;
                            write_record_in_file_l(file, &change, id);
                        } else
                            printf("Incorrect input data:\n");

                        fclose(file);
                    } else
                        printf("This table doesn't have the protected mode\n");

                } else if (operation == 8) {
                    if (table_n != 2 && table_n != 3) {
                        printf("Please input the id to set protected mode for module: \n");
                        file = fopen(name_table, "r+");
                        int id;
                        if (scanf("%d%c", &id, &x) == 2 && x == '\n') {
                            MODULE change = read_record_from_file_m(file, id);
                            printf("Please input new specified memory level and cell\n");
                            char a;
                            if (scanf("%d%c%d%c", &change.mem_n, &a, &change.item_n, &x) == 4 && x == '\n')
                                write_record_in_file_m(file, &change, id);
                            else
                                printf("Incorrect input data:\n");
                        } else
                            printf("Incorrect input data:\n");

                        fclose(file);
                    } else
                        printf("This table doesn't have the memory level and cell\n");

                } else if (operation == 9) {
                    if (table_n == 2) {
                        printf("Input the specified memory level: ");
                        file = fopen(name_table, "r+");
                        int mem;
                        if (scanf("%d%c", &mem, &x) == 2 && x == '\n') {
                            LEVEL memory = read_record_from_file_l(file, mem);
                            printf("Please set protection flag: ");
                            if (scanf("%d%c", &memory.flag_def, &x) == 2 && x == '\n' &&
                                (memory.flag_def == 1 || memory.flag_def == 0))
                                write_record_in_file_l(file, &memory, mem);
                            else
                                printf("Incorrect number of table:\n");
                        } else
                            printf("Incorrect number of table:\n");

                        fclose(file);
                    } else
                        printf("This table doesn't have the protection flag of the specified memory level\n");

                }
                
            } else
                printf("Incorrect number of table:\n");
        } else
            printf("Incorrect number of operation:\n");

        getchar();
    }
}