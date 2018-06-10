#ifndef _COURSE_
#define _COURSE_

#include<string>
#include "Helper.h"
using namespace std;

struct Course{
	string course_id;
	string sub_id;
	string fal_id;
	string falcuty;
	string sub_name;
	int total_st;
	int max_st;
	int credit;

	Course() {};
	Course(string sub_id, string sub_name, string falcuty, string fal_id) {
		this->sub_id = sub_id;
		this->sub_name = sub_name;
		this->falcuty = falcuty;
		this->fal_id = fal_id;
	};
	~Course() {};

	void isCourseFull() {
		if (total_st > max_st) {
			this->max_st++;
		}
	}
	void CreateNewCourse(string sub_id, string sub_name, string falcuty, string fal_id, int total_st, int max_st, int credit){
		this->sub_id = sub_id;
		this->sub_name = sub_name;
		this->falcuty = falcuty;
		this->fal_id = fal_id;
		this->total_st = total_st;
		this->max_st = max_st;
		this->credit = credit;
	}
	void printCourseInfo(); // dung de ghi ra thong tin mot course ma teacher vua mo
};

//----------------------THIS IS FOR COURSE LIST--------------------
class CourseList : public arrayList<Course> {
public:
	CourseList() {};
	~CourseList() {};

	Course* findCourseById(string id);
	CourseList* findCourseByName(string name);
	CourseList* findAllCourseById(arrayList<string> id_list);
	CourseList* findAllCourseByName(arrayList<string> name_list);
	CourseList* findCourseByFacuty(string fal);
	CourseList* findAllCourseByFalcuty(arrayList<string> fal_list);
	CourseList* findCourseByFacutyId(string fal_id);
	CourseList* findAllCourseByFalcutyId(arrayList<string> falid_list);
	bool isCourseExist(string,Course&);
	bool addToCourseList(Course newCourse); // add a opened course to courseList ( course.csv )
	void addStudentToCourse(string course_id);
	void removeStudentToCourse(string course_id);
	void printCourse();
};
#endif // !_COURSE_

