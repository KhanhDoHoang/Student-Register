/*
 ============================================================================
 Name        : Assignment1.c
 Author      : Peter Mitchell
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

int getStudentId(char *string) {
    int x = 0;
    do{
        printf(string);
        scanf("%d", &x);
        if (x < 10000 || x > 99999) {
        	printf("Invalid student id. Please enter a 5 digit integer\n");
        }
    } while(x < 10000 || x > 99999);
    return x;
}

char* getCourseId(char *string) {
	char *courseToAdd = malloc(sizeof(char)*50);
	if (courseToAdd == NULL) {
		printf("Error! could not find space for malloc!\n");
		return NULL;
	}
	while (1) {
		printf(string);
		scanf("%s", courseToAdd);

		if (strlen(courseToAdd) == 7) {
			courseToAdd = realloc(courseToAdd, sizeof(char)*8);
			return courseToAdd;
		}

		printf("Invalid course id. Please enter a 7 digit alpha-numeric id\n");
	}
}

int main(void) {
	//https://wiki.eclipse.org/CDT/User/FAQ#Eclipse_console_does_not_show_output_on_Windows
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	printf("Welcome to the Student Register System (SRS)\n\n");

	// number of students
	printf("How many students would you like to register: ");
	int numberOfStudents;
	scanf("%d", &numberOfStudents);

	// getting initial student ids
	int studentIds[numberOfStudents];
	for (int i = 0; i < numberOfStudents; i++) {
		char tempStr[75];
		sprintf(tempStr, "Please enter the student ID for student %d: ",(i+1));

		int noDupes = 1;
		while (noDupes) {
			studentIds[i] = getStudentId(tempStr);

			noDupes = 0;
			for(int j = 0; j < i; j++){
				if (studentIds[i] == studentIds[j]){
					noDupes = 1;
					break;
				}
			}

			// error message if it didn't work
			if (noDupes == 1) {
				printf("Error: student ID %d already entered. Try again.\n", studentIds[i]);
			} else {
				break;
			}
		}
	}
	printIntArray(studentIds,numberOfStudents);


	// number of students
	printf("How many courses are you offering: ");
	int numberOfCourses = 0;
	scanf("%d", &numberOfCourses);

	// getting initial course ids
	char *courseIds[numberOfCourses];
	for (int i = 0; i < numberOfCourses; i++) {
		//loop until there are no duplicates
		char tempStr[60]; // defined out here so it doesn't need to be redefined in the while loop
		sprintf(tempStr, "Please enter the course code for course %d: ",(i+1));

		int noDupes = 1;
		while (noDupes) {

			//get course id from the user
			char *courseToAdd = getCourseId(tempStr);

			noDupes = 0;
			for (int j = 0; j < i; j++) {
				if (strcmp(courseToAdd, courseIds[j]) == 0) {
					noDupes = 1;
					break;
				}
			}

			// error message if it didn't work
			if (noDupes == 1) {
				printf("Error: course ID %s already entered. Try again.\n", courseToAdd);
				free(courseToAdd);
			} else {
				courseIds[i] = courseToAdd;
				break;
			}
		}
	}
	printStringArray(courseIds,numberOfCourses);

	int studentCourses[numberOfStudents][numberOfCourses];
	// the example in the assignment appears to show unset as -1
	initilaize2DArray(*studentCourses, numberOfStudents, numberOfCourses);

	// main loop
	unsigned char done = 1; //char because its smaller
	while (done) {
		int selection;
		printf("Please choose one of the following actions: \n1- Register a student in a course\n2- Drop a student's course\n3- Print registration table\n4- Quit\n");
		printf("Please enter action number: ");
		scanf("%d", &selection);

		if (selection == 1 || selection == 2) {
			//register      //drop

			// -- student id --
			int studentNumIndex = -1;
			while (studentNumIndex == -1) {

				int studentToAdd = getStudentId("Please enter the student id: ");

				//Check if student Id exists
				for(int i = 0; i < numberOfStudents; i++){
					if (studentToAdd == studentIds[i]){
						studentNumIndex = i;
						break;
					}
				}

				// error message if it didn't work
				if (studentNumIndex == -1) {
					printf("Error: student ID %d not found. Try again.\n", studentToAdd);
				}
			}

			// -- course id --

			int courseIdIndex = -1;
			while (courseIdIndex == -1) {

				//get course id from the user
				char *courseToAdd = getCourseId("Please enter the course id: ");

				for(int i = 0; i < numberOfCourses; i++){
					if (strcmp(courseToAdd, courseIds[i]) == 0){
						courseIdIndex = i;
						break;
					}
				}

				// error message if it didn't work
				if (courseIdIndex == -1) {
					printf("Error: course ID %s not found. Try again.\n", courseToAdd);
				}

				free(courseToAdd);
			}




			studentCourses[studentNumIndex][courseIdIndex] = (selection == 1 ? 1 : 0); //If equal to 1 set to 1 if not set to 0


			print2DArray(*studentCourses, numberOfStudents, numberOfCourses);
		} else if (selection == 3) {
			//print registration table
			print2DArray(*studentCourses, numberOfStudents, numberOfCourses);
		} else if (selection == 4) {
			done = 0;
			break;
		} else {
			printf("Error: unknown action: %d",selection);
		}
	}


	for (int i = 0;i < numberOfCourses;i++) {
		free(courseIds[i]);
	}

	return EXIT_SUCCESS;
}
