#include "Task.h"

Task::Task(int taskID, Rectangle textBox, char inputText) {
	frame = { 10, 80.0f + taskID * 10, textBox.width, textBox.height };
	this->taskID;
	this->inputText;
	this->textBox;
}
void Task::Draw()
{
	DrawRectangle(10, 80, textBox.width, textBox.height + 50, LIGHTGRAY);
	DrawText(inputText, frame.x, frame.y + 10, 20, BLACK);
}


