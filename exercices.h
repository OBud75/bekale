#include <iostream>
#include <cstring>

typedef struct Person {
    int age;
} Person;

int are_persons_equals(Person *p1, Person *p2) {
    return p1->age == p2->age;
}

typedef struct Book {
    int pages;
} Book;

int are_books_equals(Book *b1, Book *b2) {
    return b1->pages == b2->pages;
}

int are_equals(void *obj1, void *obj2, int (*compare_fnc)(void *, void *)) {
    return compare_fnc(obj1, obj2);
}

int is_greater(void *obj1, void *obj2, int (*compare_fnc)(void *, void *)) {
    return compare_fnc(obj1, obj2) > 0;
}

void swap(void *obj1, void *obj2, size_t size) {
    void *temp = malloc(size);
    memcpy(temp, obj1, size);
    memcpy(obj1, obj2, size);
    memcpy(obj2, temp, size);
    free(temp);
}

void sort(void *array, int nb_of_elems_in_array, size_t elem_size, int (*compare_fnc)(void *, void *)) {
    for (int i = 0; i < nb_of_elems_in_array - 1; i++) {
        for (int j = 0; j < nb_of_elems_in_array - i - 1; j++) {
            void *elem1 = (char *)array + j * elem_size;
            void *elem2 = (char *)array + (j + 1) * elem_size;
            if (compare_fnc(elem1, elem2) > 0) {
                swap(elem1, elem2, elem_size);
            }
        }
    }
}

int is_in_array(void *obj_to_find, void *array, int nb_of_elems_in_array, size_t elem_size, int (*compare_fnc)(void *, void *)) {
    for (int i = 0; i < nb_of_elems_in_array; i++) {
        void *elem = (char *)array + i * elem_size;
        if (compare_fnc(obj_to_find, elem) == 1) {
            return 1;
        }
    }
    return 0;
}

int main() {
    Person person1 = {50};
    Person person2 = {50};
    Person people[] = {{20}, {50}};
    Book book1 = {100};
    Book books[] = {{50}, {100}};

    std::cout << "Are persons equal: " << are_equals(&person1, &person2, (int (*)(void *, void *))are_persons_equals) << std::endl;
    std::cout << "Is person1 in array: " << is_in_array(&person1, people, 2, sizeof(Person), (int (*)(void *, void *))are_persons_equals) << std::endl;
    std::cout << "Is book1 in array: " << is_in_array(&book1, books, 2, sizeof(Book), (int (*)(void *, void *))are_books_equals) << std::endl;

    return 0;
}
