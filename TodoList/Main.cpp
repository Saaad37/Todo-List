#include "raylib.h"

#define MAX_INPUT_CHARS 48

Rectangle textBox;
char inputText[MAX_INPUT_CHARS + 1] = "\0";


class Task {
public:
	bool Completed = false;
	int TaskID = 0;

	Task(int taskID) {
		frame = { 10, 80.0f + taskID * 10, textBox.width, textBox.height };
		this->TaskID;
	}

	void Draw()
	{
		DrawRectangleRec(frame, LIGHTGRAY);
		DrawText(inputText, frame.x + 10, frame.y + 10, 20, BLACK);
	}
private:
	Rectangle frame;
};



int main() {

	const int screenWidth = 680;
	const int screenHeight = 700;

	InitWindow(screenWidth, screenHeight, "Todo List");
	char displayText[MAX_INPUT_CHARS + 1] ="\0";
	int letterCount = 0;



	textBox = { 10, 10, screenWidth - 150, 58 }; //width = 440
	Rectangle submitTaskButton = { screenWidth - 120, 10, 105, 58 };
	bool mouseOnButton = false;
	bool mouseOnText = false;
	bool showTasks = false;

	Task task = Task(0);

	int framesCounter = 0;

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
		
		BeginDrawing();
		
		ClearBackground(RAYWHITE);

		DrawRectangleRec(textBox, LIGHTGRAY);

		if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, MAROON);
		else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

		if (MeasureText(inputText, 40) > textBox.width && letterCount >= 20) {
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
		if (showTasks) {
			task.Draw();
		}
		else DrawText("No Tasks to display", 150,screenHeight/2, 40, MAROON);
	
		EndDrawing();
	}


	CloseWindow();

	return 0;
}