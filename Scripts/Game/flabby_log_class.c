/*
	Classes
*/
//! Data stored in log
class flabby_data
{
	string key;
	string data;
	flabby_log_output_format format;
	
	void flabby_data(string key_, string data_, flabby_log_output_format format_ = flabby_log_output_format.RICH)
	{
		key = key_;
		data = data_;
		format = format_;
	}
}
//! Builder class 
class flabby_log
{
	// variables
	//! Logging identifier
	int logId;
	// Foat time
	float serverTimeSecondsFloat;
	//! Int time
	int systemTimeInt;
	//! String times
	string systemTimeUTC, serverTimeSecondsStr, systemTimeStr = string.Empty;
	//! Extra info
	ref map<string, ref flabby_data> info = new map<string, ref flabby_data>();
	//! File to store log if needed
	ref array<flabby_log_output_file> fileToStoreData = new array<flabby_log_output_file>();
	//! Category of log
	flabby_log_output_category category;
	
//	// Load/get defaults in constructor
//	//! Default log's output_category
//	int output_category = flabbyLogger.category;
//	//! Default log's output_format
//	int output_format = flabbyLogger.format;
//	//! Default log's output_extension
//	int output_extension = flabbyLogger.extension;
	
	//! constructor
	void flabby_log(flabby_log_identifier logs_identifier)
	{
		logId = logs_identifier;
		setDebugTime();
	}
	
	// Static Methods
	//! Debug information for time
	void setDebugTime()
	{
		systemTimeInt = System.GetUnixTime();
		systemTimeStr = SCR_DateTimeHelper.GetDateTimeLocal();
		systemTimeUTC = SCR_DateTimeHelper.GetDateTimeUTC();
		
		serverTimeSecondsFloat = Math.Round(GetGame().GetWorld().GetWorldTime()) / 1000;
		serverTimeSecondsStr = serverTimeSecondsFloat.ToString();
	}
	// Add times to data(info var)
	void addDebugTime()
	{
		info.Insert("systemTimeInt", new flabby_data("systemTimeInt", systemTimeInt.ToString(), flabby_log_output_format.NORMAL));
		info.Insert("serverTimeSecondsFloat", new flabby_data("systemTimeInt", serverTimeSecondsFloat.ToString(), flabby_log_output_format.NORMAL));
		info.Insert("systemTimeUTC", new flabby_data("systemTimeInt", systemTimeUTC, flabby_log_output_format.NORMAL));
		info.Insert("systemTimeStr", new flabby_data("systemTimeInt", systemTimeStr, flabby_log_output_format.NORMAL));
		info.Insert("serverTimeSecondsStr", new flabby_data("systemTimeInt", serverTimeSecondsStr, flabby_log_output_format.NORMAL));
	}
	// Non-Static Methods
	//! Add an informational string
	bool add(string name, string input, flabby_log_output_format format_ = flabby_log_output_format.RICH)
	{
		return info.Insert(name, new flabby_data(name, input));
	}
	//! Add an informational int
	bool add(string name, int input, flabby_log_output_format format_ = flabby_log_output_format.RICH)
	{
		return info.Insert(name, new flabby_data(name, input.ToString()));
	}
	//! Add information
	bool add(map<string, string> input, flabby_log_output_format format_ = flabby_log_output_format.RICH)
	{
		for (int i; i < input.Count(); i++)
		{
			string key = input.GetKey(i);
			string value = input.GetElement(i);
			info.Insert(key, new flabby_data(key, value));
		}
		return true;
	}
	//! Build this class and output
	void build(out string output, flabby_log_output_extension extension)
	{
		addDebugTime();
		
		if (extension == flabby_log_output_extension.TXT)
		{
			string str = string.Empty;
			for (int i; i < info.Count(); i++)
			{
				string key = info.GetKey(i);
				flabby_data value = info.GetElement(i);
				
				if (str.IsEmpty())
				{
					str += string.Format("%1: %2", key, value.data);
				}
				else 
				{
					str += string.Format(", %1: %2", key, value.data);
				}
			}
			output = str;
			return;
		}
		else if (extension == flabby_log_output_extension.LOG)
		{
			string str = string.Empty;
			for (int i; i < info.Count(); i++)
			{
				string key = info.GetKey(i);
				flabby_data value = info.GetElement(i);
				
				if (str.IsEmpty())
				{
					str += string.Format("%1 = %2", key, value.data);
				}
				else 
				{
					str += string.Format(", %1 = %2", key, value.data);
				}
			}
			output = str;
			return;
		}
		else if (extension == flabby_log_output_extension.JSON)
		{
			SCR_JsonSaveContext jsonSaver = new SCR_JsonSaveContext();
			for (int i; i < info.Count(); i++)
			{
				string key = info.GetKey(i);
				flabby_data value = info.GetElement(i);
				
				jsonSaver.WriteValue(key, value.data);
			}
			output = jsonSaver.ExportToString();
			return;
		}
		else
		{
			Print("flabby_log.build() Extension not defined", LogLevel.ERROR);
		}
		
	}
	string AsString()
	{
		string infoStr = string.Empty;
		string rtnStr = string.Empty;
		for (int i; i < info.Count(); i++)
		{
			string key = info.GetKey(i);
			flabby_data value = info.GetElement(i);
			if (infoStr.IsEmpty())
			{
				infoStr += string.Format("%1=%2", key, value.data);
			}
			else
			{
				infoStr += string.Format(", %1='%2'", key, value.data);
			}
		}
		rtnStr += infoStr;
		rtnStr += string.Format(", Data_ID='%1'", SCR_Enum.GetEnumName(flabby_log_identifier, logId));
		rtnStr += string.Format(", Server_time='%1s'", Math.Round(serverTimeSecondsFloat));
		rtnStr += string.Format(", System_time='%1s'", systemTimeStr);
		
		return rtnStr;
	}
}
//! Event log def
void F_Log(flabby_log_output_extension extension, flabby_log_output_format format, flabby_log_output_category category, flabby_log log);
typedef func F_Log;
//! Class for printing and saving logs
class flabby_logger
{
	ref static ScriptInvokerBase<F_Log> Event_OnLogStored = new ScriptInvokerBase<F_Log>();
	
