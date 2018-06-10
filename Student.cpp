#include "Student.h"
using namespace std;

void Student::getSemesterCredit(studentCourse& enrolledCourse, CourseList* db_courseList) {
	arrayList<string> current_course_id;
	arrayList<string> done_course_id;
	for (size_t i = 0; i < enrolledCourse.st_course.size; i++) {
		if (enrolledCourse.st_point.list[i] == -1) {
			current_course_id.addToList(enrolledCourse.st_course.list[i]);
		}
		else {
			done_course_id.addToList(enrolledCourse.st_course.list[i]);
		}
	}
	CourseList* st_course_detail = db_courseList->findAllCourseById(current_course_id);
	CourseList* _st_course_detail = db_courseList->findAllCourseById(done_course_id);
	int credit = 0;
	int _credit = 0;
	double sum = 0;// for gpa's calulation
	for (size_t i = 0; i < st_course_detail->size; i++) {
		credit += st_course_detail->list[i].credit;
	}
	enrolledCourse.curr_credit = credit;

	for (size_t i = 0; i < _st_course_detail->size; i++) {
		int index;
		enrolledCourse.st_course.isExist(_st_course_detail->list[i].course_id, index);
		_credit += _st_course_detail->list[i].credit;
		sum += _st_course_detail->list[i].credit*enrolledCourse.st_point.list[index];
	}
	enrolledCourse.done_credit = _credit;
	enrolledCourse.setGPA(sum / _credit);
}

bool Student::getStudentCourse(StudentCourseList db_st_course_list, studentCourse& enrolledCourse, CourseList* db_courseList) {
	for (size_t i = 0; i < db_st_course_list.size; i++) {
		if (db_st_course_list.list[i].st_num == this->st_number) {
			enrolledCourse = db_st_course_list.list[i];
			getSemesterCredit(enrolledCourse, db_courseList);
			return true;
		}
	}	
	return false;
}
bool Student::modifyBaseStudentCourse(StudentCourseList& db_st_course_list, studentCourse enrolledCourse) {
	bool edit = false;
	for (size_t i = 0; i < db_st_course_list.size; i++) {
		if (db_st_course_list.list[i].st_num == this->st_number) {
			edit = true;
			if (enrolledCourse.isExist()){
				db_st_course_list.list[i] = enrolledCourse;
			}
			else db_st_course_list.removeFromList_(enrolledCourse);
			return true;
		}
	}
	if (edit == false) {
		if (enrolledCourse.isExist()) {
			db_st_course_list.addToList(enrolledCourse);
		}
	}
	return false;
}
void Student::showStudentCourse(CourseList* db_courseList, studentCourse enrolledCourse) {
	if (enrolledCourse.isExist()) {
		CourseList* st_course_detail = db_courseList->findAllCourseById(enrolledCourse.st_course);
		cout << setfill('-') << setw(115) << "-" << setfill(' ') << endl;
		cout << left << setw(5) << "STT"
			<< left << setw(30) << "Giao vien huong dan"
			<< left << setw(20) << "Ma so khoa hoc"
			<< left << setw(15) << "Ma mon hoc"
			<< left << setw(30) << "Ten mon hoc"
			<< left << setw(10) << "Diem"
			<< left << setw(10) << "Tin chi" << endl;
		cout << setfill('-') << setw(50) << setfill(' ') << endl;
		for (size_t i = 0; i < enrolledCourse.st_course.size; i++) {
			int index = 0;
			enrolledCourse.st_course.isExist(st_course_detail->list[i].course_id, index);
			cout << left << setw(5) << i + 1
				<< left << setw(30) << st_course_detail->list[i].falcuty
				<< left << setw(20) << st_course_detail->list[i].course_id
				<< left << setw(15) << st_course_detail->list[i].sub_id
				<< left << setw(30) << st_course_detail->list[i].sub_name
				<< left << setw(10) << enrolledCourse.st_point.list[index]
				<< left << setw(10) << st_course_detail->list[i].credit << endl;
		}
		cout << endl;
		enrolledCourse.getGPA();
		cout << "Your GPA: " << setprecision(3) << enrolledCourse.getGPA() << endl;
	}
	else cout << "You haven't enroll in any course" << endl;
};
bool Student::joinCourse(studentCourse enrolledCourse, arrayList<string>&courseId, StudentCourseList& db_st_course_list, CourseList& db_course_list) {
	if (st_number == enrolledCourse.st_num) {
		arrayList<string> error_course;
		for (size_t i = 0; i < courseId.size; i++) {
			Course* course_detail = db_course_list.findCourseById(courseId.list[i]);
			if (db_course_list.isCourseExist(courseId.list[i], *course_detail)) {
				if (enrolledCourse.addCourse(courseId.list[i], course_detail->credit)) {
					db_course_list.addStudentToCourse(courseId.list[i]);
				}
				else {
					error_course.addToList(courseId.list[i]);
				}
			}
			else {
				error_course.addToList(courseId.list[i]);
			}
		}
		modifyBaseStudentCourse(db_st_course_list, enrolledCourse);
		courseId = error_course;
		return true;
	}
	else return false;
};
bool Student::cancelCourse(studentCourse enrolledCourse, arrayList<string> courseId, StudentCourseList& db_st_course_list, CourseList& db_course_list) {
	if (enrolledCourse.isExist()) {
		for (size_t i = 0; i < courseId.size; i++) {
			if (enrolledCourse.hasEnrolled(courseId.list[i]) == true) {
				int index = 0;
				enrolledCourse.st_course.isExist(courseId.list[i], index);
				if (enrolledCourse.st_point.list[index] == -1) {
					enrolledCourse.st_course.removeFromList_(courseId.list[i]);
					enrolledCourse.st_point.removeFromList(index);
					db_course_list.removeStudentToCourse(courseId.list[i]);
				}
			}
		}
		modifyBaseStudentCourse(db_st_course_list, enrolledCourse);
		return true;
	}
	else return false;
};
CourseList* Student::searchForCourseByName(arrayList<string> cList, CourseList db_course_list) {
	CourseList* course_list = NULL;
	for (size_t i = 0; i < db_course_list.size; i++) {
		for (size_t j = 0; j < cList.size; j++) {
			course_list = db_course_list.findAllCourseById(cList);
		}
	}
	return course_list;
}
inline bool operator==(Student &lhs, Student &rhs) {
	return lhs.st_number == rhs.st_number;
}
inline bool operator==(Student &lhs, int &rhs) {
	return lhs.st_number == rhs;
}
inline bool operator==(int &lhs, Student &rhs) {
	return lhs == rhs.st_number;
}
inline bool operator!=(Student &lhs, Student &rhs) {
	return !(lhs.st_number == rhs.st_number);
}
inline bool operator!=(Student &lhs, int &rhs) {
	return !(lhs.st_number == rhs);
}
inline bool operator!=(int &lhs, Student &rhs) {
	return !(lhs == rhs.st_number);
}

