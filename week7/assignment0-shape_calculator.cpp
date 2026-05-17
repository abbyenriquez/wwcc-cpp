#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class Rectangle {
private:
    double length;
    double width;

public:
    Rectangle(double l, double w) {
        length = (l > 0) ? l : 1;
        width = (w > 0) ? w : 1;
    }

    double getLength() const {
        return length;
    }

    double getWidth() const {
        return width;
    }

    void setLength(double l) {
        if (l > 0)
            length = l;
    }

    void setWidth(double w) {
        if (w > 0)
            width = w;
    }

    double area() const {
        return length * width;
    }

    void area(double &result) const {
        result = length * width;
    }

    Rectangle& resize(double factor) {
        this->length *= factor;
        this->width *= factor;
        return *this;
    }
};

class Circle {
private:
    double radius;

public:
    Circle(double r) {
        radius = (r > 0) ? r : 1;
    }

    void setRadius(double r) {
        if (r > 0)
            radius = r;
    }

    double area() const {
        return 3.14159 * radius * radius;
    }

    double circumference() const {
        return 2 * 3.14159 * radius;
    }

    void print() const {
        cout << "Circle Radius: " << radius << endl;
    }

    void print(bool detailed) const {
        if (detailed) {
            cout << "Radius: " << radius << endl;
            cout << "Area: " << area() << endl;
            cout << "Circumference: " << circumference() << endl;
        } else {
            print();
        }
    }
};

int main() {
    cout << fixed << setprecision(2);

    Rectangle rect(5, 3);

    cout << "Rectangle Area: " << rect.area() << endl;

    double result;
    rect.area(result);

    cout << "Area via reference: " << result << endl;

    rect.resize(2.0);

    cout << "After resize:\n";
    cout << "Length: " << rect.getLength() << endl;
    cout << "Width: " << rect.getWidth() << endl;

    cout << endl;

    Circle circle(4);

    circle.print();

    cout << "Area: " << circle.area() << endl;
    cout << "Circumference: " << circle.circumference() << endl;

    cout << endl;

    circle.print(true);

    cout << endl;

    const Circle constCircle(2);

    cout << "Const circle area: "
         << constCircle.area() << endl;

    return 0;
}