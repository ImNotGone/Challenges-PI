#include "uni-tad.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct student_node {

    student student;

    struct student_node * tail;

} student_node;

typedef struct student_node * student_list;

typedef struct course_info {

    course course;

    student ** students;
    unsigned student_count;

} course_info;

typedef struct universityCDT {

    university_configuration * conf;

    course_info * courses;
    unsigned course_count;

    student_list students;
    unsigned student_count;

} universityCDT;

#define MEM_BLOCK 5

// Reserva memoria para una nueva universidad
universityADT university_create(struct university_configuration * conf) {
    if(conf == NULL) {
        return NULL;
    }

    universityADT new_uni = malloc(sizeof(universityCDT));
    university_configuration * new_conf = malloc(sizeof(university_configuration));
    if(new_uni == NULL || new_conf == NULL) {
        free(new_uni);
        free(new_conf);
        return NULL;
    }
    memcpy(new_conf, conf, sizeof(university_configuration));
    new_uni->conf = new_conf;
    new_uni->courses = NULL;
    new_uni->course_count = 0;
    new_uni->students = NULL;
    new_uni->student_count = 0;
    return new_uni;
}

student_list add_student_rec(student_list first, student student, student_comparator_fun comparator, bool * added, bool * updated) {

    int c;

    if(first == NULL || (c = comparator(first->student, student)) > 0) {
        student_list new_node = malloc(sizeof(student_node));
        if(new_node == NULL) {
            *added=false;
            return first;
        }
        new_node->student = student;
        new_node->tail = first;
        *added = true;
        return new_node;
    }

    // es igual (porahi es un update -> piso el q tenia)
    if(c == 0) {
        *updated = true;
        first->student = student;
        return first;
    }

    first->tail = add_student_rec(first->tail, student, comparator, added, updated);
    return first;
}

bool university_add_or_update_student(universityADT uni, struct student student) {
    bool added = false;
    bool updated = false;
    uni->students = add_student_rec(uni->students, student, uni->conf->student_comparator, &added, &updated);
    if(added) {
        uni->student_count++;
    }
    return added || updated;
}

bool university_add_course(universityADT uni, struct course course) {
    if(uni->course_count == uni->conf->max_courses) {
        return false;
    }

    if(uni->course_count % MEM_BLOCK == 0) {
        uni->courses = realloc(uni->courses, sizeof(course_info)*(uni->course_count + MEM_BLOCK));
        //TODO: check error?
    }


    uni->courses[uni->course_count].course = course;
    uni->courses[uni->course_count].students = NULL;
    uni->courses[uni->course_count].student_count = 0;
    uni->course_count++;
    return true;
}


static student_list find_student_rec(student_list first, student student, student_comparator_fun comparator) {
    int c;

    if(first == NULL || (c = comparator(first->student, student)) > 0) {
        return NULL;
    }

    if(c == 0) {
        return first;
    }

    return find_student_rec(first->tail, student, comparator);
}

static course_info * find_course(universityADT uni, course course) {
    for(unsigned i = 0; i < uni->course_count; i++) {
        if(uni->conf->course_comparator(uni->courses[i].course, course) == 0) {
            return &uni->courses[i];
        }
    }
    return NULL;
}

bool university_course_add_student(universityADT uni, struct course course, struct student student) {
    course_info * course_aux = find_course(uni, course);

    if(course_aux == NULL || uni->conf->max_students_per_course == course_aux->student_count) {
        return false;
    }

    student_list student_aux = find_student_rec(uni->students, student, uni->conf->student_comparator);
    if(student_aux == NULL) {
        return false;
    }

    for(int i = 0; i < course_aux->student_count; i++) {
        if(&student_aux->student == course_aux->students[i]) {
            return false;
        }
    }

    if(course_aux->student_count % MEM_BLOCK == 0) {
        course_aux->students = realloc(course_aux->students, sizeof(struct student *) * (course_aux->student_count + MEM_BLOCK));
    }

    course_aux->students[course_aux->student_count++] = &student_aux->student;

    return true;

}

bool university_course_remove_student(universityADT uni, struct course course, struct student student) {
    course_info * course_aux = find_course(uni, course);

    if(course_aux == NULL) {
        return false;
    }

    bool found = false;
    int i;
    for (i = 0; i < course_aux->student_count && !found; i++) {
        found = uni->conf->student_comparator(*course_aux->students[i], student) == 0;
        if (found) {
            for (int j = i; j < course_aux->student_count - 1; j++) {
            course_aux->students[j] = course_aux->students[j+1];
            }
            course_aux->student_count--;
        }
    }

    return found;
}

struct student * university_course_students(universityADT uni, struct course course) {
    course_info * course_aux = find_course(uni, course);

    if (course_aux == NULL) {
        return NULL;
    }

    student * students = malloc(sizeof(struct student) * course_aux->student_count);

    for (int i = 0; i < course_aux->student_count; i++) {
        students[i] = *course_aux->students[i];
    }
    return students;
}

struct student * university_students(universityADT uni) {
    if(uni->student_count == 0) return NULL;
    student_list aux = uni->students;
    student * students = malloc(sizeof(struct student) * uni->student_count);
    for(int i = 0; aux != NULL; i++, aux = aux->tail) {
        students[i] = aux->student;
    }
    return students;
}

unsigned university_student_count(universityADT uni) {
    return uni->student_count;
}

unsigned university_course_student_count(universityADT uni, struct course course) {
    course_info * course_aux = find_course(uni, course);
    if(course_aux == NULL) {
        return 0;
    }
    return course_aux->student_count;
}

static void freeList(student_list first) {
    if(first == NULL) return;
    freeList(first->tail);
    free(first);
}

void university_free(universityADT uni) {

    freeList(uni->students);

    for (int i = 0; i < uni->course_count; i++) {
        free(uni->courses[i].students);
    }
    free(uni->courses);
    free(uni->conf);
    free(uni);
}

