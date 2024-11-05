#include <graphics.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

class Point {
public:
    int x, y;
};

class Polygon {
private:
    Point p[20]; // Array to store vertices
    int inter[20], c; // Array for intersections
    int v, xmin, ymin, xmax, ymax;

public:
    void read();
    void calculateBounds();
    void display();
    void findIntersections(float z);
    void sortIntersections(int z);
};

void Polygon::read() {
    cout << "\nScan Fill Algorithm ";
    cout << "\nEnter Number Of Vertices Of Polygon: ";
    cin >> v;
    if (v > 2) {
        for (int i = 0; i < v; i++) { // Accept the vertices
            cout << "\nEnter coordinate no. " << i + 1 << ": ";
            cout << "\n\tx" << (i + 1) << " = ";
            cin >> p[i].x;
            cout << "\n\ty" << (i + 1) << " = ";
            cin >> p[i].y;
        }
        p[v] = p[0]; // Closing the polygon
        xmin = xmax = p[0].x;
        ymin = ymax = p[0].y;
    } else {
        cout << "\nEnter valid number of vertices.";
    }
}

void Polygon::calculateBounds() {
    for (int i = 0; i < v; i++) {
        if (xmin > p[i].x) xmin = p[i].x;
        if (xmax < p[i].x) xmax = p[i].x;
        if (ymin > p[i].y) ymin = p[i].y;
        if (ymax < p[i].y) ymax = p[i].y;
    }
}

void Polygon::display() {
    int choice;
    char cont = 'y';
    do {
        cout << "\n\nMENU:";
        cout << "\n\n\t1. Scan line Fill ";
        cout << "\n\n\t2. Exit ";
        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                float s = ymin + 0.01;
                delay(100);
                cleardevice();
                while (s <= ymax) {
                    findIntersections(s);
                    sortIntersections(s);
                    s++;
                }
                break;
            }
            case 2:
                exit(0);
        }
        cout << "Do you want to continue? (y/n): ";
        cin >> cont;
    } while (cont == 'y' || cont == 'Y');
}

void Polygon::findIntersections(float z) {
    int x1, x2, y1, y2, temp;
    c = 0;
    for (int i = 0; i < v; i++) {
        x1 = p[i].x;
        y1 = p[i].y;
        x2 = p[i + 1].x;
        y2 = p[i + 1].y;

        if (y2 < y1) {
            // Swap points if necessary
            temp = x1; x1 = x2; x2 = temp;
            temp = y1; y1 = y2; y2 = temp;
        }

        if (z <= y2 && z >= y1) {
            int x;
            if ((y1 - y2) == 0) {
                x = x1; // Horizontal line
            } else {
                x = ((x2 - x1) * (z - y1)) / (y2 - y1) + x1; // Linear interpolation
            }
            if (x <= xmax && x >= xmin)
                inter[c++] = x; // Store intersection point
        }
    }
}

void Polygon::sortIntersections(int z) {
    for (int i = 0; i < v; i++) {
        line(p[i].x, p[i].y, p[i + 1].x, p[i + 1].y);
    }
    delay(100);
    for (int i = 0; i < c; i += 2) {
        delay(100);
        line(inter[i], z, inter[i + 1], z);
    }
}

int main() {
    int color;

    // Initialize the graphics system
    int gd = DETECT, gm;
    initgraph(&gd, &gm, ""); // Adjust the path to your BGI folder if needed
    cleardevice();

    Polygon polygon;
    polygon.read();
    polygon.calculateBounds();
    cleardevice();

    cout << "\n\tEnter The Color You Want (In Range 0 To 15): ";
    cin >> color;
    setcolor(color);
    polygon.display();

    closegraph(); // Close graphics
    return 0;
}

