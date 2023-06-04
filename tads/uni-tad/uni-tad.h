#ifndef UNI_TAD_H
#define UNI_TAD_H
#include <stdbool.h>

typedef struct student {
    unsigned id;
} student;

typedef struct course {
    unsigned id;
} course;


typedef int (*student_comparator_fun)(struct student std1, struct student std2);

typedef int (*course_comparator_fun)(struct course std1, struct course std2);

typedef struct university_configuration {

    unsigned max_courses;

    unsigned max_students_per_course;

    student_comparator_fun student_comparator;

    course_comparator_fun course_comparator;

} university_configuration;


typedef struct universityCDT * universityADT;

// Reserva memoria para una nueva universidad
universityADT university_create(struct university_configuration * conf);

bool university_add_student(universityADT uni, struct student student);

bool university_add_course(universityADT uni, struct course course);

bool university_course_add_student(universityADT uni, struct course course, struct student student);

bool university_course_remove_student(universityADT uni, struct course course, struct student student);

struct student * university_course_students(universityADT uni, struct course course);

struct student * university_students(universityADT uni);

unsigned university_student_count(universityADT uni);

unsigned university_course_student_count(universityADT uni, struct course course);

void university_free(universityADT uni);

#endif
