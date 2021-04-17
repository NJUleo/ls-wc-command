#include "get_file_info.h"

/**
 * static functions that are only used by the current module.
 */
static char *lsperms(int mode);
static int filetypeletter(int mode);

void for_test() {
    printf("haha\n");
    return;
}

int get_file_info(char *file_path, file_info *file_info) {
    struct stat file_stat;
    if (stat(file_path, &file_stat) < 0) {
        return -1;
    }

    printf("---------------------------\n");
    printf("File Size: \t\t%lu bytes\n", file_stat.st_size);
    printf("Number of Links: \t%lu\n", file_stat.st_nlink);
    printf("File inode: \t\t%lu\n", file_stat.st_ino);

    printf("File Permissions: \t");
    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");

    // get owner and gourp name
    struct passwd *pw = getpwuid(file_stat.st_uid);
    struct group *gr = getgrgid(file_stat.st_gid);

#ifndef NDEBUG
    assert(pw != NULL);
    assert(gr != NULL);
#endif
    file_info->owner = pw->pw_name;
    file_info->group = gr->gr_name;

    // get file permissions string
    strcpy(file_info->permissions_str, lsperms(file_stat.st_mode));
    printf("%s\n", file_info->permissions_str);

    // inode, linke number, file size, file name
    file_info->inode_num = file_stat.st_ino;
    file_info->link_num = file_stat.st_nlink;
    file_info->bytes = file_stat.st_size;
    file_info->name = basename(file_path);
    file_info->m_time = file_stat.st_mtime;

    return 1;
}

/* Convert a mode field into "ls -l" type perms field. */
static char *lsperms(int mode) {
    static const char *rwx[] = {"---", "--x", "-w-", "-wx",
                                "r--", "r-x", "rw-", "rwx"};
    static char bits[11];

    bits[0] = filetypeletter(mode);
    strcpy(&bits[1], rwx[(mode >> 6) & 7]);
    strcpy(&bits[4], rwx[(mode >> 3) & 7]);
    strcpy(&bits[7], rwx[(mode & 7)]);
    if (mode & S_ISUID) bits[3] = (mode & S_IXUSR) ? 's' : 'S';
    if (mode & S_ISGID) bits[6] = (mode & S_IXGRP) ? 's' : 'l';
    if (mode & S_ISVTX) bits[9] = (mode & S_IXOTH) ? 't' : 'T';
    bits[10] = '\0';
    return (bits);
}

/**
 * use macros in <sys/stat.h> to check file type.
 */
static int filetypeletter(int mode) {
    char c;
    if (S_ISREG(mode))
        c = '-';
    else if (S_ISDIR(mode))
        c = 'd';
    else if (S_ISBLK(mode))
        c = 'b';
    else if (S_ISCHR(mode))
        c = 'c';
    else if (S_ISFIFO(mode))
        c = 'p';
    else if (S_ISLNK(mode))
        c = 'l';
    else if (S_ISSOCK(mode))
        c = 's';
    else {
        /* Unknown type -- possibly a regular file? */
        c = '?';
    }
    return (c);
}