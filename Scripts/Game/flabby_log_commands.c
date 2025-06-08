/*
	Classes to be inherited
*/
//! Core commands class
class flabby_log_command : ScrServerCommand
{
	override event string GetKeyword()
	{
		return "flabby";
	}
	
	
	// Run command server-side
	//-----------------------------------------------------------------------------
	override bool IsServerSide()
	{
		return true;
	}
	
	// Set requirement to admin permission via RCON
	//-----------------------------------------------------------------------------
	override int RequiredRCONPermission()
	{
		return ERCONPermissions.PERMISSIONS_ADMIN;
	}
	
	// Set requirement to be logged in administrator for chat command
	//-----------------------------------------------------------------------------
	override int RequiredChatPermission()
	{
		return EPlayerRole.ADMINISTRATOR;
	}
	
	// Handle Chat command on server
	//-----------------------------------------------------------------------------
	override ref ScrServerCmdResult OnChatServerExecution(array<string> argv, int playerId)
	{
		return ScrServerCmdResult(string.Empty, EServerCmdResultType.OK);
	}
	
	// Handle Chat command on client
	//-----------------------------------------------------------------------------
	override ref ScrServerCmdResult OnChatClientExecution(array<string> argv, int playerId)
	{
		return ScrServerCmdResult(string.Empty, EServerCmdResultType.OK);
	}
	
	// Handle RCON command on server
	//-----------------------------------------------------------------------------
	override ref ScrServerCmdResult OnRCONExecution(array<string> argv)
	{
		return ScrServerCmdResult(string.Empty, EServerCmdResultType.OK);
	}
	
	// Handle Pending command
	//-----------------------------------------------------------------------------
	override ref ScrServerCmdResult OnUpdate()
	{
		return ScrServerCmdResult(string.Empty, EServerCmdResultType.OK);
	}

}

/*
	Commands
*/
//! Help command
class flabby_log_cmd_help : flabby_log_command
{
	override event string GetKeyword()
	{
		return "loghelp";
	}
	
	override int RequiredChatPermission()
	{
		return EPlayerRole.NONE;
	}
	
	override ref ScrServerCmdResult OnChatServerExecution(array<string> argv, int playerId)
	{
		string helpString = string.Empty;
		helpString += "#login Is required for before a command\n";
		helpString += "Examples of updating log formatting,\n";
		helpString += "#log format COMPACT - Just the essential data of a log\n";
		helpString += "#log format NORMAL - COMPACT format just with time(s)\n";
		helpString += "#log format RICH - NORMAL format but with extra, possible, useful data\n\n";
		helpString += "Examples of updating log extensions,\n";
		helpString += "#log extension JSON - File(s) will be .json\n";
		helpString += "#log extension LOG - File(s) will in .log\n";;
		helpString += "#log extension TXT - File(s) will plain .txt\n";
		helpString += "Example to disable server log printing,\n";
		helpString += "#log print false - No printing in server console log\n";
		
		return ScrServerCmdResult(helpString, EServerCmdResultType.OK);
	}
}
//! Log configurating command
class flabby_log_cmd_config : flabby_log_command
{
	override event string GetKeyword()
	{
		return "log";
	}
	
	override ref ScrServerCmdResult OnChatServerExecution(array<string> argv, int playerId)
	{
		if (argv[1])
		{
			const string argOne = argv[1];
			argOne.ToLower();
			
			if (argOne == "test")
			{
				// Build test log
				ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_GENERIC);
				if (log && flabbyLogger)
				{
					log.add("test", "log");
					log.setDebugTime();
					// Print and store log
					flabbyLogger.printer(log);
					flabbyLogger.writer(log);
					return ScrServerCmdResult("Success, test log printed and stored.", EServerCmdResultType.OK);
				}
				else
				{
					return ScrServerCmdResult("Failed, make sure server is running with or without the peertool plugin.", EServerCmdResultType.ERR);
				}
			}
			
			 //! Option
			const string argTwo = argv[1];
			argTwo.ToLower();
			 //! Value
			const string argThree = argv[2];
			argThree.ToUpper();
			switch (argTwo)
			{
				case "format":
				{
					if (argThree == "NORMAL")
					{
						flabby_logger_update.updateFormat(flabby_log_output_format.NORMAL);
						return ScrServerCmdResult(string.Format("Success, updated format to NORMAL"), EServerCmdResultType.OK);
					}
					if (argThree == "RICH")
					{
						flabby_logger_update.updateFormat(flabby_log_output_format.RICH);
						return ScrServerCmdResult(string.Format("Success, updated format to RICH"), EServerCmdResultType.OK);
					}
					if (argThree == "COMPACT")
					{
						flabby_logger_update.updateFormat(flabby_log_output_format.COMPACT);
						return ScrServerCmdResult(string.Format("Success, updated format to COMPACT"), EServerCmdResultType.OK);
					}
					
					break;
				}
				case "extension":
				{
					if (argThree == "LOG")
					{
						flabby_logger_update.updateExtension(flabby_log_output_extension.LOG);
						return ScrServerCmdResult(string.Format("Success, updated extension to LOG"), EServerCmdResultType.OK);
					}
					if (argThree == "JSON")
					{
						flabby_logger_update.updateExtension(flabby_log_output_extension.JSON);
						return ScrServerCmdResult(string.Format("Success, updated extension to JSON"), EServerCmdResultType.OK);
					}
					if (argThree == "TXT")
					{
						flabby_logger_update.updateExtension(flabby_log_output_extension.TXT);
						return ScrServerCmdResult(string.Format("Success, updated extension to TXT"), EServerCmdResultType.OK);
					}
					break;
				}
				case "print":
				{
					if (argThree == "TRUE")
					{
						flabby_logger_update.addKeyToFile("flabby_log_output_server_console", "TRUE");
						flabbyLogger.printLog = true;
						return ScrServerCmdResult(string.Format("Success, updated to TRUE"), EServerCmdResultType.OK);
					}
					if (argThree == "FALSE")
					{
						flabby_logger_update.addKeyToFile("flabby_log_output_server_console", "FALSE");
						flabbyLogger.printLog = false;
						return ScrServerCmdResult(string.Format("Success, updated to FALSE"), EServerCmdResultType.OK);
					}
					break;
				}
				case "file":
				{
					if (argThree == "TRUE")
					{
						flabby_logger_update.addKeyToFile("flabby_log_output_to_file", "TRUE");
						flabbyLogger.fileLog = true;
						return ScrServerCmdResult(string.Format("Success, updated file output to TRUE"), EServerCmdResultType.OK);
					}
					if (argThree == "FALSE")
					{
						flabby_logger_update.addKeyToFile("flabby_log_output_to_file", "FALSE");
						flabbyLogger.fileLog = false;
						return ScrServerCmdResult(string.Format("Success, updated file output to FALSE"), EServerCmdResultType.OK);
					}
					break;
				}
			}
		}
		
		return ScrServerCmdResult("Display all commands with #loghelp", EServerCmdResultType.PARAMETERS);
	}
}