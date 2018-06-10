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
	bool openNewCourse(Teacher& tc, StudentCourseList& db_st_course_list, CourseList& db_course_list);
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