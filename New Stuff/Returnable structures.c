// Yes...structures can even return stuff


// Returning a Structure by Value
#include <stdio.h>

// Define a structure
struct Point {
    int x;
    int y;
};

// Function that returns a structure
struct Point getPoint() {
    struct Point p;
    p.x = 10;
    p.y = 20;
    return p;  // Returns the whole structure
}

int m() {
    struct Point p1 = getPoint();  // Receive the returned struct
    printf("Point: (%d, %d)\n", p1.x, p1.y);
    return 0;
}







// 2.Returning a Structure by Pointer
#include <stdio.h>

// Define a structure
struct Rectangle {
    int width;
    int height;
};

// Function that returns a pointer to a structure
struct Rectangle* createRectangle() {
    static struct Rectangle r;  // Static to persist after function returns
    r.width = 30;
    r.height = 40;
    return &r;  // Return address of the struct
}

int m() {
    struct Rectangle* rect = createRectangle();
    printf("Rectangle: Width = %d, Height = %d\n", rect->width, rect->height);
    return 0;
}







// 3. Returning a Structure by Dynamic Memory Allocation

#include <stdio.h>
#include <stdlib.h>

struct Circle {
    float radius;
};

// Function that dynamically allocates memory for a structure
struct Circle* createCircle(float r) {
    struct Circle* c = (struct Circle*)malloc(sizeof(struct Circle));
    if (c != NULL) {
        c->radius = r;
    }
    return c;
}

int m() {
    struct Circle* c1 = createCircle(5.5);
    if (c1 != NULL) {
        printf("Circle Radius: %.2f\n", c1->radius);
        free(c1);  // Free allocated memory
    }
    return 0;
}

// Which Method Should You Use?
// For small structures: Returning by value is fine.
// For large structures: Use pointers to avoid unnecessary copying.
// For dynamic structures: Use malloc() but remember to free it.


// Note:
// If functions already exist, why do we need structures at all? 

// 1.The main reason is that functions return only a single value, 
// but structures allow us to group multiple related values and return them together.

// 2. Structures Improve Code Readability & Organization

// 3. Structures Work Well With Arrays & Complex Data
// struct Student students[3];  // Array of structures


// Conclusion
// ✅ Use functions for calculations & logic.
// ✅ Use structures when you need to return multiple values, group related data, or organize code better.



