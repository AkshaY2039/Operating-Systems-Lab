class Scheduler
{
	int Number_of_Processes,Process_ID[20],Arrival_Time[20],Service_Time[20],Completion_Time[20],Turn_Around_Time[20],Wait_Time[20];
	public:
		void Select_Schedule();
		void Manual_Input();
		void AutoGen_Input();
		void Files_As_Processes();
		void Sort_By(int Array[]);
		void Formatted_Output();
		void First_Come_First_Serve();
		void Shortest_Job_First();
		void Shortest_Remaining_Time_Next();
		void Round_Robin();
		void Static_Priority();
		void Dynamic_Priority();
		void Highest_Response_Ratio_Next();
		void Display_Ready_Queue();
};