inline bool operator==(studentCourse &lhs, studentCourse&rhs) {
	return lhs.st_num == rhs.st_num;
}
//-----------------STUDENT_LIST------------------------
StudentList StudentList::findStudentByNameKeyWord(string keyword[], size_t n) {
	StudentList* stList = new StudentList();
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < n; j++) {
			if (list[i].st_name.find(keyword[j]) != string::npos) {
				Student data = list[i];
				stList->addToList(data);
				break;
			}
		}
	}
	return *stList;
}

void StudentList::removeStudentByNameKeyWord(string keyword[], size_t n) {
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < n; j++) {
			if (list[i].st_name.find(keyword[j]) != string::npos) {
				removeFromList(i);
				break;
			}
		}
	}
}
void StudentList::updateStudentList(Student data) {
	for (size_t i = 0; i < size; i++) {
		if (data.st_number == this->list[i].st_number) {
			this->list[i] = data;
		}
	}
}

bool StudentList::getStudentInfo(Student& st) {
	int st_num;
	istringstream(st.username) >> st_num;

	for (size_t i = 0; i < size; i++) {
		if (st_num == this->list[i].st_number) {
			st.st_number = this->list[i].st_number;
			st.st_name = this->list[i].st_name;
			st.st_birthday = this->list[i].st_birthday;
			st.st_home_town = this->list[i].st_home_town;
			return true;
		}
	}
	return false;
}

//Tim sinh vien va diem cua sinh vien tham gia mot khoa hoc nhat dinh.
StudentCourseList* StudentCourseList::findStudentJoinCourse(string courseID){
	StudentCourseList* data = new StudentCourseList();
	int a = 0;
	for (size_t i = 0; i < this->size; i++){
		for (size_t j = 0; j < this->list[i].st_course.size; j++){
			if (this->list[i].st_course.list[j].compare(courseID) == 0){
				data->list[a].st_num = this->list[i].st_num;
				data->list[a].st_point.list[0] = this->list[i].st_point.list[j];
				data->list[a].st_course.list[0] = this->list[i].st_course.list[j];
				data->size++;
				a++;
			}
		}
	}
	return data;
}
//Ghi diem vao file student_course.
void StudentCourseList::updatePoint( StudentCourseList st_join_course){
	int i = 0;
	for (size_t j = 0; j < this->size; j++){
		for (size_t k = 0; k < this->list[j].st_course.size; k++){
			if (st_join_course.list[i].st_course.list[0].compare(this->list[j].st_course.list[k]) == 0){
				this->list[j].st_point.list[k] = st_join_course.list[i].st_point.list[0];
				i++;
			}
		}
	}
}

//Xem khoa hoc da dc cham diem chua.
bool StudentCourseList::isGrade(){
	for (int i = 0; i < this->size; i++){
		if (this->list[i].st_point.list[0] != -1)
			return true;
	}
	return false;
}

void StudentList::print()
{
	cout << setw(10) << "ID" << setw(30) << "Name" << setw(15) << "Birthday" << setw(50) << "Hometown" << endl;
	for (int i = 0; i < this->size; i++)
	{
		cout
			<< setw(10) << this->list[i].st_number
			<< setw(30) << this->list[i].st_name
			<< setw(15) << this->list[i].st_birthday
			<< setw(50) << this->list[i].st_home_town
			<< endl;
	}
}