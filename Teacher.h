#ifndef _TEACHER_
#define _TEACHER_

#include<iostream>
#include <string>
#include <sstream>
#include "Helper.h"
#include "User.h"
#include "Course.h"
#include "Student.h"

using namespace std;


class Teacher :public User{
public:
	string tc_identify;
	string tc_name;
	string tc_birthday;
	string tc_phone_number;
	string tc_home_town;
	CourseList* teacherCourse(CourseList db_courseList); //nhung khoa hoc ma teacher da mo
	CourseList* tcSumCourse(CourseList db_course_list,StudentCourseList);
	CourseList* tcNotSumCourse(CourseList db_course_list, StudentCourseList);
	Teacher(){};
	Teacher(string id){
		this->tc_identify = id;
	}
	~Teacher(){};
	bool openNewCourse(Teacher& tc, StudentCourseList& db_st_course_list, CourseList& db_course_list){
		cout << "\t\t______________________OPEN COURSE__________________________\n";
		CourseList* sum = new CourseList();
		CourseList* nsum = new CourseList();
		sum = tc.tcSumCourse(db_course_list, db_st_course_list);
		nsum = tc.tcNotSumCourse(db_course_list, db_st_course_list);
		if (nsum->size >= 5){
			cout << "You has open 5 courses for  this term so you cannot open more course.\n";
			cout << "Press Enter to go back";
			cin.get();
			return true;
		}
		else{
			string newCourse_sub_id; //ms viet tat mon hoc
			string newCourse_class_id; //nhom lop
			string newCourse_id; //ms mon hoc
			string newCourse_name; //ten mon hoc
			float newCourse_max; //so luong sv toi da
			float newCourse_ncredit; //tin chi
			Course dummy;
			do{
				do{
					cout << "\nInput new sub_course ID you want to open: ";
					cin >> newCourse_sub_id;
					cin.ignore(INT_MAX, '\n');
					if (!tc.checkNewPass(newCourse_sub_id)) cout << "New course details do not allow special sign character (, ! # @...).Try again\n";
				} while (!tc.checkNewPass(newCourse_sub_id));
				do{
					cout << "Input class group: ";
					cin >> newCourse_class_id;
					cin.ignore(INT_MAX, '\n');
					if (!tc.checkNewPass(newCourse_class_id)) cout << "New course details do not allow special sign character (, ! # @...).Try again\n";
				} while (!tc.checkNewPass(newCourse_class_id));
				newCourse_id = newCourse_sub_id + newCourse_class_id;
				if (db_course_list.isCourseExist(newCourse_id, dummy)){
					cout << "You can not open an existed course. Try again! \n";
				}
			} while (db_course_list.isCourseExist(newCourse_id, dummy));

			cout << "Input new course details.\n";
			do{
				cout << "Input course name: ";
				getline(cin, newCourse_name);
				if (!tc.checkNewPass(newCourse_name)) cout << "New course details do not allow special sign character (, ! # @...).Try again\n";
			} while (!tc.checkNewPass(newCourse_name));

			do{
				cout << "Input student number limitation (at least 10) : "; cin >> newCourse_max;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				if (newCourse_max < 10 || cin.bad() || newCourse_max != (int)newCourse_max){
					cout << "Invalid input.Try again!\n";
				}
			} while (cin.bad() || newCourse_max < 10 || newCourse_max != (int)newCourse_max);

			do{
				cout << "Input course's credit number (1-6): "; cin >> newCourse_ncredit;
				cin.clear();
				cin.ignore(INT_MAX, '\n');

				if (!cin.good() || newCourse_ncredit<1 || newCourse_ncredit>6 || newCourse_ncredit != (int)newCourse_ncredit){
					cout << "Invalid input.Try again!\n";
				}
			} while (cin.bad() || newCourse_ncredit < 1 || newCourse_ncredit>6 || newCourse_ncredit != (int)newCourse_ncredit);

			Course newCourse(newCourse_sub_id, newCourse_name, tc.tc_name, tc.tc_identify);
			newCourse.course_id = newCourse_id;
			newCourse.total_st = 0;
			newCourse.max_st = newCourse_max;
			newCourse.credit = newCourse_ncredit;
			cout << "NEW COURSE PREVIEW: \n";
			newCourse.printCourseInfo();
			char ans;
			cout << "Are you sure to open this course? [Y/N] :";
			do{
				cin >> ans;
				if (ans != 'Y' && ans != 'N'){
					cout << "Retype: ";
				}
				cin.ignore(INT_MAX, '\n');
			} while (ans != 'Y' && ans != 'N');
			if (ans == 'Y'){
				cout << "SUCESSFULLY OPEN A NEW COURSE \n";
				//cout << "Date created: " << endl;
				//std::time_t t = std::time(0);   // get time now
				//std::tm* now = std::localtime(&t);
				//std::cout << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday << "\n";
				cin.ignore(INT_MAX, '\n');
				db_course_list.addToCourseList(newCourse);
				return true;
			}
			else{

				return true;
			}


		}//else right
	}
	bool openCourse(CourseList& db_courseList, Course newCourse); //mo mot khoa hoc
	bool gradingCourse(StudentCourseList& st_join_course); //tong ket diem va sua diem

	void showTeacherCouser(CourseList tc_course,StudentCourseList st_course);//Xuat thong tin nhung khoa hoc ma teacher da mo
	Teacher& operator=(User u){
		this->username = u.username;
		this->password = u.password;
		this->role = u.role;
		return *this;
	}
};

//-------------------------LECTURERS LIST-------------------------

class TeacherList :public arrayList<Teacher>{
public:
	TeacherList(){};
	~TeacherList(){};

	TeacherList findTeacherByNameKeyword(string keyword[], size_t n);
	bool getTeacherInfo(Teacher& st);
	void removeTeacherByNameKeyword(string keyword[], size_t n);
	void updateTeacherList(Teacher data);
	void print();
};


#endif