	//! For the Print function
	const string printPrefix = "<flabby_logger>";
	
	// Cfg variables
	flabby_log_output_extension extension = flabby_log_output_extension.JSON;
	flabby_log_output_format format = flabby_log_output_format.RICH;
	flabby_log_output_category category = flabby_log_output_category.ALL; // NOT USED
	bool printLog = true;
	string serverName = string.Empty;
	bool fileLog = true; // write log files
	int extractPlayerDataSeconds = 0;
	
	//! constructor
	void flabby_logger()
	{
		// First console's log of the mod :)
		Print("<flabby_logger> Hello World!", LogLevel.NORMAL);
		
		// See if the cfg files exists 
		if (FileIO.FileExists("$profile:/flabby/enhanced-logging.json") == false)
		{
			// Since the file does not exist set default values
			flabby_logger_update.updateExtension(flabby_log_output_extension.JSON);
			flabby_logger_update.addKeyToFile("flabby_log_output_server_console", "TRUE");
			flabby_logger_update.addKeyToFile("flabby_log_output_server_name", "EXAMPLE SERVER NAME");
			flabby_logger_update.addKeyToFile("flabby_log_extract_player_data_seconds", "0");
		}
		
		// Get extension from cfg file or set to default
		SCR_JsonLoadContext jsonLoader = new SCR_JsonLoadContext();
		jsonLoader.LoadFromFile("$profile:/flabby/enhanced-logging.json");
		jsonLoader.ReadValue("flabby_log_output_extension", extension);
		if (jsonLoader.ReadValue("flabby_log_output_server_name", serverName) == false)
		{
			flabby_logger_update.addKeyToFile("flabby_log_output_server_name", "EXAMPLE SERVER NAME");
			serverName = "EXAMPLE SERVER NAME";
		}
		string printerLogCfg = "TRUE";
		if (jsonLoader.ReadValue("flabby_log_output_server_console", printerLogCfg) == false)
		{
			flabby_logger_update.addKeyToFile("flabby_log_output_server_console", "FALSE");
		}
		if (printerLogCfg == "TRUE") printLog = true;
		else printLog = false;
		string writerLogCfg = "TRUE";
		if (jsonLoader.ReadValue("flabby_log_output_to_file", writerLogCfg) == false)
		{
			flabby_logger_update.addKeyToFile("flabby_log_output_to_file", "TRUE");
		}
		if (writerLogCfg == "TRUE") fileLog = true;
		else fileLog = false;
		string extractStr = "0";
		if (jsonLoader.ReadValue("flabby_log_extract_player_data_seconds", extractStr) == false)
		{
			flabby_logger_update.addKeyToFile("flabby_log_extract_player_data_seconds", "0");
		}
		if (extractStr == "0") extractPlayerDataSeconds = 0;
		else extractPlayerDataSeconds = extractStr.ToInt();
		
		// Webhooks configuration
		bool webhooks_config = flabby_log_webhook_setup();
		if (webhooks_config == false)
		{
			flabby_log_webhook_creation();
		}
	}
	
