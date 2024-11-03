#include <raylib.h>

#define MAX_INPUT_CHARS 48


int main() {

	const int screenWidth = 680;
	const int screenHeight = 700;

	InitWindow(screenWidth, screenHeight, "Todo List");
	char inputText[MAX_INPUT_CHARS + 1] = "\0";
	int letterCount = 0;

	Rectangle textBox = { 10, 10, screenWidth - 150, 58 };
	bool mouseOnText = false;

	int framesCounter = 0;

	SetTargetFPS(60);


	while (!WindowShouldClose()) {
	

		if (CheckCollisionPointRec(GetMousePosition(), textBox)) {
			mouseOnText = true;
		}
		else {
			mouseOnText = false;
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
		if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
		else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

		DrawText(inputText, (int)textBox.x + 5,(int)textBox.y + 8, 40, MAROON);
		
		//DrawText(TextFormat("Input char: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);

		if (mouseOnText) {
			if (letterCount < MAX_INPUT_CHARS) {
				if ((framesCounter / 20) % 2 == 0) {
					DrawText("|", (int)textBox.x + 8 + MeasureText(inputText, 40), (int)textBox.y + 12, 40, MAROON);
				}
			}
			else {
				DrawText("You have exceeded the number of authorized chars..", 10, 78, 20, GRAY);
			}
		}
		EndDrawing();
	}

	CloseWindow();

	return 0;
}