#include "Course.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

string toUpperCase(string&input) {
	for (string::iterator i = input.begin(); i != input.end(); i++) {
		*i = toupper(*i);
	}
	return input;
}

inline bool operator==(Course &lhs, Course &rhs) {
	return lhs.course_id == rhs.course_id;
}
inline bool operator==(Course &lhs, string &rhs) {
	return lhs.course_id == rhs;
}
inline bool operator==(string &lhs, Course &rhs) {
	return lhs == rhs.course_id;
}
inline bool operator!=(Course &lhs, Course &rhs) {
	return !(lhs.course_id == rhs.course_id);
}
inline bool operator!=(Course &lhs, string &rhs) {
	return !(lhs.course_id == rhs);
}
inline bool operator!=(string &lhs, Course &rhs) {
	return !(lhs == rhs.course_id);
}

bool CourseList::addToCourseList(Course newCourse){
	newCourse.total_st = 0;
	/*if (this->isCourseExist(newCourse.course_id) == true)
		return false;
	else{
		this->addToList(newCourse);
		return true;
	}*/
	Course dummy;
	if (this->isCourseExist(newCourse.course_id, dummy) == true)
		return false;
	else{
		this->addToList(newCourse);
		return true;
	}

}

void Course::printCourseInfo(){

	cout << setfill('-') << setw(50) << "-" << "New Course" << setfill('-') << setw(55) << "-" << setfill(' ') << endl;
	cout
		<< left << setw(20) << "Course Id"
		<< left << setw(10) << "Fal ID"
		<< left << setw(25) << "Falcuty"
		<< left << setw(15) << "Sub_Id"
		<< left << setw(35) << "Subject Name"

		<< left << setw(6) << "Credit" << endl;
	cout << setfill('-') << setw(110) << "-" << setfill(' ') << endl;

	cout
		<< left << setw(20) << this->course_id
		<< left << setw(10) <<this->fal_id
		<< left << setw(25) << this->falcuty
		<< left << setw(15) << this->sub_id
		<< left << setw(35) << this->sub_name

		<< left << setw(6) << this->credit << endl;

}

Course* CourseList::findCourseById(string id) {
	for (size_t i = 0; i < size; i++) {
		if (list[i].course_id == id) {
			return &list[i];
		}
	}
	return NULL;
}
CourseList*  CourseList::findCourseByName(string name) {
	CourseList* cList = new CourseList();
	for (size_t i = 0; i < size; i++) {
		string s = this->list[i].sub_name;
		toUpperCase(s);
		toUpperCase(name);
		int found = s.find(name);
		if (found != string::npos) {
			cList->addToList(list[i]);
		}
	}
	return cList;
}

CourseList*  CourseList::findAllCourseById(arrayList<string> id_list) {
	CourseList* cList = new CourseList();
	for (size_t i = 0; i < this->size; i++) {
		string s = this->list[i].course_id;
		for (size_t j = 0; j < id_list.size; j++) {
			string s1 = id_list.list[j];
			toUpperCase(s);
			toUpperCase(s1);
			if (s == s1) {
				cList->addToList(list[i]);
				break;
			}
		}
	}
	return cList;
}
CourseList* CourseList::findAllCourseByName(arrayList<string> name_list) {
	CourseList* cList = new CourseList();
	for (size_t i = 0; i < this->size; i++) {
		string s = this->list[i].sub_name;
		for (size_t j = 0; j < name_list.size; j++) {
			string s1 = name_list.list[j];
			toUpperCase(s);
			toUpperCase(s1);
			int found = s.find(s1);
			if (found != string::npos) {
				cList->addToList(list[i]);
				break;
			}
		}
	}
	return cList;
}
void  CourseList::addStudentToCourse(string course_id) {
	for (size_t i = 0; i < this->size; i++) {
		if (this->list[i].course_id == course_id) {
			this->list[i].total_st++;
			this->list[i].isCourseFull();
			break;
		}
	}
}
void  CourseList::removeStudentToCourse(string course_id) {
	for (size_t i = 0; i < this->size; i++) {
		if (this->list[i].course_id == course_id && this->list[i].total_st > 0) {
			this->list[i].total_st--;
			break;
		}
	}
}
void CourseList::printCourse() {
	cout << setfill('-') << setw(50) << "-" << "Course" << setfill('-') << setw(50) << "-" << setfill(' ') << endl;
	cout << left << setw(5) << "STT"
		<< left << setw(10) << "Course Id"
		<< left << setw(25) << "Falcuty"
		<< left << setw(15) << "Sub_id"
		<< left << setw(25) << "Subject Name"
		<< left << setw(15) << "Student/Slot"
		<< left << setw(6) << "Credit" << endl;
	cout << setfill('-') << setw(110) << "-" << setfill(' ') << endl;
	for (size_t i = 0; i < this->size; i++) {
		ostringstream  buffer;
		buffer << this->list[i].total_st << "/" << this->list[i].max_st;
		cout << left << setw(5) << i + 1
			<< left << setw(10) << this->list[i].course_id
			<< left << setw(25) << this->list[i].falcuty
			<< left << setw(15) << this->list[i].sub_id
			<< left << setw(25) << this->list[i].sub_name
			<< left << setw(15) << buffer.str()
			<< left << setw(6) << this->list[i].credit << endl;
	}
}
CourseList* CourseList::findCourseByFacuty(string fal) {
	CourseList* cList = new CourseList();
	for (size_t i = 0; i < size; i++) {
		string s = this->list[i].falcuty;
		toUpperCase(s);
		toUpperCase(fal);
		if (s.find(fal) != string::npos) {
			cList->addToList(list[i]);
		}
	}
	return cList;
}
CourseList* CourseList::findAllCourseByFalcuty(arrayList<string> fal_list) {
	CourseList* cList = new CourseList();
	for (size_t i = 0; i < this->size; i++) {
		string s = this->list[i].falcuty;
		for (size_t j = 0; j < fal_list.size; j++) {
			string s1 = fal_list.list[j];
			toUpperCase(s);
			toUpperCase(s1);
			int found = s.find(s1);
			if (found != string::npos) {
				cList->addToList(list[i]);
				break;
			}
		}
	}
	return cList;
}

CourseList* CourseList::findCourseByFacutyId(string fal_id) {
	CourseList* cList = new CourseList();
	for (size_t i = 0; i < size; i++) {
		string s = this->list[i].fal_id;
		toUpperCase(s);
		toUpperCase(fal_id);
		if (s.find(fal_id) != string::npos) {
			cList->addToList(list[i]);
		}
	}
	return cList;
}
CourseList* CourseList::findAllCourseByFalcutyId(arrayList<string> falid_list) {
	CourseList* cList = new CourseList();
	for (size_t i = 0; i < this->size; i++) {
		string s = this->list[i].fal_id;
		for (size_t j = 0; j < falid_list.size; j++) {
			string s1 = falid_list.list[j];
			toUpperCase(s);
			toUpperCase(s1);
			int found = s.find(s1);
			if (found != string::npos) {
				cList->addToList(list[i]);
				break;
			}
		}
	}
	return cList;
}
bool CourseList::isCourseExist(string id, Course&out_data) {
	Course* tmp = new Course();
	tmp = findCourseById(id);	
	if (tmp == NULL) {
		return false;
	}
	else
	{
		out_data = *tmp;
		return true;
	}
}