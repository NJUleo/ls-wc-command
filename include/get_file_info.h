#include <stdio.h>

#define __USE_GNU  // define this to use basename() function in <string.h>
#include <string.h>

// to read file stat
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// to read file owner and group
#include <grp.h>
#include <pwd.h>

// // to transfer time stamps to string
// #include <time.h>

#ifndef NDEBUG
// assert only in debug
#include <assert.h>
#endif

/**
 * struct containing the information that could be directely printed.
 * owner and group name must be less than 64 chars.
 */
typedef struct file_info {
    char permissions_str[11];
    long bytes;
    long link_num;
    long inode_num;
    char* owner;
    char* group;
    char* name;
    __time_t m_time;  // modified time
} file_info;

void for_test();

/**
 * return -1 if failed.
 */
int get_file_info(char* file_path, file_info* file_info);