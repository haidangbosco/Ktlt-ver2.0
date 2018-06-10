#include "Admin.h"
using namespace std;

bool Admin::addUser(User user, UserList &db_user_list) {
	if (db_user_list.findUserByUsername(user.username) != -1) {
		return 0;
	}
	else {
		db_user_list.addToList(user);
		return 1;
	}
}

bool Admin::removeUser(string username, UserList &db_user_list, StudentList &db_st_list, TeacherList &db_tc_list, CourseList &db_course_list, StudentCourseList &db_st_course_list) {
	int index = db_user_list.findUserByUsername(username);
	if (index == -1 || db_user_list.list[index].role == "admin") {
		return 0;
	}
	else {
		string s = db_user_list.list[index].role;
		if (s == "student") {
			stringstream ss;
			ss.str(username);
			int id;
			ss >> id;
			for (size_t i = 0; i < db_st_list.size; i++) {
				if (db_st_list.list[i].st_number == id) {
					studentCourse enrolled_course;
					CourseList* db_courseList = new CourseList();
					db_st_list.list[i].getStudentCourse(db_st_course_list, enrolled_course, db_courseList);
					for (size_t j = 0; j < enrolled_course.st_course.size; j++) {
						for (size_t k = 0; k < db_course_list.size; k++) {
							if (db_course_list.list[k].course_id == enrolled_course.st_course.list[j]) {
								db_course_list.list[k].total_st--;
							}
						}
					}
					/*
					arrayList<string> as; // Can not replace "as" by "enrolled_course.st_course"
					as = enrolled_course.st_course;
					db_st_list.list[i].cancelCourse(enrolled_course, as, db_st_course_list, db_course_list); //cancel all student course (student_course.csv)
					*/
					db_st_list.removeFromList(i); //delete student from student.csv
					break;
				}
			}
			for (size_t i = 0; i < db_st_course_list.size; i++) {
				if (db_st_course_list.list[i].st_num == id) {
					db_st_course_list.removeFromList(i);
					break;
				}
			}
		}
		else {
			//string name;
			//remove all student from this teacher course (student_course.csv)
			for (size_t i = 0; i < db_tc_list.size; i++) {
				if (db_tc_list.list[i].tc_identify == username) {
					CourseList* tc_open_course = new CourseList();
					tc_open_course = db_tc_list.list[i].teacherCourse(db_course_list);
					for (size_t j = 0; j < tc_open_course->size; j++) {
						/*
						arrayList<string> as;
						as.addToList(tc_open_course->list[j].course_id);
						*/
						for (size_t k = 0; k < db_st_course_list.size; k++) {
							for (size_t l = 0; l < db_st_course_list.list[k].st_course.size; l++) {
								if (db_st_course_list.list[k].st_course.list[l] == tc_open_course->list[j].course_id) {
									if (db_st_course_list.list[k].st_course.size > 1) {
										db_st_course_list.list[k].st_course.removeFromList(l);
										db_st_course_list.list[k].st_point.removeFromList(l);
										for (size_t m = 0; m < db_st_list.size; m++) {
											if (db_st_list.list[m].st_number == db_st_course_list.list[k].st_num) {
												studentCourse enrolled_course;
												CourseList* db_courseList = new CourseList();
												db_st_list.list[m].getStudentCourse(db_st_course_list, enrolled_course, db_courseList);
												db_st_list.list[m].modifyBaseStudentCourse(db_st_course_list, enrolled_course);
											}
										}
									}
									else {
										db_st_course_list.removeFromList(k);
										k--;
									}
									break;
								}
							}
							/*
							if (db_st_course_list.list[k].hasEnrolled(tc_open_course->list[j].course_id)) {
								for (size_t l = 0; l < db_st_list.size; l++) {
									if (db_st_list.list[l].st_number == db_st_course_list.list[k].st_num) {
										studentCourse enrolled_course;
										CourseList* db_courseList = new CourseList();
										db_st_list.list[l].getStudentCourse(db_st_course_list, enrolled_course, db_courseList);
										db_st_list.list[l].cancelCourse(enrolled_course, as, db_st_course_list, db_course_list);
									}
								}
							}
							*/
						}
						for (size_t n = 0; n < db_course_list.size; n++) {
							if (db_course_list.list[n].course_id == tc_open_course->list[j].course_id) {
								db_course_list.removeFromList(n);
								break;
							}
						}
					}
					//name = db_tc_list.list[i].tc_name;
					db_tc_list.removeFromList(i);
					break;
				}
			}
			//delete teacher course from course.csv
			/*
			for (size_t n = 0; n < db_course_list.size; n++) {
				while (db_course_list.list[n].falcuty == name) {
					db_course_list.removeFromList(n);
				}
			}
			*/
		}
		db_user_list.removeFromList(index); //delete user from user.csv
		return 1;
	}
}

bool Admin::addStudent(StudentList &db_st_list, UserList &db_user_list) {
	Student st;
	User student;
	student.role = "student";
	cout << "Input number, name, birthday, \"hometown\": (separate by comma)" << endl;
	string s;
	getline(cin, s, ',');
	if (s == "q" || s.find('\n') != -1) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return 0;
	}
	student.username = student.password = s;
	istringstream iss;
	iss.str(s);
	iss >> st.st_number;
	if (iss.fail() || st.st_number <0) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return 0;
	}
	getline(cin, s, ',');
	if (s.find('\n') != -1) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return 0;
	}
	to_upper(s);
	st.st_name = s;
	getline(cin, s, ',');
	if (s.find('\n') != -1) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return 0;
	}
	st.st_birthday = s;
	getline(cin, s);
	if (s.find('\n') != -1) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return 0;
	}
	st.st_home_town = s;
	if (addUser(student, db_user_list)) {
		db_st_list.addToList(st);
		return 1;
	}
	else {
		return 0;
	}
}

bool Admin::addTeacher(TeacherList &db_tc_list, UserList &db_user_list) {
	Teacher tc;
	User teacher;
	teacher.role = "teacher";
	cout << "Input identify, name, birthday, \"phone number\", \"hometown\": (separate by comma)" << endl;
	string s;
	getline(cin, s, ',');
	if (s == "q" || s.find('\n') != -1) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return 0;
	}
	tc.tc_identify = teacher.username = teacher.password = s;
	getline(cin, s, ',');
	if (s.find('\n') != -1) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return 0;
	}
	to_upper(s);
	tc.tc_name = s;
	getline(cin, s, ',');
	if (s.find('\n') != -1) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return 0;
	}
	tc.tc_birthday = s;
	getline(cin, s, ',');
	if (s.find('\n') != -1) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return 0;
	}
	tc.tc_phone_number = s;
	getline(cin, s);
	if (s.find('\n') != -1) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return 0;
	}
	tc.tc_home_town = s;
	if (addUser(teacher, db_user_list)) {
		db_tc_list.addToList(tc);
		return 1;
	}
	else {
		return 0;
	}
}