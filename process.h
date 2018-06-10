#ifndef _PROCESS_H_
#define _PROCESS_H_
#include "User.h"
#include "Student.h"
#include "Teacher.h"
#include "Admin.h"
using namespace std;

bool startProgram(User& random_user, UserList user_list);

bool studentProcess(Student&st, UserList& user_list, StudentCourseList&db_st_course_list, CourseList db_course_list, arrayList<string> agvList);
bool studentMenu(Student& st, StudentCourseList&db_st_course_list, CourseList&db_course_list, UserList&Suser_list);
bool teacherMenu(Teacher& tc, StudentCourseList& db_st_course_list, CourseList& db_course_list, UserList user_list);
bool teacherProcess(Teacher& tc, UserList& user_list, StudentCourseList&db_st_course_list, CourseList& db_course_list, arrayList<string> agvList);
bool adminMenu(Admin& ad, StudentList& db_st_list, TeacherList& db_tc_list, UserList& user_list, CourseList &db_course_list, StudentCourseList &db_st_course_list);
bool adminProcess(Admin& ad, UserList& user_list, StudentList& db_st_list, TeacherList& db_tc_list, CourseList &db_course_list, StudentCourseList &db_st_course_list, arrayList<string> agvList);
#endif // !_PROCESS_H_