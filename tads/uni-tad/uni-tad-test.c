#include "uni-tad.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int course_cmp(struct course course1, struct course course2) {
    return course1.id - course2.id;
}

int student_cmp(struct student student1, struct student student2) {
    return student1.id - student2.id;
}

int main() {
    university_configuration conf = {
        .max_courses = 3,
        .course_comparator = course_cmp,
        .max_students_per_course = 5,
        .student_comparator = student_cmp
    };
    universityADT uni = university_create(&conf);

    student student1 = {.id = 1};
    student student2 = {.id = 2};
    student student3 = {.id = 3};
    student student4 = {.id = 4};
    student student5 = {.id = 5};
    student student6 = {.id = 6};

    student students_expected_1[] = {
        student1,
        student2,
        student3,
        student4,
        student5,
        student6,
    };

    student * students_expected = students_expected_1;

    assert(university_student_count(uni) == 0);
    assert(university_students(uni) == NULL);

    student * students;
    for (int i = 0; i < 6;) {
        student aux = {.id = i+1};
        assert(university_add_or_update_student(uni, aux) == true);
        i++;
        assert(i == university_student_count(uni));
        students = university_students(uni);
        for (int j = 0; j < i; j++) {
            assert(student_cmp(students_expected[j], students[j]) == 0);
        }
        free(students);
    }

    assert(university_student_count(uni) == 6);
    assert(university_add_or_update_student(uni, student6) == true);
    assert(university_student_count(uni) == 6);

    course course1 = {.id = 1};
    course course2 = {.id = 2};
    course course3 = {.id = 3};
    course course4 = {.id = 4};

    assert(university_add_course(uni, course1) == true);
    assert(university_add_course(uni, course2) == true);
    assert(university_add_course(uni, course3) == true);
    assert(university_add_course(uni, course4) == false);
    assert(university_course_student_count(uni, course1) == 0);
    assert(university_course_student_count(uni, course2) == 0);
    assert(university_course_student_count(uni, course4) == 0);

    assert(university_course_student_count(uni, course1) == 0);
    assert(university_course_add_student(uni, course1, student1) == true);
    assert(university_course_student_count(uni, course1) == 1);
    assert(university_course_add_student(uni, course1, student3) == true);
    assert(university_course_student_count(uni, course1) == 2);
    assert(university_course_add_student(uni, course1, student5) == true);
    assert(university_course_student_count(uni, course1) == 3);

    assert(university_course_student_count(uni, course2) == 0);
    assert(university_course_add_student(uni, course2, student2) == true);
    assert(university_course_student_count(uni, course2) == 1);
    assert(university_course_add_student(uni, course2, student4) == true);
    assert(university_course_student_count(uni, course2) == 2);
    assert(university_course_add_student(uni, course2, student6) == true);
    assert(university_course_student_count(uni, course2) == 3);

    assert(university_course_student_count(uni, course3) == 0);
    assert(university_course_add_student(uni, course3, student1) == true);
    assert(university_course_student_count(uni, course3) == 1);
    assert(university_course_add_student(uni, course3, student2) == true);
    assert(university_course_student_count(uni, course3) == 2);
    assert(university_course_add_student(uni, course3, student3) == true);
    assert(university_course_student_count(uni, course3) == 3);
    assert(university_course_add_student(uni, course3, student4) == true);
    assert(university_course_student_count(uni, course3) == 4);
    assert(university_course_add_student(uni, course3, student5) == true);
    assert(university_course_student_count(uni, course3) == 5);
    assert(university_course_add_student(uni, course3, student6) == false);
    assert(university_course_student_count(uni, course3) == 5);

    student student7 = {.id = 7};
    assert(university_course_student_count(uni, course4) == 0);
    assert(university_course_add_student(uni, course4, student6) == false);
    assert(university_course_student_count(uni, course4) == 0);
    assert(university_course_add_student(uni, course4, student7) == false);
    assert(university_course_student_count(uni, course4) == 0);

    int student_count = university_course_student_count(uni, course1);
    assert(student_count == 3);
    students = university_course_students(uni, course1);
    for (int i = 0; i < student_count; i++) {
        assert(student_cmp(students_expected[i*2], students[i]) == 0);
    }
    free(students);

    student_count = university_course_student_count(uni, course2);
    assert(student_count == 3);
    students = university_course_students(uni, course2);
    for (int i = 0; i < student_count; i++) {
        assert(student_cmp(students_expected[i*2 + 1], students[i]) == 0);
    }
    free(students);

    student_count = university_course_student_count(uni, course3);
    assert(student_count == 5);
    students = university_course_students(uni, course3);
    for (int i = 0; i < student_count; i++) {
        assert(student_cmp(students_expected[i], students[i]) == 0);
    }
    free(students);

    assert(university_course_students(uni, course4) == NULL);

    student students_expected_2[] = {
        student1,
        student2,
        student5,
        student6,
    };

    students_expected = students_expected_2;

    assert(university_course_remove_student(uni, course1, student3) == true);
    assert(university_course_remove_student(uni, course2, student4) == true);

    student_count = university_course_student_count(uni, course1);
    assert(student_count == 2);
    students = university_course_students(uni, course1);
    for (int i = 0; i < student_count; i++) {
        assert(student_cmp(students_expected[i*2], students[i]) == 0);
    }
    free(students);

    student_count = university_course_student_count(uni, course2);
    assert(student_count == 2);
    students = university_course_students(uni, course2);
    for (int i = 0; i < student_count; i++) {
        assert(student_cmp(students_expected[i*2 + 1], students[i]) == 0);
    }
    free(students);

    assert(university_course_remove_student(uni, course3, student3) == true);
    assert(university_course_remove_student(uni, course3, student3) == false);
    assert(university_course_remove_student(uni, course3, student4) == true);
    assert(university_course_remove_student(uni, course3, student4) == false);
    assert(university_course_remove_student(uni, course3, student6) == false);
    assert(university_course_add_student(uni, course3, student6) == true);
    assert(university_course_add_student(uni, course3, student6) == false);
    assert(university_course_add_student(uni, course3, student7) == false);

    student_count = university_course_student_count(uni, course3);
    assert(student_count == 4);
    students = university_course_students(uni, course3);
    for (int i = 0; i < student_count; i++) {
        assert(student_cmp(students_expected[i], students[i]) == 0);
    }
    free(students);

    assert(university_course_remove_student(uni, course4, student3) == false);

    university_free(uni);
    return 0;
}
