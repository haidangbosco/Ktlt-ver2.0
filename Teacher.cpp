#include "Teacher.h"
using namespace std;



CourseList* Teacher::teacherCourse(CourseList db_course_list){
	return db_course_list.findCourseByFacuty(this->tc_name);
}
CourseList* Teacher::tcSumCourse(CourseList db_course_list,StudentCourseList db_st_course_list){
	CourseList* tc_sumed = new CourseList();
	CourseList* tc = teacherCourse(db_course_list);
	StudentCourseList* data = new StudentCourseList();
	int i = 0;
	for (i; i < tc->size; i++){
		data = db_st_course_list.findStudentJoinCourse(tc->list[i].course_id);
		if (data->isGrade()){
			tc_sumed->addToList(tc->list[i]);
		}
	}
	return tc_sumed;
}

CourseList* Teacher::tcNotSumCourse(CourseList db_course_list, StudentCourseList db_st_course_list){
	CourseList* tc_nsumed = new CourseList();
	CourseList* tc = teacherCourse(db_course_list);
	StudentCourseList* data = new StudentCourseList();
	int i = 0;
	for (i; i < tc->size; i++){
		data = db_st_course_list.findStudentJoinCourse(tc->list[i].course_id);
		if (!(data->isGrade())){
			tc_nsumed->addToList(tc->list[i]);
		}
	}
	return tc_nsumed;
}

bool Teacher::gradingCourse(StudentCourseList& st_join_course){
	int flag = 0;
	cout << endl;
	cout << setw(40) << right << "\nStudent List:\n" << endl;
	cout << setw(5) << left << "STT";
	cout << setw(30) << left << "MSSV";
	cout << setw(20) << right << "Point\n";
	cout << setfill('-');
	cout << setw(55) << "-" << endl;
	cout << setfill(' ');
	for (size_t j = 0; j < st_join_course.size; j++){
		cout << setw(5) << left << j + 1;
		cout << setw(30) << left << st_join_course.list[j].st_num;
		cout << setw(20) << right << st_join_course.list[j].st_point.list[0] << endl;
	}

	if (st_join_course.isGrade()){
		int index;
		int a = 0;
		do{
			double spoint;

			cout << "Input student's index  to modify grade (press 0) to exit: ";
			cin >> index;
			cin.clear();
			cin.ignore(INT_MAX, '\n');

			if (index<0 || index>st_join_course.size || cin.bad() || index != (int)index){
				cout << "Wrong input, try again!\n";
				continue;
			}
			if (index == 0){
				flag++;
				break;
			}
			do{
				cout << "Input new grade for " << st_join_course.list[index - 1].st_num << " : ";
				cin >> spoint;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				if (spoint<-1 || spoint == 11 || spoint == 12 || spoint>13 || cin.bad()){
					cout << "Wrong input, try again!\n";
					continue;
				}
				st_join_course.list[index - 1].st_point.list[0] = spoint;
				flag++;
			} while (spoint<-1 || spoint == 11 || spoint == 12 || spoint>13 || cin.bad());
			
		} while (index != 0||cin.bad());
	}
	else{
		cout << "Sumarize ( input 11 to exit ) : \n";
		for (int i = 0; i<st_join_course.size; ++i){
			double spoint;
			do{
				cout << st_join_course.list[i].st_num << " : ";
				cin >> spoint;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				if (spoint == 11){
					break;
				}
				if (spoint<-1 || spoint == 12 || spoint>13 || cin.bad()){
					cout << "Wrong input, try again!\n";
					continue;
				}

			} while (spoint<-1 || spoint == 12 || spoint>13 || cin.bad());
			st_join_course.list[i].st_point.list[0] = spoint;
		}
	}
	if (flag!=1){
		cout << "\nSuccessfully modify student's grade!\n";
		cout << "Changes preview: \n";
		//*data = db_st_course_list.findStudentJoinCourse(tc_open_course->list[i].course_id); //lay danh sach sinh vien + diem ma sinh vien tham gia course;
		cout << endl;
		//cout << setw(40) << right << "__Danh Sach Sinh Vien Da Dang Ky__\n" << endl;
		cout << setw(5) << left << "STT";
		cout << setw(30) << left << "MSSV";
		cout << setw(20) << right << "Grade\n";
		cout << setfill('-');
		cout << setw(55) << "-" << endl;
		cout << setfill(' ');
		for (size_t j = 0; j < st_join_course.size; j++){
			cout << setw(5) << left << j + 1;
			cout << setw(30) << left << st_join_course.list[j].st_num;
			cout << setw(20) << right << st_join_course.list[j].st_point.list[0] << endl;
		}
	}
	return true;
}

