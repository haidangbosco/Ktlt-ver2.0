#include <iostream>
#include "User.h"
#include "Student.h"
#include "Teacher.h"
#include "process.h"
#include "DBHelper.h"
UserList  db_user_list;
CourseList db_course_list;
StudentList db_st_list;
TeacherList db_tc_list;
StudentCourseList db_st_course_list;

using namespace std;

void main() {
	loadUsers(db_user_list);
	loadCourse(db_course_list);
	loadStudentCourse(db_st_course_list);
	loadStudentInfo(db_st_list);
	loadTeacherInfo(db_tc_list);
	User random_user;
	while (startProgram(random_user, db_user_list)) {
		system("cls");
		if (random_user.role == "student") {
			Student st;
			st = random_user;
			db_st_list.getStudentInfo(st);
			if (studentMenu(st, db_st_course_list, db_course_list, db_user_list) == false) {
				break;
			}
		}
		else if (random_user.role == "teacher") {
			Teacher tc;
			tc = random_user;
			db_tc_list.getTeacherInfo(tc);

			if (teacherMenu(tc, db_st_course_list, db_course_list, db_user_list) == false){
				break;
			}
		}
		else if (random_user.role == "admin") {
			Admin ad;
			ad.username = random_user.username;
			ad.password = random_user.password;
			ad.role = random_user.role;
			if (adminMenu(ad, db_st_list, db_tc_list, db_user_list, db_course_list, db_st_course_list) == false) {
				break;
			}
		}
	}
	writeToCouresFile(db_course_list);
	writeToStudentCourseFile(db_st_course_list);
	writeToStudentFile(db_st_list);
	writeToTeacherFile(db_tc_list);
	writeToUserFile(db_user_list);
	return;
}