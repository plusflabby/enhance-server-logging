// Global rest callback for webhooks
ref flabby_RestCallback flabby_webhookCallback = new flabby_RestCallback;

// Global list of webhook names
ref array<string> flabby_log_webhooks_list = {
	"webhooks_all",
	"webhooks_gamemode_player_connected",
	"webhooks_gamemode_player_registered",
	"webhooks_gamemode_player_disconnected",
	"webhooks_gamemode_player_spawned",
	"webhooks_gamemode_player_killed",
	"webhooks_gamemode_player_deleted",
	"webhooks_gamemode_chat_onnewmessage",
	"webhooks_gamemode_building_delete",
	"webhooks_player_data_extract"
};

bool flabby_log_webhook_setup()
{
	// Check if webhook config events are in configuration json file
	bool rntValue = true;
	for (int i = 0; i < flabby_log_webhooks_list.Count(); i++)
	{
		string webhook_value = string.Empty;
		flabby_logger_update.getValueInFile(flabby_log_webhooks_list.Get(i), webhook_value);
		if (webhook_value == "_NONE")
		{
			rntValue = false;
			break;
		}
	}
	
	return rntValue;
	
}

void flabby_log_webhook_creation()
{
	// Add events to configuration file
	for (int i = 0; i < flabby_log_webhooks_list.Count(); i++)
	{
		string webhook_value = string.Empty;
		flabby_logger_update.getValueInFile(flabby_log_webhooks_list.Get(i), webhook_value);
		if (webhook_value == "_NONE")
		{
			flabby_logger_update.addKeyToFile(flabby_log_webhooks_list.Get(i), string.Empty);
		}
	}
}


void GetWebookAndSendJson(string configJsonKey, notnull flabby_log log)
{
	string webhook_value = string.Empty;
	flabby_logger_update.getValueInFile(configJsonKey, webhook_value);
	if (webhook_value.IsEmpty() == false && webhook_value != "_NONE")
	{
		// Send http post to webhook_value
		string LogToSend = string.Empty;
		if (webhook_value.Contains("discord.com"))
		{
			log.build(LogToSend, flabby_log_output_extension.DISCORD);
			LogToSend.Replace(",,, ", "\\n");
			string Username = "Logging Enhanced by flabby";
			if (flabbyLogger.serverName != "EXAMPLE SERVER NAME") Username = flabbyLogger.serverName;
			string discordOutput1 = "{\"username\": \"%1\", \"content\": \"%2\" }";
			LogToSend = string.Format(discordOutput1, Username, LogToSend);
		}
		else
		{
			log.build(LogToSend, flabby_log_output_extension.JSON);
		}
		if (LogToSend.IsEmpty())
		{
			PrintFormat("GetWebookAndSendJson trying to send empty body. configJsonKey=%1", configJsonKey, level:LogLevel.WARNING);
			return;
		}
		RestContext rc = GetGame().GetRestApi().GetContext(webhook_value);
		rc.SetHeaders("Content-Type,application/json");
		rc.POST(flabby_webhookCallback, "", LogToSend);
		return;
	}
	
	if (configJsonKey != "webhooks_all")
	{
		GetWebookAndSendJson("webhooks_all", log);
	}
}

void flabby_setWebhook()
{
	if (flabbyLogger)
	{
		flabbyLogger.Event_OnLogStored.Insert(flabby_log_webhook_send);
		return;
	}
	
	GetGame().GetCallqueue().CallLater(flabby_setWebhook, 1000, false); // 1s
}

class flabby_RestCallback: RestCallback
{
	//------------------------------------------------------------------------------------------------
    override void OnError(int errorCode)
    {
        Print("A webhook has failed with error code = " + errorCode.ToString(), LogLevel.WARNING);
		
    };
 
	//------------------------------------------------------------------------------------------------
    override void OnTimeout()
    {
        Print("A webhook has timed out", LogLevel.WARNING);	
    };
};

// Sending out webhooks
void flabby_log_webhook_send(flabby_log_output_extension extension, flabby_log_output_format format, flabby_log_output_category category, notnull flabby_log log)
{
	switch (log.logId)
	{
		case flabby_log_identifier.SCR_GameMode_101:
		{
			GetWebookAndSendJson("webhooks_gamemode_player_connected", log);
			break;
		}
		
		case flabby_log_identifier.SCR_GameMode_106:
		{
			GetWebookAndSendJson("webhooks_gamemode_player_registered", log);
			break;
		}
		
		case flabby_log_identifier.SCR_GameMode_107:
		{
			GetWebookAndSendJson("webhooks_gamemode_player_disconnected", log);
			break;
		}
		
		case flabby_log_identifier.SCR_GameMode_109:
		{
			GetWebookAndSendJson("webhooks_gamemode_player_spawned", log);
			break;
		}
		
		case flabby_log_identifier.SCR_GameMode_110:
		{
			GetWebookAndSendJson("webhooks_gamemode_player_killed", log);
			break;
		}
		
		case flabby_log_identifier.SCR_GameMode_114:
		{
			GetWebookAndSendJson("webhooks_gamemode_player_deleted", log);
			break;
		}
		
		case flabby_log_identifier.SCR_ChatComponent_101:
		{
			GetWebookAndSendJson("webhooks_gamemode_chat_onnewmessage", log);
			break;
		}
		
		case flabby_log_identifier.SCR_Building_101:
		{
			GetWebookAndSendJson("webhooks_gamemode_building_delete", log);
			break;
		}
		
		case flabby_log_identifier.CUSTOM_Extract:
		{
			GetWebookAndSendJson("webhooks_player_data_extract", log);
			break;
		}
		
		default:
		{
			GetWebookAndSendJson("webhooks_all", log);
			break;
		}
	}
	return;
}