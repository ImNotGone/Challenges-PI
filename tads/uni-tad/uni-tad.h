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
// si conf == NULL retorna NULL y no reserva memoria
universityADT university_create(struct university_configuration * conf);

// agrega un estudiante o actualiza su informacion si el mismo ya estaba presente
// retorna true, si lo pudo agregar o lo actualizo
bool university_add_or_update_student(universityADT uni, struct student student);

// borra un estudiante de la universidad
// retorna true si lo borro, false sino
bool university_remove_student(universityADT uni, struct student student);

// agrega un curso a la universidad si el maximo de cursos no se alcanzo
// retorna true o false dependiendo si agrego o no el curso
bool university_add_course(universityADT uni, struct course course);

// agrega un alumno a un curso de la universidad
// retorna false si el curso o el alumno no existe, o si el maximo de alumnos se alcanzo
// retorna true si pudo agregar el alumno al curso
bool university_course_add_student(universityADT uni, struct course course, struct student student);

// borra un alumno de un curso
// retorna false si el alumno o el curso no existen
// retorna true si borro el alumno del curso
bool university_course_remove_student(universityADT uni, struct course course, struct student student);

// retorna los alumnos de un curso
// retorna null si no hay alumnos en ese curso
struct student * university_course_students(universityADT uni, struct course course);

// retorna los alumnos de la universidad
// retorna null si no hay alumnos en la universidad
struct student * university_students(universityADT uni);

// retorna la cantidad de alumnos en la universidad
unsigned university_student_count(universityADT uni);

// retorna la cantidad de alumnos por curso en la universidad
unsigned university_course_student_count(universityADT uni, struct course course);

// libera la memoria utilizada por el tad
void university_free(universityADT uni);

#endif
