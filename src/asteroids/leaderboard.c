void abd(void)
{

}
//#include "leaderboard.h"
//
//Leaders L [MAX_LEADER];
//
//#define BUTTON_WIDTH 200.0f
//#define BUTTON_HEIGHT 50.0f
//Button ExitBtn;
//
//void Asteroids_Init_LeaderBoard(void)
//{
//	Leaderboard.text_color = CP_Color_Create(255, 255, 255, 255);
//	Leaderboard.pos.x = (float)WIN_WIDTH / 2;
//	Leaderboard.pos.y = (float)WIN_HEIGHT / 3;
//	Leaderboard.textsize = 50.0f;
//	Leaderboard.text = "LEADERBOARD: ";
//	Leaderboard.player_score = Score.enemy_kill_score + Score.time_score;
//	Leaderboard.player_name[0] = '\0';
//
//	CP_Vector pos6 = CP_Vector_Set((float)((WIN_WIDTH / 2 - BUTTON_WIDTH / 2)), (float)(WIN_HEIGHT - BUTTON_HEIGHT));
//	ExitBtn = Asteroids_Button_Add_New_Button(BUTTON_WIDTH, BUTTON_HEIGHT);
//	Asteroids_Button_Set_Text(&ExitBtn, 100.0f, "Exit");
//	Asteroids_Button_Set_Position(&ExitBtn, pos6);
//
//	Asteroids_Read_LeaderBoard_Data();
//}
//void Asteroids_Read_LeaderBoard_Data(void)
//{
//	FILE* LeaderboardFile = Asteroids_Open_File("./LeaderBoard.data", "r");
//
//	if (LeaderboardFile == NULL)
//	{
//		//Create file
//		LeaderboardFile = Asteroids_Open_File("./LeaderBoard.data", "w");
//		for (int i = 0; i < MAX_LEADER; i++)
//		{
//			fprintf_s(LeaderboardFile, "nil %d\n", 0);
//		}
//		Asteroids_Close_File(LeaderboardFile);
//	}
//	else
//	{
//		for (int i = 0; i < MAX_LEADER; i++)
//		{
//			int b = fscanf_s(LeaderboardFile, "%s %f", &L[i].name, 20, (float)L[i].score);
//			(void)b;
//			
//		}
//		Asteroids_Close_File(LeaderboardFile);
//	}
//	qsort(&L->score, MAX_LEADER, sizeof(float), Asteroids_Compare_LeaderScore);
//}
//
//int Asteroids_Compare_LeaderScore(const void* first, const void* second)
//{
//	if (*(float*)first > *(float*)second) return 1;
//	if (*(float*)first == *(float*)second) return 0;
//
//	return -1;
//}
//
//bool Asteroids_Check_If_Leader(void)
//{
//	for (int i = 0; i < MAX_LEADER; i++)
//	{
//		if (Leaderboard.player_score > L[i].score)
//		{
//			L[MAX_LEADER - 1].score = Leaderboard.player_score;
//			L[MAX_LEADER - 1].name = Leaderboard.player_name;
//			return true;
//		}
//	}
//	return false;
//}
//
//void Asteroids_Write_LeaderBoard_Data(void)
//{
//	if (Asteroids_Check_If_Leader)
//	{
//		qsort(&L->score, MAX_LEADER, sizeof(float), Asteroids_Compare_LeaderScore);
//
//		FILE* LeaderboardFile = Asteroids_Open_File("Leaderboard.data", "w");
//		for (int i = 0; i < MAX_LEADER; i++)
//		{
//			fprintf_s(LeaderboardFile, "%s %.2f", L[i].name, L[i].score);
//		}
//	}
//}
//
//void Asteroids_Update_LeaderBoard(void)
//{
//	if (Asteroids_Check_If_Leader)
//	{
//
//		Asteroids_LeaderBoard_ReadInput();
//		Asteroids_LeaderBoard_Display_PlayerName();
//	}
//}
//
//void Asteroids_LeaderBoard_ReadInput(void)
//{
//	if (CP_Input_KeyTriggered(KEY_ENTER))
//	{
//		Asteroids_Write_LeaderBoard_Data();
//		return;
//	}
//
//	if (CP_Input_KeyTriggered(KEY_BACKSPACE))
//	{
//		if (counter.name_length > 0)
//		{
//			counter.name_length--;
//			Leaderboard.player_name[counter.name_length] = '\0';
//		}
//	}
//
//	for (int i = KEY_A, j = KEY_0; i <= KEY_Z; i++, j++)
//	{
//		if (counter.name_length >= MAX_INPUT_LEN - 1)
//			return;
//
//		if (CP_Input_KeyTriggered(i))
//		{
//			Leaderboard.player_name[counter.name_length] = (char)i;
//			counter.name_length++;
//		}
//		else if (CP_Input_KeyTriggered(j))
//		{
//			if (j > KEY_9)
//				return;
//
//			Leaderboard.player_name[counter.name_length] = (char)j;
//			counter.name_length++;
//		}
//	}
//}
//void Asteroids_LeaderBoard_Display_PlayerName(void)	// function to display name onto screen
//{
//	if (Leaderboard.player_name)
//		CP_Font_DrawText(Leaderboard.player_name, Leaderboard.pos.x, Leaderboard.pos.y);
//}
//
//void Asteroids_LeaderBoard_Draw(void)
//{
//	CP_Settings_Fill(Leaderboard.text_color);
//	CP_Settings_TextSize(Leaderboard.textsize);
//
//	for (int i = 0; i < MAX_LEADER; i++)
//	{
//		char L_score[16];
//		int whatever = sprintf_s(L_score, 16, "%.2lf", L[i].score);//debug prints
//		(void)whatever;
//
//		CP_Font_DrawText(L[i].name, Leaderboard.pos.x, Leaderboard.pos.y);
//		CP_Font_DrawText(L_score, Leaderboard.pos.x, Leaderboard.pos.y);
//	}
//}
//
//
////#include "leaderboard.h"
////
////extern const int WIN_WIDTH;
////extern const int WIN_HEIGHT;
////
////#define MAX_LINE_INPUT 100
////#define BUFFER_SIZE 20
////#define MAX_LEADERS 3
////
////bool is_leader;
////
////Player player;
////
////Leader LeaderBoard[MAX_LEADERS] = { 0 };
////int LeaderBoard_Scores[MAX_LEADERS];
////
////
////const char leaderboard_file[] = "leaderboard.txt";
////
////Button Button_Exit;
////
////
////void Read_Leaderboard_Data(void)			// Read inputs from leadboard.txt file
////{
////	FILE* leaderboard = leaderboard_file;
////	errno_t error;
////	char buffer[MAX_LINE_INPUT];
////
////	error = fopen_s(&leaderboard, "leaderboard.txt", "r");
////
////
////	if (error != 0)
////	{
////		fopen_s(&leaderboard, "leaderboard.txt", "w");
////
////		if (leaderboard)
////		{
////			for (int i = 0; i < MAX_LEADERS; i++)
////			{
////				fprintf(leaderboard, "%s %d\n", "nil", 0);
////			}
////			fclose(leaderboard);
////		}
////
////		return;
////	}
////
////	else if (error == 0)						// 0 is successful.
////	{
////		if (leaderboard)
////		{
////			while (fgets(buffer, MAX_LINE_INPUT, leaderboard) != NULL)
////			{
////				if (counter.leaders_count < MAX_LEADERS)
////				{
////					int index = counter.leaders_count;
////					int a = sscanf_s(buffer, "%s %d", LeaderBoard[index].name, (unsigned)sizeof buffer, &LeaderBoard[index].score);
////
////					for (int i = 0; i < MAX_LEADERS; i++)
////					{
////						LeaderBoard_Scores[i] = LeaderBoard[i].score;
////					}
////					if (a == 2)
////					{
////						counter.leaders_count++;
////					}
////				}
////				else
////				{
////					break;
////				}
////			}
////			fclose(leaderboard);
////		}
////	}
////}
////
////void Write_Leaderboard_Data(void)			// Writes playername and score into leaderboard.txt
////{
////	FILE* leaderboard = leaderboard_file;
////	errno_t error;
////
////	error = fopen_s(&leaderboard, "leaderboard.txt", "w+");
////	if (is_leader)
////	{
////		strcpy_s(LeaderBoard[MAX_LEADERS - 1].name, BUFFER_SIZE, player.name);
////		LeaderBoard[MAX_LEADERS - 1].score = player.score;
////	}
////
////	if (leaderboard == 0)		//file not found
////	{
////		return;
////	}
////
////	else if (error == 0)		// error = 0 successfully opened
////	{
////		for (int i = 0; i < MAX_LEADERS; i++)
////		{
////			fprintf(leaderboard, "%s %d\n", LeaderBoard[i].name, LeaderBoard[i].score);
////		}
////	}
////
////
////	fclose(leaderboard);
////}
////
////void Check_If_Leader(void)		// Function to check if player is on entitled leaderboard placement
////{
////	for (int i = 0; i < MAX_LEADERS; i++)
////	{
////		if (player.score > LeaderBoard[i].score)
////			is_leader = true;
////	}
////}
////
////void Init_LeaderBoard(void)		// Initialize leaderboard variables
////{
////	Read_Leaderboard_Data();
////
////	is_leader = false;
////	counter.leaders_count = 0;
////	Leaderboard_Variables.text_color = CP_Color_Create(255, 255, 255, 255);
////	Leaderboard_Variables.x = (float)(WIN_WIDTH / 2.0);
////	Leaderboard_Variables.y = (float)(WIN_HEIGHT / 3.5);
////
////	void(*ptr_exit)() = &Load_Main_Menu;
////
////	CP_Vector pos = CP_Vector_Zero();
////	pos.x = (float)(WIN_WIDTH * 0.5f) - (Button_Exit.width / 2);
////	pos.y = (float)(WIN_HEIGHT * 0.8f) - (Button_Exit.height / 2);
////
////	Button Button_Exit = Asteroids_Button_Add_New_Button(100.0f, 100.0f);
////	Asteroids_Button_Set_Position(&Button_Exit, pos);
////	Asteroids_Button_Set_Text(&Button_Exit, 50.0f, "Exit");
////	Asteroids_Button_Draw_Text(Button_Exit);
////	Asteroids_Button_Set_Callback_Void(&Load_Main_Menu, &Button_Exit);
////	
////
////	int n = sizeof(LeaderBoard_Scores) / sizeof(LeaderBoard_Scores[0]);
////	Sort_Data(LeaderBoard_Scores, n);
////
////	if (player.name)
////	{
////		counter.name_length = (int)strlen(player.name);
////	}
////	else
////		counter.name_length = 0;
////}
////
////void Update_LeaderBoard(void)		// Draws and checks every frame of leaderboard
////{
////	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
////	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
////	CP_Settings_TextSize(50.0f);
////
////	float mousex = CP_Input_GetMouseX();
////	float mousey = CP_Input_GetMouseY();
////
////	Asteroids_Button_Update(&Button_Exit, mousex, mousey);
////	Draw_LeaderBoard();
////
////}
////
////void Load_Main_Menu(void)			// Function to return from leaderboard screen to main menu
////{
////	CP_Engine_SetNextGameState(Asteroids_MainMenu_Init, Asteroids_MainMenu_Update, Asteroids_MainMenu_Exit);
////}
////
////void LeaderBoard_Display_PlayerName()	// function to display name onto screen
////{
////	if (player.name)
////		CP_Font_DrawText(player.name, Leaderboard_Variables.x, Leaderboard_Variables.y);
////}
////
////void LeaderBoard_ReadInput()			// function to read input for player name
////{
////	if (CP_Input_KeyTriggered(KEY_ENTER))
////	{
////		Write_Leaderboard_Data();
////		return;
////	}
////
////	if (CP_Input_KeyTriggered(KEY_BACKSPACE))
////	{
////		if (counter.name_length > 0)
////		{
////			counter.name_length--;
////			player.name[counter.name_length] = '\0';
////		}
////	}
////
////	for (int i = KEY_A, j = KEY_0; i <= KEY_Z; i++, j++)
////	{
////		if (counter.name_length >= BUFFER_SIZE - 1)
////			return;
////
////		if (CP_Input_KeyTriggered(i))
////		{
////			player.name[counter.name_length] = (char)i;
////			counter.name_length++;
////		}
////		else if (CP_Input_KeyTriggered(j))
////		{
////			if (j > KEY_9)
////				return;
////
////			player.name[counter.name_length] = (char)j;
////			counter.name_length++;
////		}
////
////	}
////
////}
////
////void Draw_LeaderBoard(void)			// function whichs draws leaderboard variables
////{
////	CP_Settings_TextSize(50.0f);
////	CP_Settings_Fill(Leaderboard_Variables.text_color);
////	CP_Font_DrawText("LEADERBOARD", WIN_WIDTH / 2.0f, 50.0f);
////
////	CP_Font_DrawText("FIRST PLACE: ", WIN_WIDTH / 5.8f, Leaderboard_Variables.y + 105.0f);
////	CP_Font_DrawText("SECOND PLACE: ", WIN_WIDTH / 5.8f, Leaderboard_Variables.y + 205.0f);
////	CP_Font_DrawText("THIRD PLACE: ", WIN_WIDTH / 5.8f, Leaderboard_Variables.y + 305.0f);
////
////	for (int i = 0; i < MAX_LEADERS; i++)
////	{
////		char leaderscore_buffer[16];
////		sprintf_s(leaderscore_buffer, 16, "%d", LeaderBoard[i].score);//debug prints
////
////		CP_Font_DrawText(LeaderBoard[i].name, WIN_WIDTH / 2.0f, Leaderboard_Variables.y + 100.0f + (i * 100));
////		CP_Font_DrawText(leaderscore_buffer, WIN_WIDTH * 0.80f, Leaderboard_Variables.y + 100.0f + (i * 100));
////	}
////}
////
////void Exit_LeaderBoard(void)
////{
////	_fcloseall();
////}
////
////void Sort_Data(int test[], int n)	// function which sorts scores in descending order
////{
////	int i, j, temp;
////	char Temp_name[BUFFER_SIZE];
////	for (i = 0; i < n; i++)
////	{
////		for (j = i + 1; j < n; j++)
////		{
////			if (test[i] < test[j])
////			{
////				temp = test[i];											// If score gets sorted
////				strcpy_s(Temp_name, BUFFER_SIZE, LeaderBoard[i].name);  // Sort name also
////
////				test[i] = test[j];
////				strcpy_s(LeaderBoard[i].name, BUFFER_SIZE, LeaderBoard[j].name); // 
////
////				test[j] = temp;
////				strcpy_s(LeaderBoard[j].name, BUFFER_SIZE, Temp_name);
////			}
////		}
////		LeaderBoard[i].score = LeaderBoard_Scores[i];					// Write Sorted scores into struct
////	}
////	Write_Leaderboard_Data();											// Write sorted data into file
////}
////
////void Player_Is_Leader(void)			// Function which ask player to enter name if entitled leaderboard placement
////{
////	if (is_leader)
////	{
////		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
////		CP_Font_DrawTextBox("CONGRATULATIONS, YOU WON A SPOT ON THE LEADERBOARD! Please enter your name (Up to 20 characters) and press enter to register your score:",
////			(float)(WIN_WIDTH / WIN_WIDTH), (float)WIN_HEIGHT / 6.0f, (float)WIN_WIDTH);
////
////		LeaderBoard_Display_PlayerName();
////		LeaderBoard_ReadInput();
////	}
////}