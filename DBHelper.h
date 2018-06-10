#ifndef _DBHELPER_
#define _DBHELPER_

#include<fstream>
#include<iostream>
#include<string.h>
#include<sstream>
#include "User.h"
#include "Student.h"
#include "Teacher.h"

using namespace std;

bool loadUsers(UserList &user_list);
bool loadCourse(CourseList &courseList);
bool loadStudentCourse(StudentCourseList &st_course_list);
bool loadStudentInfo(StudentList &st_list);
bool loadTeacherInfo(TeacherList &tc_list);
void writeToCouresFile(CourseList &courseList);
void writeToStudentFile(StudentList &st_list);
void writeToTeacherFile(TeacherList &tc_list); //h
void writeToStudentCourseFile(StudentCourseList &st_course_list);
void writeToUserFile(UserList &user_list);
#endif // !_DBHELPER_

