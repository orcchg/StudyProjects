#include <iostream>
#include <vector>
using std::cout;
using std::vector;

class Figure {
protected:
	int colour; // общее поле для классов-наследников
	
public:
	virtual void draw() const {
		cout << "Cannot draw!\n";
	}
	virtual ~Figure() {
		cout << "~Figure()\n";
	}
};

class Line : public Figure {
protected:
	int x1, x2, y1, y2;
	char* c;

public:
	virtual void draw() const {
		cout << "Line\n";
	}
	~Line() {
		cout << "~Line()\n";
	}
};

class Circle : public Figure {
protected:
	int x, y, r;
	char* c;

public:
	void draw() const {
		cout << "Circle\n";
	}
	~Circle() {
		cout << "~Circle()\n";
	}
};

int main() {
	vector<Figure*> v;
	v.push_back(new Line());
	v.push_back(new Circle());
	v.push_back(new Circle());
	
	for (size_t i = 0; i != v.size(); ++i) {
		v[i]->draw();
	}
	
	for (size_t i = 0; i != v.size(); ++i) {
		delete v[i];
	}
	
	return 0;
}
