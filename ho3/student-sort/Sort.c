#include <string.h>

#include "Sort.h"
#include "Person.h"

void swapPersons(Person *obj1, Person *obj2);

void sortByName(Person *a, int n) {
	for (int i = 1; i < n; i++) {
		for (int j = n - 1; j >= i; j--) {
			if (strcmp(a[j].name, a[j - 1].name) < 0) {
				swapPersons(&a[j], &a[j-1]);
			}
		}
	}
}

void sortByAge(Person *a, int n) {
	// Complete function definition
	// similar to sortByName()
	// ...
	for (int i = 1; i < n; i++) {
		for (int j = n - 1; j >= i; j--) {
			if (a[j].age < a[j-1].age) {
				swapPersons(&a[j], &a[j-1]);
			}
		}
	}
}

void swapPersons(Person *obj1, Person *obj2) {
	Person temp;

	strcpy(temp.name, obj1->name);
	strcpy(temp.id, obj1->id);
	temp.birthDate = obj1->birthDate;
	temp.age = obj1->age;

	strcpy(obj1->name, obj2->name);
	strcpy(obj1->id, obj2->id);
	obj1->birthDate = obj2->birthDate;
	obj1->age = obj2->age;

	strcpy(obj2->name, temp.name);
	strcpy(obj2->id, temp.id);
	obj2->birthDate= temp.birthDate;
	obj2->age=temp.age;
}