#include "DBHelper.h"

bool loadUsers(UserList &user_list) {
	ifstream file;
	file.open("user.csv", ios::in);
	if (file.is_open() == NULL) {
		return false;
	}
	else {
		string line;
		while (getline(file, line)) {
			User data;
			string str;
			stringstream ss;
			ss.str(line);

			getline(ss, str, ',');
			data.username = str;

			getline(ss, str, ',');
			data.password = str;

			getline(ss, str, ',');
			data.role = str;

			user_list.addToList(data);
		}
		file.close();
		return true;
	}
}
bool loadCourse(CourseList &courseList) {
	ifstream file;
	file.open("course.csv", ios::in);
	if (file.is_open() == NULL) {
		return false;
	}
	else {
		string line;
		while (getline(file, line)) {
			Course data;
			string str;
			stringstream ss;
			ss.str(line);

			getline(ss, str, ',');
			data.course_id = str;

			getline(ss, str, ',');
			data.fal_id = str;

			getline(ss, str, ',');
			data.falcuty = str;

			getline(ss, str, ',');
			data.sub_id = str;

			getline(ss, str, ',');
			data.sub_name = str;

			getline(ss, str, ',');
			istringstream(str) >> data.max_st;

			getline(ss, str, ',');
			istringstream(str) >> data.total_st;

			getline(ss, str, ',');
			istringstream(str) >> data.credit;

			courseList.addToList(data);
		}
		file.close();
		return true;
	}
}
bool loadStudentCourse(StudentCourseList &st_course_list) {
	ifstream file;
	file.open("student_course.csv", ios::in);
	if (file.is_open() == NULL) {
		return false;
	}
	else {
		string line;
		while (getline(file, line)) {
			studentCourse data;
			string str, str1, str2, str3;
			stringstream ss, sstr1, sstr2, sstr3;
			ss.str(line);

			getline(ss, str, ';');
			getline(ss, str1, ';');
			getline(ss, str2, ';');
			getline(ss, str3);

			istringstream(str) >> data.st_num;

			sstr1.str(str1);
			while (getline(sstr1, str1, ',')) {
				data.st_course.addToList(str1);
			}

			sstr2.str(str2);
			while (getline(sstr2, str2, ',')) {
				double num;
				istringstream(str2) >> num;
				data.st_point.addToList(num);
			}

			double st_gpa;
			istringstream(str3) >> st_gpa;

			st_course_list.addToList(data);
		}
		file.close();
		return true;
	}
}
bool loadStudentInfo(StudentList &st_list) {
	ifstream file;
	file.open("student.csv", ios::in);
	if (file.is_open() == NULL) {
		return false;
	}
	else {
		string line;
		while (getline(file, line)) {
			Student data;
			string str;
			stringstream ss;
			ss.str(line);

			getline(ss, str, ',');
			istringstream(str) >> data.st_number;

			getline(ss, str, ',');
			data.st_name = str;

			getline(ss, str, ',');
			data.st_birthday = str;

			getline(ss, str);
			data.st_home_town = str;

			st_list.addToList(data);
		}
		file.close();
		return true;
	}
}
bool loadTeacherInfo(TeacherList& tc_list){
	ifstream file;
	file.open("teacher.csv", ios::in);
	if (file.is_open() == NULL) {
		return false;
	}
	else {
		string line;
		while (getline(file, line)) {
			Teacher data;
			string str;
			stringstream ss;
			ss.str(line);

			getline(ss, str, ',');
			data.tc_identify = str;

			getline(ss, str, ',');
			data.tc_name = str;

			getline(ss, str, ',');
			data.tc_birthday = str;

			getline(ss, str, ',');
			data.tc_phone_number = str;

			getline(ss, str);
			data.tc_home_town = str;

			tc_list.addToList(data);
		}
		file.close();
		return true;
	}
}
void writeToCouresFile(CourseList &courseList) {
	ofstream file;
	file.open("course.csv", ios::out);
	for (size_t i = 0; i<courseList.size; i++) {
		file << courseList.list[i].course_id << ",";
		file << courseList.list[i].falcuty << ",";
		file << courseList.list[i].sub_id << ",";
		file << courseList.list[i].sub_name << ",";
		file << courseList.list[i].max_st << ",";
		file << courseList.list[i].total_st << ",";
		file << courseList.list[i].credit << "\n";
	}
	file.close();
}
void writeToStudentFile(StudentList &st_list) {
	ofstream file;
	file.open("student.csv", ios::out);
	for (size_t i = 0; i< st_list.size; i++) {
		file << st_list.list[i].st_number << ",";
		file << st_list.list[i].st_name << ",";
		file << st_list.list[i].st_birthday << ",";
		file << st_list.list[i].st_home_town << "\n";
	}
	file.close();
}
void writeToTeacherFile(TeacherList &tc_list){
	ofstream file;
	file.open("teacher.csv", ios::out);
	for (size_t i = 0; i < tc_list.size; i++){
		file << tc_list.list[i].tc_identify << ",";
		file << tc_list.list[i].tc_name << ",";
		file << tc_list.list[i].tc_birthday << ",";
		file << tc_list.list[i].tc_phone_number << ",";
		file << tc_list.list[i].tc_home_town << "\n";
	}
	file.close();
}
void writeToStudentCourseFile(StudentCourseList &st_course_list) {
	ofstream file;
	file.open("student_course.csv", ios::out);

	for (size_t i = 0; i< st_course_list.size; i++) {
		int num = st_course_list.list[i].getCourseNum();
		file << st_course_list.list[i].st_num << ";";

		for (size_t j = 0; j < num; j++) {
			if (j == num - 1) {
				file << st_course_list.list[i].st_course.list[j] << ";";
			}
			else {
				file << st_course_list.list[i].st_course.list[j] << ",";
			}
		}

		for (size_t j = 0; j < num; j++) {
			if (j == num - 1) {
				file << st_course_list.list[i].st_point.list[j] << ";";
			}
			else {
				file << st_course_list.list[i].st_point.list[j] << ",";
			}
		}
		file << st_course_list.list[i].getGPA() << endl;
	}
	file.close();
}
void writeToUserFile(UserList &user_list) {
	ofstream file;
	file.open("user.csv", ios::out);
	for (size_t i = 0; i< user_list.size; i++) {
		file << user_list.list[i].username << ",";
		file << user_list.list[i].password << ",";
		file << user_list.list[i].role << "\n";
	}
	file.close();
}