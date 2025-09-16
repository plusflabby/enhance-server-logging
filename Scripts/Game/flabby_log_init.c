/*
 * flabby_log_init.c
 *
 * Purpose: Handles initialization of logging systems in the game.
 * Contains functions for setting up, configuring, and starting logging.
 * Author: https://github.com/plusflabby
 */
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
			GetGame().GetCallqueue().CallLater(flabby_setWebhook, 2000, false); // 1s
			return;
		}
	}
	
	GetGame().GetCallqueue().CallLater(setGlobalVariables, 1000, false); // 1s
}