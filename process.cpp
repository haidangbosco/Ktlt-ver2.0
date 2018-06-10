#include "process.h"
#include "Student.h"
#include "Teacher.h"
#include "DBHelper.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

CourseList* ctemp = new CourseList();
CourseList* ttemp = new CourseList();
bool startProgram(User& random_user, UserList user_list) {

	while (true) {

		cout << "\t\t\t\t" << "|++++++++++++++++++++++++++++++++++++|\n\n";
		cout << "\t\t\t\t" << "|   Welcome to student manager site  |\n\n";
		cout << "\t\t\t\t" << "|++++++++++++++++++++++++++++++++++++|\n\n\n";

		cout << "Username (Type q to exit): ";
		cin >> random_user.username;
		cout << "Password (Type q to exit): ";
		cin >> random_user.password;
		cin.ignore(INT_MAX, '\n');
		if (random_user.username == "q" && random_user.password == "q") {
			return false;
		}
		if (user_list.authentication(random_user)) {
			return true;
		}
		else {
			cout << "===================" << endl;
			cout << "Login Failed" << endl;
			bool rep = true;
			do {
				char option;
				cout << "Continue? (Y/N) ";
				cin >> option;
				cin.ignore(INT_MAX, '\n');
				switch (option) {
				case 'Y':rep = false; break;
				case 'N':return false;
				default: {
							 cout << "Error: option must be Y or N " << endl;
							 break;
				}
				}
				system("cls");
			} while (rep);
		}
	}
}
bool studentMenu(Student& st, StudentCourseList&db_st_course_list, CourseList&db_course_list, UserList&user_list) {
	while (st.isLogin() == true) {
		cout << "\t\t\t\t" << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << "\t\t\t\t" << "|\t\tSTUDENT SITE\t\t | \n";
		cout << "\t\t\t\t" << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n";

		cout << setfill('-') << setw(50) << "-" << "Student: " << st.st_number << setw(50) << "-" << endl;
		cout << setw(40) << setfill(' ') << left << "1. Change password" << "[cp]" << endl;
		cout << setw(40) << setfill(' ') << left << "2. View my courses" << "[vc]" << endl;
		cout << setw(40) << setfill(' ') << left << "3. Search courses" << "[sc] [-n,-f]" << endl;
		cout << setw(40) << setfill(' ') << left << "4. Join course" << "[jc]" << endl;
		cout << setw(40) << setfill(' ') << left << "5. Cancel course" << "[xc]" << endl;
		cout << setw(40) << setfill(' ') << left << "6. Log out" << "[lo]" << endl;
		cout << setw(40) << setfill(' ') << left << "7. Help" << "[h]" << endl;
		cout << "\nYour command (press [e] to quit program): ";
		string command;
		stringstream ss;
		string agv;
		arrayList<string> agvList;
		getline(cin, command);
		ss.str(command);
		do{
			ss >> agv;
			if (ss.fail() || agv == "") {
				system("cls");
				break;
			}
			else agvList.addToList(agv);
		} while (true);
		if (agvList.list[0] == "e" && agvList.size == 1) return false;
		if (studentProcess(st, user_list, db_st_course_list, db_course_list, agvList) == true) {
			system("cls");
		}
		else {
			cout << "Error: command not found" << endl;
		}
	}
	return true;
}
bool teacherMenu(Teacher& tc, StudentCourseList& db_st_course_list, CourseList& db_course_list, UserList user_list){
	while (tc.isLogin() == true){
		cout << "\t\t\t\t" << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << "\t\t\t\t" << "|\t\tTEACHER SITE\t\t | \n";
		cout << "\t\t\t\t" << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n";
		cout << "Lecturer: " << tc.tc_name << "[" << tc.tc_identify << "]\n";
		cout << setfill('=') << setw(100) << "=" << endl;
		cout << setw(40) << setfill(' ') << left << "1. Change password" << "[cp (new password)]" << endl;
		cout << setw(40) << setfill(' ') << left << "2. View my opened courses" << "[vc]" << endl;
		cout << setw(40) << setfill(' ') << left << "3. Open a course" << "[oc]" << endl;
		cout << setw(40) << setfill(' ') << left << "4. Grading student's course" << "[gc]" << endl;
		cout << setw(40) << setfill(' ') << left << "5. Log out" << "[lo]" << endl;
		cout << setw(40) << setfill(' ') << left << "6. Help" << "[h]" << endl;
		cout << "\nYour command (press [e] to quit program): ";
		string command;
		stringstream ss;
		string agv;
		arrayList<string> agvList;
		getline(cin, command);
		ss.str(command);
		do{
			ss >> agv;
			if (ss.fail() || agv == "") {
				system("cls");
				break;
			}
			else agvList.addToList(agv);
		} while (true);
		if (agvList.list[0] == "e" && agvList.size == 1) return false;
		if (teacherProcess(tc, user_list, db_st_course_list, db_course_list, agvList) == true) {
			system("cls");
		}
		else {
			cout << "\nError: command not found\n" << endl;
		}
	}
	return true;
}
bool studentProcess(Student&st, UserList& user_list, StudentCourseList& db_st_course_list, CourseList db_course_list, arrayList<string> agvList) {
	if (agvList.list[0] == "cp") {
		return cp(st, agvList, user_list);
	}
	else if (agvList.list[0] == "vc") {
		system("cls");
		studentCourse enrolledCourse;
		st.getStudentCourse(db_st_course_list, enrolledCourse, &db_course_list);
		st.showStudentCourse(&db_course_list, enrolledCourse);
		cout << "PRESS ENTER TO GO BACK\n";
		cin.get();
		return true;
	}
	else if (agvList.list[0] == "sc") {
		if (agvList.list[1] == "-n") {
			if (agvList.size > 2) {
				agvList.removeFromList(0);
				agvList.removeFromList(0);
				CourseList* cList = db_course_list.findAllCourseByName(agvList);
				if (cList->size == 0) {
					cout << "Error: Failed to find data" << endl;
				}
				else {
					system("cls");
					ctemp = cList;
					cList->printCourse();
				}
			}
			else if (agvList.size == 2) {
				cout << "Course to search: ";
				string course_name;
				getline(cin, course_name);
				CourseList* cList = db_course_list.findCourseByName(course_name);
				if (cList->size == 0) {
					cout << "Error: Failed to find data" << endl;
				}
				else {
					system("cls");
					ctemp = cList;
					cList->printCourse();
				}
			}
			cout << "PRESS ENTER TO GO BACK\n";
			cin.get();
			return true;
		}
		else if (agvList.list[1] == "-f") {
			if (agvList.size > 2) {
				agvList.removeFromList(0);
				agvList.removeFromList(0);
				CourseList* cList = db_course_list.findAllCourseByFalcuty(agvList);
				ttemp = cList;
				cList->printCourse();
				
			}
			else if (agvList.size == 2) {
				cout << "Falcuty to search: ";
				string fal_name;
				getline(cin, fal_name);
				CourseList* cList = db_course_list.findCourseByFacuty(fal_name);
				ttemp = cList;
				cList->printCourse();
				

			}
			cout << "PRESS ENTER TO GO BACK\n";
			cin.get();
			return true;
		}
	}
	else if (agvList.list[0] == "jc") {
		studentCourse enrolledCourse;
		if (st.getStudentCourse(db_st_course_list, enrolledCourse, &db_course_list) == false) {
			enrolledCourse.st_num = st.st_number;
		}
		if (agvList.size > 1) {
			agvList.removeFromList(0);
			if (st.joinCourse(enrolledCourse, agvList, db_st_course_list, db_course_list) == false) {
				if (agvList.size != 0) {
					cout << "Error: Failed to join in ";
					for (size_t i = 0; i < agvList.size; i++) {
						cout << "'" << agvList.list[i] << "'";
					}
				}
			}
			else {
				if (agvList.isEmpty() == true) {
					cout << "Your have successfully joined the courses." << endl;
				}
				else {
					cout << "Error: Failed to join in ";
					for (size_t i = 0; i < agvList.size; i++) {
						cout << "'" << agvList.list[i] << "'";
					}
					cout << endl;
				}
			}
		}
		else if (agvList.size == 1) {
			
			if (ctemp->size!=0){
				cout << "Search history: \n";
				ctemp->printCourse();
			}
			else if (ttemp->size!=0){
				cout << "Search history: \n";
				ttemp->printCourse();
			}
			else{
				db_course_list.printCourse();
			}
			string courseId;
			arrayList<string> join_course;
			cout << "Course to join: ";
			cin >> courseId;
			cin.ignore(INT_MAX, '\n');
			join_course.addToList(courseId);
			if (st.joinCourse(enrolledCourse, join_course, db_st_course_list, db_course_list) == false) {
				cout << "Error: Failed to join in ";
				for (size_t i = 0; i < join_course.size; i++) {
					cout << "'" << join_course.list[i] << "'";
				}
				cout << endl;
			}
			else {
				if (join_course.isEmpty() == true) {
					cout << "Your have successfully joined the courses." << endl;
				}
				else {
					cout << "Error: Failed to join in ";
					for (size_t i = 0; i < join_course.size; i++) {
						cout << "'" << join_course.list[i] << "'";
					}
					cout << endl;
				}
			}
		}
		cout << "PRESS ENTER TO GO BACK\n";
		cin.get();
		return true;
	}
	else if (agvList.list[0] == "xc") {
		studentCourse enrolledCourse;
		studentCourse tmp_enrolledCourse;
		st.getStudentCourse(db_st_course_list, enrolledCourse, &db_course_list);
		tmp_enrolledCourse = enrolledCourse;
		st.showStudentCourse(&db_course_list, enrolledCourse);
		cout << setfill('_') << setw(120) << "_" << endl;
		cout << setfill(' ');//reset
		
		if (agvList.size > 1) {
			agvList.removeFromList(0);
			for (size_t i = 0; i < agvList.size; i++) {
				if (tmp_enrolledCourse.hasEnrolled(agvList.list[i]) == false) {
					cout << "Error: You have not joined " << agvList.list[i] << endl;
					cout << endl;
				}
				else {
					int index = 0;
					tmp_enrolledCourse.st_course.isExist(agvList.list[i], index);

					if (tmp_enrolledCourse.st_point.list[index] != -1) {
						cout << "You are graded in \"" << agvList.list[i] << "\" so you can not cancel it." << endl;
					}
					else {
						cout << "You have canceled join " << agvList.list[i] << endl;
						tmp_enrolledCourse.st_course.removeFromList(index);
						tmp_enrolledCourse.st_point.removeFromList(index);
					}
				}
			}
			st.cancelCourse(enrolledCourse, agvList, db_st_course_list, db_course_list);
		}
		else if (agvList.size == 1) {
			string courseId;
			arrayList<string> cancel_course;
			cout << "Course to cancel: ";
			cin >> courseId;
			cin.ignore(INT_MAX, '\n');
			cancel_course.addToList(courseId);
			for (size_t i = 0; i < cancel_course.size; i++) {
				if (enrolledCourse.hasEnrolled(cancel_course.list[i]) == false) {
					cout << "Error: You have not joined " << cancel_course.list[i] << endl;
					cout << endl;
				}
				else {
					int index = 0;
					enrolledCourse.st_course.isExist(cancel_course.list[i], index);
					if (enrolledCourse.st_point.list[index] != -1) {
						cout << "You are graded in \"" << cancel_course.list[i] << "\" so you can not cancel it." << endl;
					}
					else cout << "You have canceled join " << cancel_course.list[i] << endl;
				}
			}
			st.cancelCourse(enrolledCourse, cancel_course, db_st_course_list, db_course_list);
		}
		cout << "PRESS ENTER TO GO BACK\n";
		cin.get();
		return true;
	}
	else if (agvList.list[0] == "lo") {
		st.logout();
		system("cls");
		return true;
	}
	else if (agvList.list[0] == "h") {
		if (agvList.size == 1) {
			system("cls");
			cout << setw(40) << left << "Description " << setw(10) << left << "Command" << setw(10) << left << "Argument list" << endl;
			cout << setw(100) << setfill('-') << "-" << setfill(' ') << endl;
			cout << setw(40) << left << "Change password" << setw(10) << left << "cp" << setw(10) << left << "<new password> (optional)" << endl;
			cout << setw(40) << left << "View all course" << setw(10) << left << "vc" << setw(10) << left << "none" << endl;
			cout << setw(40) << left << "Search coures by keyword" << setw(10) << left << "sc -n" << setw(10) << left << "<list of course's name> (optional)" << endl;
			cout << setw(40) << left << "Search coures by falcuty" << setw(10) << left << "sc -f" << setw(10) << left << "<list of falcuty's name> (optional)" << endl;
			cout << setw(40) << left << "Cancel course" << setw(10) << left << "xc" << setw(10) << left << "<list of course id> (optional)" << endl;
			cout << setw(40) << left << "Join course" << setw(10) << left << "jc" << setw(10) << left << "<list of course id> (optional)" << endl;
			cout << setw(100) << setfill('=') << "=" << setfill(' ') << endl;
			cout << "PRESS ENTER TO GO BACK\n";
			cin.get();
			return true;
		}
	}
	return false;
}
bool teacherProcess(Teacher& tc, UserList& user_list, StudentCourseList& db_st_course_list, CourseList& db_course_list, arrayList<string> agvList) {

#pragma region ChangePass
	if (agvList.list[0] == "cp"){
		return cp(tc, agvList, user_list);
	}
#pragma endregion

	else if (agvList.list[0] == "vc"){
		
			CourseList* tc_open_course = new CourseList();
			tc_open_course = tc.teacherCourse(db_course_list); //lay danh sach nhung course ma teacher da mo
			StudentCourseList* data = new StudentCourseList();
			CourseList* tc_sum = tc.tcSumCourse(db_course_list, db_st_course_list);
			CourseList* tc_nsum = tc.tcNotSumCourse(db_course_list, db_st_course_list);
			if (tc_open_course->size == 0){
				cout << "YOU HAVE NOT OPEN ANY COURSE YET.\n";
				cin.get();
				return true;
			}
			if (tc_sum->size != 0){
				cout << "Your sumarized course: \n";
				tc.showTeacherCouser(*tc_sum, db_st_course_list);
			}
			else{
				cout << "Your sumarized course: \n";
				cout << "You have not sumarized any course yet.\n";
			}

			if (tc_nsum->size != 0){
				cout << "\nYour unsumarized course: \n";
				tc.showTeacherCouser(*tc_nsum, db_st_course_list);
			}
			else{
				cout << "\nYour unsumarized course: \n"; 
				cout << "All course has ben sumarized.\n";
			}
			//tc.showTeacherCouser(*tc_open_course,db_st_course_list);
			if (tc_open_course->size == 0){
				cout << "Try opening a course in main menu.\n";
				cout << "PRESS ENTER TO GO BACK";
				cin.get();
				return true;
			}
			cout << "PRESS ENTER TO GO BACK";
			cin.get();
			return true;
	}

#pragma region OpenCourse
	else if (agvList.list[0] == "oc"){
		return tc.openNewCourse(tc, db_st_course_list, db_course_list);
	}

#pragma endregion

#pragma region Grading

	else if (agvList.list[0] == "gc"){
		CourseList* tc_open_course = new CourseList();
		tc_open_course = tc.teacherCourse(db_course_list); //lay danh sach nhung course ma teacher da mo
		StudentCourseList* data = new StudentCourseList();
		
		tc.showTeacherCouser(*tc_open_course,db_st_course_list);
		if (tc_open_course->size == 0){
			cout << "Try opening a course in main menu.\n";
			cout << "PRESS ENTER TO GO BACK";
			cin.get();
			return true;
		}
		float option;
		do{
			cout << "\nChose course to grade or press 0  to exit: ";
			cin >> option;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			if (option<0 || option>tc_open_course->size || cin.bad() || option != (int)option){
				cout << "Wrong input, try again!\n";
				continue;
			}
		} while (option<0 || option>tc_open_course->size || cin.bad() || option != (int)option);

		if (option == 0){
			return true;
		}
		else if (option != 0){
			int flag = 1;
			for (size_t i = 0; i < tc_open_course->size; i++){
				if (option == i + 1){
					data = db_st_course_list.findStudentJoinCourse(tc_open_course->list[i].course_id); //lay danh sach sinh vien + diem ma sinh vien tham gia course;
					if (data->size == 0){
						cout << "There are no students applied to this course, try again later!\n";
						flag = 0;
						cout << "PRESS ENTER TO GO BACK\n";
						cin.get();
						
						return true;
						
					}
					if (flag == 1){
						tc.gradingCourse(*data);
						db_st_course_list.updatePoint(*data);
						cout << "PRESS ENTER TO GO BACK\n";
						cin.get();
						return true;
					}
				}
			}
			
		}

	} //end else if

#pragma endregion

#pragma region logout
	else if (agvList.list[0] == "lo") {
		tc.logout();
		system("cls");
		return true;
	}
#pragma endregion

#pragma region help
	else if (agvList.list[0] == "h") {
		if (agvList.size == 1) {
			system("cls");
			cout << setw(40) << left << "Description " << setw(10) << left << "Command" << setw(10) << left << "Argument list" << endl;
			cout << setw(100) << setfill('-') << "-" << setfill(' ') << endl;
			cout << setw(40) << left << "Change password" << setw(10) << left << "cp" << setw(10) << left << "<new password> (optional)" << endl;
			cout << setw(40) << left << "View your opened course" << setw(10) << left << "vc" << setw(10) << left << "none" << endl;
			cout << setw(40) << left << "Opent a course" << setw(10) << left << "oc" << setw(10) << left << "none" << endl;
			cout << setw(40) << left << "Grading a course" << setw(10) << left << "gc" << setw(10) <<endl;
			cout << setw(100) << setfill('=') << "=" << setfill(' ') << endl;
			cout << "Press any key to exit." << endl;
			getchar();
			system("cls");
			return true;
		}
	}
#pragma endregion

}

