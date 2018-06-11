#include "Admin.h"

using namespace std;

//Loai bo khoang trang khoi string
inline string remove_space(string str) {
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}

//Kiem tra string co chua dau phay "," khong
inline bool check_comma(string np) {
	for (int i = 0; i < np.length(); i++) {
		if (np[i] == ',') return false;
	}
	return true;
}

//Kiem tra nam nhuan
inline bool isleapyear(unsigned short year) {
	return (!(year % 4) && (year % 100) || !(year % 400));
}

//Kiem tra ngay thang nam hop le
inline bool valid_date(unsigned short year, unsigned short month, unsigned short day) {
	unsigned short monthlen[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (!year || !month || !day || month>12)
		return 0;
	if (isleapyear(year) && month == 2)
		monthlen[1]++;
	if (day>monthlen[month - 1])
		return 0;
	return 1;
}

//Ham nhap ten
inline bool input_name(string &name) {
	string s;
	cout << "Input name:" << endl;
	getline(cin, s);
	if (check_comma(s) == 0) {
		return 0;
	}
	to_upper(s);
	for (unsigned int i = 0; i < s.length(); i++) {
		if (isalpha(s[i]) == 0 && s[i] != ' ') {
			return 0;
		}
	}
	name = s;
	return 1;
}

//Ham nhap ngay thang nam sinh
inline bool input_birthday(string &birthday) {
	string s;
	stringstream ss, ss2;
	char c;
	cout << "Input date of birth: (YYYY-MM-DD)" << endl;
	getline(cin, s);
	if (check_comma(s) == 0) {
		return 0;
	}
	s = remove_space(s);
	unsigned short d, m, y;
	ss.str(s);
	ss >> y;
	if (ss.fail()) {
		return 0;
	}
	ss >> c;
	ss >> m;
	if (ss.fail()) {
		return 0;
	}
	ss >> c;
	ss >> d;
	if (ss.fail()) {
		return 0;
	}
	if (valid_date(y, m, d) == 0) {
		return 0;
	}
	ss2 << y << '-';
	if (m < 10) {
		ss2 << '0';
	}
	ss2 << m << '-';
	if (d < 10) {
		ss2 << '0';
	}
	ss2 << d;
	ss2 >> s;
	birthday = s;
	return 1;
}

//Ham nhap que quan
inline bool input_hometown(string &hometown) {
	string s;
	cout << "Input hometown:" << endl;
	getline(cin, s);
	if (check_comma(s) == 0) {
		return 0;
	}
	hometown = "\"" + s + "\"";
	return 1;
}

//Ham them nguoi dung vao user.csv
bool Admin::addUser(User user, UserList &db_user_list) {
	if (db_user_list.findUserByUsername(user.username) != -1) {
		return 0;
	}
	else {
		db_user_list.addToList(user);
		return 1;
	}
}

//Ham xoa tat ca du lieu cua nguoi dung khoi database
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
					db_st_list.removeFromList(i);
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
			for (size_t i = 0; i < db_tc_list.size; i++) {
				if (db_tc_list.list[i].tc_identify == username) {
					CourseList* tc_open_course = new CourseList();
					tc_open_course = db_tc_list.list[i].teacherCourse(db_course_list);
					for (size_t j = 0; j < tc_open_course->size; j++) {
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
						}
						for (size_t n = 0; n < db_course_list.size; n++) {
							if (db_course_list.list[n].course_id == tc_open_course->list[j].course_id) {
								db_course_list.removeFromList(n);
								break;
							}
						}
					}
					db_tc_list.removeFromList(i);
					break;
				}
			}
		}
		db_user_list.removeFromList(index);
		return 1;
	}
}

//Ham them student
bool Admin::addStudent(StudentList &db_st_list, UserList &db_user_list) {
	Student st;
	User student;
	string s;
	stringstream ss, ss2;
	student.role = "student";
	cout << "Input number:" << endl;
	getline(cin, s);
	if (check_comma(s) == 0) {
		return 0;
	}
	s = remove_space(s);
	ss.str(s);
	ss >> st.st_number;
	if (ss.fail()) {
		return 0;
	}
	if (st.st_number < 0) {
		return 0;
	}
	ss2 << st.st_number;
	ss2 >> s;
	student.username = s;
	student.password = s;
	if (input_name(st.st_name) == 0) {
		return 0;
	}
	if (input_birthday(st.st_birthday) == 0) {
		return 0;
	}
	if (input_hometown(st.st_home_town) == 0) {
		return 0;
	}
	if (addUser(student, db_user_list) == 1) {
		db_st_list.addToList(st);
		return 1;
	}
	else {
		return 0;
	}
}

//Ham them teacher
bool Admin::addTeacher(TeacherList &db_tc_list, UserList &db_user_list) {
	Teacher tc;
	User teacher;
	string s;
	teacher.role = "teacher";
	cout << "Input identify:" << endl;
	getline(cin, s);
	if (check_comma(s) == 0) {
		return 0;
	}
	s = remove_space(s);
	if (s == "q") {
		return 0;
	}
	tc.tc_identify = s;
	teacher.username = s;
	teacher.password = s;
	if (input_name(tc.tc_name) == 0) {
		return 0;
	}
	if (input_birthday(tc.tc_birthday) == 0) {
		return 0;
	}
	cout << "Input phone:" << endl;
	getline(cin, s);
	for (unsigned int i = 0; i < s.length(); i++) {
		if (isdigit(s[i]) == 0) {
			return 0;
		}
	}
	tc.tc_phone_number = "\"" + s + "\"";
	if (input_hometown(tc.tc_home_town) == 0) {
		return 0;
	}
	if (addUser(teacher, db_user_list)) {
		db_tc_list.addToList(tc);
		return 1;
	}
	else {
		return 0;
	}
}