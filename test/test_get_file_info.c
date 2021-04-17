#include <time.h>

#include "get_file_info.h"
int main() {
    file_info info;
    get_file_info("/home/leo/Desktop", &info);
    file_info info2;
    get_file_info("/home/leo/Desktop", &info2);

    // print mtime.
    char buff[20];
    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&info.m_time));
    printf("%s\n", buff);

    return 0;
}