/*
 * flabby_log_EXAMPLE_LOGr.c
 *
 * Purpose: Example file for logging implementation in the game.
 * Contains sample functions for tracking, formatting, and outputting logs.
 * Author: https://github.com/plusflabby
 */
/*

// Step one: identify the log
modded enum flabby_log_identifier
{
	CUSTOM_LOG_ONE
}

// Step two: add log id to variable and config
void flabbyLogExampleInit()
{
	flabby_log_webhook_custom.Insert(flabby_log_identifier.CUSTOM_LOG_ONE, "custom_log_name_in_config_file");
}

// Step three: make a log
void flabbyLogExampleFire()
{
	// Build log 
	ref flabby_log log = new flabby_log(flabby_log_identifier.CUSTOM_LOG_ONE);
	if (log && flabbyLogger)
	{
		// Add data 
		log.add("function", "flabbyLogExampleFire");
		log.add("exampleData", "123");
		// Print and store log
		flabbyLogger.writer(log); // This will fire the webhook
	}
}

// Step four: Run mod once on server so config is updated then Edit enhanced-logging.json

// Here's an example of making your custom log to work
modded class SCR_BaseGameMode
{
	override protected void EOnInit(IEntity owner)
	{
		flabbyLogExampleInit();
		super.EOnInit(owner);
		m_OnPlayerConnected.Insert(flabby_OnPlayerConnectedExample);
	}
	
	protected void flabby_OnPlayerConnectedExample(int playerId)
	{
		flabbyLogExampleFire();
	}
}
*/