void Teacher::showTeacherCouser(CourseList tc_course,StudentCourseList st_course){
	if (tc_course.size>0){
		cout << setfill('-') << setw(115) << "-" << setfill(' ') << endl;
		cout << left << setw(5) << "STT"
			<< left << setw(20) << "Course ID"
			<< left << setw(15) << "Sub ID"
			<< left << setw(50) << "Course Name"
			<< left << setw(10) << "Credit"
			<< left << setw(10) << "Num of student"
			<< endl;
		cout << setfill('-') << setw(50) << setfill(' ') << endl;
		for (size_t i = 0; i<tc_course.size; i++) {
			cout << left << setw(5) << i + 1
				<< left << setw(20) << tc_course.list[i].course_id
				<< left << setw(15) << tc_course.list[i].sub_id
				<< left << setw(50) << tc_course.list[i].sub_name
				<< left << setw(10) << tc_course.list[i].credit
				<< left << setw(10) << tc_course.list[i].total_st
				<< endl;
		}
	}
}


bool Teacher::openCourse(CourseList& db_course_list, Course newCourse){
	Course dummy;
	if (db_course_list.isCourseExist(newCourse.course_id,dummy)) return false;
	else {
		//Course newCourse;
		db_course_list.addToCourseList(newCourse);
	}

}

///Teacher_List_Modify

TeacherList TeacherList::findTeacherByNameKeyword(string keyword[], size_t n){
	TeacherList* tList = new TeacherList();
	for (size_t i = 0; i < this->size; i++) {
		for (size_t j = 0; j < n; j++) {
			if (list[i].tc_name.find(keyword[j]) != string::npos) {
				Teacher data = list[i];
				tList->addToList(data);
				break;
			}
		}
	}
	return *tList;
}

bool TeacherList::getTeacherInfo(Teacher& tc){

	for (size_t i = 0; i < size; i++) {

		if (tc.username.compare(this->list[i].tc_identify) == 0)
		{
			tc.tc_identify = this->list[i].tc_identify;
			tc.tc_name = this->list[i].tc_name;
			tc.tc_birthday = this->list[i].tc_birthday;
			tc.tc_phone_number = this->list[i].tc_phone_number;
			tc.tc_home_town = this->list[i].tc_home_town;
			return true;
		}
	}
	return false;

}

void TeacherList::removeTeacherByNameKeyword(string keyword[], size_t n){
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < n; j++) {
			if (list[i].tc_name.find(keyword[j]) != string::npos) {
				removeFromList(i);
				break;
			}
		}
	}
}

void TeacherList::updateTeacherList(Teacher data){
	for (size_t i = 0; i < size; i++) {
		if (data.tc_identify == this->list[i].tc_identify) {
			this->list[i] = data;
		}
	}
}

void TeacherList::print()
{
	cout << setw(10) << "ID" << setw(30) << "Name" << setw(15) << "Birthday" << setw(15) << "Phone Number" << setw(50) << "Hometown" << endl;
	for (int i = 0; i < this->size; i++)
	{
		cout
			<< setw(10) << this->list[i].tc_identify
			<< setw(30) << this->list[i].tc_name
			<< setw(15) << this->list[i].tc_birthday
			<< setw(15) << this->list[i].tc_phone_number
			<< setw(50) << this->list[i].tc_home_town
			<< endl;
	}
}