	//! Prints the log
	void printer(notnull flabby_log log)
	{
		if (printLog == false) return;
		
		log.add("ServerName", serverName);
		
		string logStr = log.AsString();
		if (logStr.IsEmpty() == false)
		{
			Print(string.Format("%1 [ %2 ]", printPrefix, logStr), LogLevel.NORMAL);
		}
	}
	
	//! Stores the log in server's profile
	bool writer(notnull flabby_log log)
	{
		// Add server name 
		log.add("ServerName", serverName);
		
		// Invoke Listened Events
		Event_OnLogStored.Invoke(extension, format, category, log);
		
		if (fileLog == false) return false;
		
		// Get dates
		int year, month, day, hour, minute, second;
		System.GetYearMonthDayUTC(year, month, day);
		System.GetHourMinuteSecondUTC(hour, minute, second);
		// Make directory(s)
		FileIO.MakeDirectory("$profile:/flabby");
		FileIO.MakeDirectory(string.Format("$profile:/flabby/%1", year));
		FileIO.MakeDirectory(string.Format("$profile:/flabby/%1/%2", year, month));
		FileIO.MakeDirectory(string.Format("$profile:/flabby/%1/%2/%3", year, month, day));
		
		
		// Data to store in file
		string data = string.Empty;
		log.build(data, flabbyLogger.extension);
		
		if (data.IsEmpty())
		{
			Print("Log's data string is empty", LogLevel.ERROR);
			return false;
		}
		
		string ext = string.Empty;
		switch (flabbyLogger.extension)
		{
			case flabby_log_output_extension.LOG:
			{
				ext = "log";
				break;
			}
			case flabby_log_output_extension.TXT:
			{
				ext = "txt";
				break;
			}
			case flabby_log_output_extension.JSON:
			{
				ext = "json";
				break;
			}
		}
		
		if (log.fileToStoreData.Count() > 0)
		{
			foreach (flabby_log_output_file fileName : log.fileToStoreData)
			{
				string name = string.Empty;
				switch (fileName)
				{
					case flabby_log_output_file.ALL:
					{
						name = "ALL";
						break;
					}
					case flabby_log_output_file.INFO:
					{
						name = "INFO";
						break;
					}
					case flabby_log_output_file.DEBUG:
					{
						name = "DEBUG";
						break;
					}
					case flabby_log_output_file.WORLD:
					{
						name = "WORLD";
						break;
					}
					case flabby_log_output_file.PLAYERS:
					{
						name = "PLAYERS";
						break;
					}
					case flabby_log_output_file.CHAT:
					{
						name = "CHAT";
						break;
					}
				}
				
				// Write string to new line in files
				FileHandle fileHandle = FileIO.OpenFile(string.Format("$profile:/flabby/%1/%2/%3/%4hr.%6.%5", year, month, day, hour, ext, name), FileMode.APPEND);
				if (fileHandle)
				{
					fileHandle.WriteLine(string.Format("%2 %1", data, log.systemTimeStr));
					fileHandle.Close();
				}
				else
				{
					array<string> lines = new array<string>();
					lines.Insert(string.Format("%2 %1", data, log.systemTimeStr));
					bool fileIo = SCR_FileIOHelper.WriteFileContent(string.Format("$profile:/flabby/%1/%2/%3/%4hr.%6.%5", year, month, day, hour, ext, name), lines);
				}
			}
		}
		else 
		{
			// Write string to new line in files
			FileHandle fileHandle = FileIO.OpenFile(string.Format("$profile:/flabby/%1/%2/%3/%4hr.ALL.%5", year, month, day, hour, ext), FileMode.APPEND);
			if (fileHandle)
			{
				fileHandle.WriteLine(string.Format("%2 %1", data, log.systemTimeStr));
				fileHandle.Close();
				return true;
			}
			else if (FileIO.FileExists(string.Format("$profile:/flabby/%1/%2/%3/%4hr.ALL.%5", year, month, day, hour, ext)) == false)
			{
				array<string> lines = new array<string>();
				lines.Insert(string.Format("%2 %1", data, log.systemTimeStr));
				bool fileIo = SCR_FileIOHelper.WriteFileContent(string.Format("$profile:/flabby/%1/%2/%3/%4hr.ALL.%5", year, month, day, hour, ext), lines);
				return fileIo;
			}
		}
		
		return true;
	}
	
	
	
	
	// Static
	static string getPlayerName(int playerGameId)
	{
		if (flabbyIdentifier)
		{
			flabby_identifier id = flabbyIdentifier.Get(playerGameId);
			if (id)
			{
				return id.name;
			}
		}
		
		ArmaReforgerScripted game = GetGame();
		if (!game) return "Error with GetGame()";
		PlayerManager pm = game.GetPlayerManager();
		if (!pm) return "Error with PlayerManager";
		return pm.GetPlayerName(playerGameId);
	}
	static string getPlayerBohemiaId(int playerGameId)
	{
		if (flabbyIdentifier)
		{
			flabby_identifier id = flabbyIdentifier.Get(playerGameId);
			if (id)
			{
				return id.bohemia;
			}
		}
		
		ArmaReforgerScripted game = GetGame();
		if (!game) return "Error with GetGame()";
		BackendApi be = game.GetBackendApi();
		if (!be) return "Error with BackendApi";
		return be.GetPlayerIdentityId(playerGameId);
	}
	static string getPlayerFaction(int playerGameId)
	{
		ArmaReforgerScripted game = GetGame();
		if (!game)
			return "UNKNOWN";
		
		// Get Player IEntity
		PlayerManager PM = game.GetPlayerManager();
		if (!PM)
			return "UNKNOWN";
		
		IEntity ent = PM.GetPlayerControlledEntity(playerGameId);
		if (!ent)
			return "UNKNOWN";
		
		FactionAffiliationComponent factionComp = FactionAffiliationComponent.Cast(ent.FindComponent(FactionAffiliationComponent));

		// Search for the faction component on parent entities as not always is it on the same component as this one (vehicle for an example)
		while (!factionComp && ent)
		{
			ent = ent.GetParent();
			if (ent)
				factionComp = FactionAffiliationComponent.Cast(ent.FindComponent(FactionAffiliationComponent));
		}

		if (!factionComp)
			return "UNKNOWN";

		Faction faction = factionComp.GetAffiliatedFaction();
		if (!faction)
			faction = factionComp.GetDefaultAffiliatedFaction();

		return faction.GetFactionName();
	}
}