#pragma region Tien

bool adminMenu(Admin& ad, StudentList& db_st_list, TeacherList& db_tc_list, UserList& user_list, CourseList &db_course_list, StudentCourseList &db_st_course_list)
{
	while (ad.isLogin() == true) {
		cout << "\t\t\t\t" << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << "\t\t\t\t" << "|\t\tADMIN  SITE\t\t | \n";
		cout << "\t\t\t\t" << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n";
		cout << setw(40) << setfill('-') << "-" << "ADMIN" << setw(40) << setfill('-') << "-" << endl;
		cout << setw(40) << setfill(' ') << left << "Change password" << "[cp]" << endl;
		cout << setw(40) << setfill(' ') << left << "Show teacher" << "[t]" << endl;
		cout << setw(40) << setfill(' ') << left << "Show student" << "[s]" << endl;
		cout << setw(40) << setfill(' ') << left << "Add Teacher" << "[at]" << endl;
		cout << setw(40) << setfill(' ') << left << "Add Student" << "[as]" << endl;
		cout << setw(40) << setfill(' ') << left << "Remove User" << "[ru]" << endl;
		cout << setw(40) << setfill(' ') << left << "Search Teacher by name" << "[st]" << endl;
		cout << setw(40) << setfill(' ') << left << "Search Student by name" << "[ss]" << endl;
		cout << setw(40) << setfill(' ') << left << "Log out" << "[lo]" << endl;
		cout << setw(40) << setfill(' ') << left << "Help" << "[h]" << endl;
		cout << "\nYour command (press [e] to quit program): ";
		string command;
		stringstream ss;
		string agv;
		arrayList<string> agvList;
		getline(cin, command);
		ss.str(command);
		do {
			ss >> agv;
			if (ss.fail() || agv == "") {
				system("cls");
				break;
			}
			else agvList.addToList(agv);
		} while (true);
		if (agvList.list[0] == "e" && agvList.size == 1) return false;
		if (adminProcess(ad, user_list, db_st_list, db_tc_list, db_course_list, db_st_course_list, agvList) == true) {
			system("cls");
		}
		else {
			cout << "Error: command not found" << endl;
		}
	}
	return true;
}

