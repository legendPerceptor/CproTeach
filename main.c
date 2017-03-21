
#include "teach.h"
int main() {
    courseDB course;
    course = ReadDataBase();
    printf("Successfully loading the question naire!\n");
    ProcessCourse(course);
    return 0;
}