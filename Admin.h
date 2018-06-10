#ifndef _ADMIN_
#define _ADMIN_

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cctype>
#include "Helper.h"
#include "User.h"
#include "Student.h"
#include "Teacher.h"

using namespace std;

inline void to_upper(string &s) {
	for (size_t i = 0; i < s.length(); i++) {
		s[i] = toupper(s[i]);
	}
}

class Admin : public User {
public:
	Admin() {};
	~Admin() {};
	bool addUser(User user, UserList &db_user_list); 
	bool removeUser(string username, UserList &db_user_list, StudentList &db_st_list, TeacherList &db_tc_list, CourseList &db_course_list, StudentCourseList &db_st_course_list);
	bool addStudent(StudentList &db_st_list, UserList &db_user_list);
	bool addTeacher(TeacherList &db_tc_list, UserList &db_user_list);
	
};

#endif // !_ADMIN_