#pragma once
#include <raylib.h>

class Task {
public:
	Task(int taskID, Rectangle textBox, char inputText);
	Rectangle textBox;
	char inputText;
	int taskID = 0;
	void Draw();
private:
	Rectangle frame;
};