bool adminProcess(Admin& ad, UserList& user_list, StudentList& db_st_list, TeacherList& db_tc_list, CourseList &db_course_list, StudentCourseList &db_st_course_list, arrayList<string> agvList) {
	if (agvList.list[0] == "cp") {
		return cp(ad, agvList, user_list);
	}
	else if (agvList.list[0] == "as")
	{
		if (ad.addStudent(db_st_list, user_list) == 1) {
			cout << "Add Student \"" << user_list.list[user_list.size - 1].username << "\" successful!" << endl;
		}
		else {
			cout << "Add Student unsuccessful!\nMay be error in your input or the same username have exist." << endl;
		}
		cout << "PRESS ENTER TO GO BACK\n";
		cin.get();
		return true;
	}
	else if (agvList.list[0] == "at")
	{
		if (ad.addTeacher(db_tc_list, user_list) == 1) {
			cout << "Add Teacher \"" << user_list.list[user_list.size - 1].username << "\" successful!" << endl;
		}
		else {
			cout << "Add Teacher unsuccessful!\nMay be error or the same username have exist." << endl;
		}
		cout << "PRESS ENTER TO GO BACK\n";
		cin.get();
		return true;
	}
	else if (agvList.list[0] == "ss") {
		if (agvList.size > 1) {
			agvList.removeFromList(0);
			for (size_t i = 0; i < agvList.size; i++) {
				to_upper(agvList.list[i]);
			}
			StudentList sList = db_st_list.findStudentByNameKeyWord(agvList.list, agvList.size);
			if (sList.size == 0) {
				cout << "Error: Failed to find data" << endl;
			}
			else {
				system("cls");
				sList.print();
			}
		}
		else if (agvList.size == 1) {
			cout << "Students to search: ";
			string command;
			stringstream ss;
			string st_name;
			arrayList<string> st_list;
			getline(cin, command);
			ss.str(command);
			do {
				ss >> st_name;
				if (ss.fail() || st_name == "") {
					break;
				}
				else {
					to_upper(st_name);
					st_list.addToList(st_name);
				}
			} while (true);
			StudentList sList = db_st_list.findStudentByNameKeyWord(st_list.list, st_list.size);
			if (sList.size == 0) {
				cout << "Error: Failed to find data" << endl;
			}
			else {
				system("cls");
				sList.print();
			}
		}
		cout << "PRESS ENTER TO GO BACK\n";
		cin.get();
		return true;
	}
	else if (agvList.list[0] == "st") {
		if (agvList.size > 1) {
			agvList.removeFromList(0);
			for (size_t i = 0; i < agvList.size; i++) {
				to_upper(agvList.list[i]);
			}
			TeacherList tList = db_tc_list.findTeacherByNameKeyword(agvList.list, agvList.size);
			if (tList.size == 0) {
				cout << "Error: Failed to find data" << endl;
			}
			else {
				system("cls");
				tList.print();
			}
		}
		else if (agvList.size == 1) {
			cout << "Teachers to search: ";
			string command;
			stringstream ss;
			string tc_name;
			arrayList<string> tc_list;
			getline(cin, command);
			ss.str(command);
			do {
				ss >> tc_name;
				if (ss.fail() || tc_name == "") {
					break;
				}
				else {
					to_upper(tc_name);
					tc_list.addToList(tc_name);
				}
			} while (true);
			TeacherList tList = db_tc_list.findTeacherByNameKeyword(tc_list.list, tc_list.size);
			if (tList.size == 0) {
				cout << "Error: Failed to find data" << endl;
			}
			else {
				system("cls");
				tList.print();
			}
		}
		cout << "PRESS ENTER TO GO BACK\n";
		cin.get();
		return true;
	}
	else if (agvList.list[0] == "ru") {
		if (agvList.size == 1) {
			cout << "Input list of usernames you want to remove (separate by space):" << endl;
			string input;
			stringstream ss;
			string username;
			arrayList<string> removeList;
			getline(cin, input);
			ss.str(input);
			do {
				ss >> username;
				if (ss.fail() || username == "") {
					break;
				}
				else removeList.addToList(username);
			} while (true);
			arrayList<string> remove_unsuccess;
			for (size_t i = 0; i < removeList.size; i++) {
				if (ad.removeUser(removeList.list[i], user_list, db_st_list, db_tc_list, db_course_list, db_st_course_list) == 1) {

				}
				else {
					remove_unsuccess.addToList(removeList.list[i]);
				}
			}
			if (remove_unsuccess.size == 0) {
				cout << "Remove all user you in your list successful!" << endl;
			}
			else {
				cout << "Some user in your list remove unsuccessful! List:" << endl;
				for (size_t j = 0; j < remove_unsuccess.size; j++) {
					cout << j + 1 << ".\t" << remove_unsuccess.list[j] << endl;
				}
				cout << "Other user in your list remove successful!" << endl;
			}
			cout << "PRESS ENTER TO GO BACK\n";
			cin.get();
			return true;
		}
		else
		{
			arrayList<string> remove_unsuccess;
			for (size_t i = 1; i < agvList.size; i++) {
				if (ad.removeUser(agvList.list[i], user_list, db_st_list, db_tc_list, db_course_list, db_st_course_list) == 1) {

				}
				else {
					remove_unsuccess.addToList(agvList.list[i]);
				}
			}
			if (remove_unsuccess.size == 0) {
				cout << "Remove all user in your list successful!" << endl;
			}
			else {
				cout << "Some user in your list remove unsuccessful! List:" << endl;
				for (size_t j = 0; j < remove_unsuccess.size; j++) {
					cout << j + 1 << ".\t" << remove_unsuccess.list[j] << endl;
				}
				cout << "Other user in your list remove successful!" << endl;
			}
			cout << "PRESS ENTER TO GO BACK\n";
			cin.get();
			return true;
		}
	}
	else if (agvList.list[0] == "h") {
		if (agvList.size == 1) {
			system("cls");
			cout << setw(40) << setfill('-') << "-" << "HELP (ADMIN)" << setw(40) << setfill('-') << "-" << endl << endl;
			cout << setw(40) << setfill(' ') << left << "Change password" << "[cp]" << endl;
			cout << "Input <cp> <newpassword> to change. Or input <cp> then input <newpassword>." << endl << endl;
			cout << setw(40) << setfill(' ') << left << "Show teacher" << "[t]" << endl;
			cout << "Show all teacher in database." << endl << endl;
			cout << setw(40) << setfill(' ') << left << "Show student" << "[s]" << endl;
			cout << "Show all student in database." << endl << endl;
			cout << setw(40) << setfill(' ') << left << "Add Teacher" << "[at]" << endl;
			cout << "Input <at> then input teacher's informations." << endl << endl;
			cout << setw(40) << setfill(' ') << left << "Add Student" << "[as]" << endl;
			cout << "Input <as> then input student's informations." << endl << endl;
			cout << setw(40) << setfill(' ') << left << "Remove User" << "[ru]" << endl;
			cout << "Input <ru> then input list of usernames. Or input <ru> <list of username you want to remove (separate by space)>." << endl << endl;
			cout << setw(40) << setfill(' ') << left << "Search Teacher by name" << "[st]" << endl;
			cout << "Input <st> <list of teachers' name> to search. Or input <st> then input <name>." << endl;
			cout << "Input as this format <identify, name, birthday, \"phone number\", \"hometown\"> (separate by comma):" << endl << endl;
			cout << setw(40) << setfill(' ') << left << "Search Student by name" << "[ss] <name>" << endl;
			cout << "Input <ss> <list of students' name> to search. Or input <ss> then input <name>." << endl;
			cout << "Input as this format <number, name, birthday, \"hometown\"> (separate by comma):" << endl << endl;
			cout << setw(40) << setfill(' ') << left << "Log out" << "[lo]" << endl;
			cout << "Input <lo> to log out. (Then you can log in as another user)." << endl << endl;
			//cout << "Input anything to return." << endl;
			/*getchar();
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			system("cls");*/
			cout << "PRESS ENTER TO GO BACK\n";
			cin.get();
			return true;
		}
	}
	else if (agvList.list[0] == "t") {
		db_tc_list.print();
		//cout << "Input anything to return." << endl;
		/*getchar();
		system("cls");
		cin.clear();
		cin.ignore(INT_MAX, '\n');*/
		cout << "PRESS ENTER TO GO BACK\n";
		cin.get();
		return true;
	}
	else if (agvList.list[0] == "s") {
		db_st_list.print();
		//cout << "Input anything to return." << endl;
		/*getchar();
		system("cls");
		cin.clear();
		cin.ignore(INT_MAX, '\n');*/
		cout << "PRESS ENTER TO GO BACK\n";
		cin.get();
		return true;
	}
	else if (agvList.list[0] == "lo") {
		ad.logout();
		system("cls");
		return true;
	}
	return false;
}

#pragma endregion