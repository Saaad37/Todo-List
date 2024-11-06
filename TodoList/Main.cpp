#include <list>
#include "raylib.h"

using namespace std;

#define MAX_INPUT_CHARS 48

Rectangle textBox;
char inputText[MAX_INPUT_CHARS + 1] = "\0";
char displayText[MAX_INPUT_CHARS + 1] = "\0";
bool mouseOnButton = false;
list<int> tasks; 
int letterCount;
int framesCounter;

bool searchFor(long taskID) {
	for (int i : tasks) {
		if (i == taskID) return true;
	}
	return false;
}

void resetInputText() {
	if (letterCount > 0) {
		for (int i = 0; i < MAX_INPUT_CHARS + 1; i++){
			if (inputText[i] != '\0') {
				inputText[i] = '\0';
				displayText[i] = '\0';
			}
			else i++;
		}
		letterCount = 0;
		framesCounter = 0;
	}
}


class Task {
public:
	bool Completed = false;
	bool DoCreate = true;
	long taskID = 0;
	char taskText[MAX_INPUT_CHARS];

	Task(int taskID) {
		frame = { 10, 100.0f + taskID * 10, textBox.width, textBox.height };
		this->taskID;
	}

	void CreateText() {
			while (DoCreate) {
				for (int i = 0;i < MAX_INPUT_CHARS;i++) {
					taskText[i] = inputText[i];
				}
				DoCreate = false;
			}
	}


	void Draw()
	{
		DrawRectangleRec(frame, LIGHTGRAY);
		DrawText(taskText, frame.x + 10, frame.y + 10, 20, BLACK);
		resetInputText();
	}
private:
	Rectangle frame;
};



int main() {

	const int screenWidth = 680;
	const int screenHeight = 700;

	InitWindow(screenWidth, screenHeight, "Todo List");
	
	letterCount = 0;
	framesCounter = 0;

	textBox = { 10, 10, screenWidth - 150, 58 }; //width = 440
	Rectangle submitTaskButton = { screenWidth - 120, 10, 105, 58 };
	bool mouseOnText = false;

	Task task1 = Task(0);
	Task task2 = Task(1);
	Task task3 = Task(2);
	Task task4 = Task(3);


	long numClicksSubmit = 0;
	

	SetTargetFPS(60);

	while (!WindowShouldClose()) {

		if (CheckCollisionPointRec(GetMousePosition(), textBox)) {
			mouseOnText = true;
		}
		else {
			mouseOnText = false;
		}

		if (CheckCollisionPointRec(GetMousePosition(), submitTaskButton)) {
			mouseOnButton = true;
		}
		else {
			mouseOnButton = false;
		}


		if (mouseOnText) {
			
			SetMouseCursor(MOUSE_CURSOR_IBEAM);
			int key = GetCharPressed();

			while (key > 0) {
				if (key > 31 && key < 125 && letterCount < MAX_INPUT_CHARS) {
					inputText[letterCount] = (char)key;
					inputText[letterCount + 1] = '\0';
					letterCount++;
				}
				key = GetCharPressed();
			}
			if (IsKeyPressed(KEY_BACKSPACE)) {
				letterCount--;
				if (letterCount < 0) {
					letterCount = 0;
				}
				inputText[letterCount] = '\0';
			}
		}
		else {
			SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		}

		if (mouseOnText) framesCounter++;
		else framesCounter = 0;

		if (mouseOnButton && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && inputText[0] != '\0') numClicksSubmit++;
		if (numClicksSubmit < 0 || numClicksSubmit > 4) numClicksSubmit = 0;
		
		BeginDrawing();
		
		ClearBackground(RAYWHITE);

		DrawRectangleRec(textBox, LIGHTGRAY);

		if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, MAROON);
		else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

		if (MeasureText(inputText, 40) > textBox.width - 20 && letterCount >= 20) {
			for (int i = 0; i < letterCount;i++) {
				displayText[i] = inputText[letterCount - 21 + i];
			}
			DrawText(displayText, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON); // Display last 23 chars
		}
		else {
			DrawText(inputText, (int)textBox.x + 5,(int)textBox.y + 8, 40, MAROON);	
		}
		
		//DrawText(TextFormat("Input char: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);

		if (mouseOnText) {
			if (letterCount < MAX_INPUT_CHARS) {
				if ((framesCounter / 20) % 2 == 0) {
					if (MeasureText(inputText, 40) > textBox.width - 10) {
						DrawText("|", (int)textBox.x + 8 + MeasureText(displayText, 40), (int)textBox.y + 12, 40, MAROON);
					}
					else {
					DrawText("|", (int)textBox.x + 8 + MeasureText(inputText, 40), (int)textBox.y + 12, 40, MAROON);
					}
				}
			}
			else {
				DrawText("You have exceeded the number of authorized chars..", 10, 78, 20, GRAY);
			}
		}
		
		DrawRectangleRec(submitTaskButton, DARKGRAY);
		DrawText("Submit Task", submitTaskButton.x + submitTaskButton.width/2 - 31, submitTaskButton.height / 2 + 5, 10, BLACK);

		if (mouseOnButton) {
			DrawRectangleLines((int)submitTaskButton.x, (int)submitTaskButton.y, (int)submitTaskButton.width, (int)submitTaskButton.height, BLACK);
			DrawRectangle((int)submitTaskButton.x, (int)submitTaskButton.y, (int)submitTaskButton.width, (int)submitTaskButton.height, WHITE);
			DrawText("Submit Task", submitTaskButton.x + submitTaskButton.width / 2 - 31, submitTaskButton.height / 2 + 5, 10, BLACK);
			SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
		}
		else {
			DrawRectangleRec(submitTaskButton, DARKGRAY);
			DrawText("Submit Task", submitTaskButton.x + submitTaskButton.width / 2 - 31, submitTaskButton.height / 2 + 5, 10, BLACK);
			SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		}

		switch (numClicksSubmit) {
		case 0:
			DrawText("No Tasks to display", 150, screenHeight / 2, 40, MAROON);
			break;
		case 1:
			task1.CreateText();
			task1.Draw();
			if(searchFor(task1.taskID)) break;
			else tasks.push_back(task1.taskID);
			break;
		case 2:
			task2.CreateText();
			task2.Draw();
			if (searchFor(task2.taskID)) break;
			else tasks.push_back(task2.taskID);
			break;
		case 3:
			task3.CreateText();
			task3.Draw();
			if (searchFor(task3.taskID)) break;
			else tasks.push_back(task3.taskID);
			break;
		case 4:
			task4.CreateText();
			task4.Draw();
			if (searchFor(task4.taskID)) break;
			else tasks.push_back(task4.taskID);
			break;
		default:
			break;
		}	
		EndDrawing();
	}

	CloseWindow();

	return 0;
}