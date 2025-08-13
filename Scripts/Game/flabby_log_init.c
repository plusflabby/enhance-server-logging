/*
	Global Variables
*/
//! Logger to do the log'n
ref flabby_logger flabbyLogger = null;
// Store player info
ref map<int, ref flabby_identifier> flabbyIdentifier = null;
/*
	Global Functions
*/
void setGlobalVariables()
{
	if (Replication.IsRunning())
	{
		if (Replication.IsServer())
		{
			flabbyLogger = new flabby_logger();
			flabbyIdentifier = new map<int, ref flabby_identifier>();
			flabby_setWebhook();
			return;
		}
	}
	
	GetGame().GetCallqueue().CallLater(setGlobalVariables, 1000, false); // 1s
}