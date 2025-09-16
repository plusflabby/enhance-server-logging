/*
 * flabby_log_enum.c
 *
 * Purpose: Handles logging for enum-related operations in the game.
 * Contains functions for tracking, formatting, and outputting enum logs.
  * Author: https://github.com/plusflabby
 */

// Add similar comments for each function and major code block below
/*
	Enums for customization(s) though command
*/
// How to categorize data in file(s)
enum flabby_log_output_category
{
	DEBUG,// A file for each class method(function)
	INFO, // Files for each group(ex. GameMode.json & Players.json)
	ALL // All data in one file
}
// How much data to store in a log
enum flabby_log_output_format
{
	COMPACT, // Just the essential data of a log
	NORMAL, // COMPACT format just with time(s)
	RICH // NORMAL format but with extra, possible, useful data
}
// File extension
enum flabby_log_output_extension
{
	JSON, // Output to ".json" file
	LOG, // Output to ".log" file
	TXT, // Output plain text ".txt" file
	DISCORD // Discord output for webhooks
}
// Files 
enum flabby_log_output_file
{
	// Common
	DEBUG,
	INFO,
	ALL,
	
	// Specific
	PLAYERS,
	CHAT,
	WORLD
}
/*
	Enums for a log
*/
enum flabby_log_identifier
{
	SCR_GameMode_GENERIC, // Any GameMode log without an identifier
	SCR_GameMode_101, // Player connected
	SCR_GameMode_102, // Player audit success
	SCR_GameMode_103, // Player audit failed
	SCR_GameMode_104, // Player audit revived
	SCR_GameMode_105, // Player audit timeouted
	SCR_GameMode_106, // Player registered
	SCR_GameMode_107, // Player disconnected
	SCR_GameMode_108, // m_OnPostCompPlayerDisconnected
	SCR_GameMode_109, // m_OnPlayerSpawned
	SCR_GameMode_110, // m_OnPlayerKilled
	SCR_GameMode_111, // m_OnControllableDestroyed
	SCR_GameMode_112, // Event_OnGameStart
	SCR_GameMode_113, // m_OnGameEnd
	SCR_GameMode_114, // m_OnPlayerDeleted
	SCR_GameMode_115, // When player role is changed
	SCR_GameMode_116, // OnWorldPostProcess
	SCR_GameMode_117, // OnControllableSpawn
	SCR_GameMode_118, // When player role is changed
	SCR_GameMode_119, // When player role controller is deleted
	
	SCR_ChatComponent_GENERIC, // Any ChatComponent log without an identifier
	SCR_ChatComponent_101, // OnNewMessage() // When someone sends chat message
	
	SCR_Building_101, // SCR_CampaignBuildingNetworkComponent.SendDeleteNotification() // When disassembled structure
	
	CUSTOM_Extract, // Extract is requested // When joining
}