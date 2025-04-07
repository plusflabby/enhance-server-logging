ref array<string> flabby_log_webhooks_list = {
	"webhooks_all",
	"webhooks_gamemode_player_connected",
	"webhooks_gamemode_player_registered",
	"webhooks_gamemode_player_disconnected",
	"webhooks_gamemode_player_spawned",
	"webhooks_gamemode_player_killed",
	"webhooks_gamemode_player_deleted",
	"webhooks_gamemode_chat_onnewmessage"
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

// Sending out webhooks
void flabby_log_webhook_send(flabby_log_output_extension extension, flabby_log_output_format format, flabby_log_output_category category, flabby_log log)
{
	switch (log.logId)
	{
		case flabby_log_identifier.SCR_GameMode_101:
		{
			string webhook_value = string.Empty;
			flabby_logger_update.getValueInFile("webhooks_gamemode_player_connected", webhook_value);
			if (webhook_value.IsEmpty() == false && webhook_value != "_NONE")
			{
				// Send http post to webhook_value
				string LogToSend = string.Empty;
				log.build(LogToSend, flabby_log_output_extension.JSON);
				RestContext rc = GetGame().GetRestApi().GetContext(webhook_value);
				rc.SetHeaders("Content-Type,application/json");
				rc.POST(null, string.Empty, LogToSend);
			}
			break;
		}
		
		case flabby_log_identifier.SCR_GameMode_106:
		{
			string webhook_value = string.Empty;
			flabby_logger_update.getValueInFile("webhooks_gamemode_player_registered", webhook_value);
			if (webhook_value.IsEmpty() == false && webhook_value != "_NONE")
			{
				// Send http post to webhook_value
				string LogToSend = string.Empty;
				log.build(LogToSend, flabby_log_output_extension.JSON);
				RestContext rc = GetGame().GetRestApi().GetContext(webhook_value);
				rc.SetHeaders("Content-Type,application/json");
				rc.POST(null, string.Empty, LogToSend);
			}
			break;
		}
		
		case flabby_log_identifier.SCR_GameMode_107:
		{
			string webhook_value = string.Empty;
			flabby_logger_update.getValueInFile("webhooks_gamemode_player_disconnected", webhook_value);
			if (webhook_value.IsEmpty() == false && webhook_value != "_NONE")
			{
				// Send http post to webhook_value
				string LogToSend = string.Empty;
				log.build(LogToSend, flabby_log_output_extension.JSON);
				RestContext rc = GetGame().GetRestApi().GetContext(webhook_value);
				rc.SetHeaders("Content-Type,application/json");
				rc.POST(null, string.Empty, LogToSend);
			}
			break;
		}
		
		case flabby_log_identifier.SCR_GameMode_109:
		{
			string webhook_value = string.Empty;
			flabby_logger_update.getValueInFile("webhooks_gamemode_player_spawned", webhook_value);
			if (webhook_value.IsEmpty() == false && webhook_value != "_NONE")
			{
				// Send http post to webhook_value
				string LogToSend = string.Empty;
				log.build(LogToSend, flabby_log_output_extension.JSON);
				RestContext rc = GetGame().GetRestApi().GetContext(webhook_value);
				rc.SetHeaders("Content-Type,application/json");
				rc.POST(null, string.Empty, LogToSend);
			}
			break;
		}
		
		case flabby_log_identifier.SCR_GameMode_110:
		{
			string webhook_value = string.Empty;
			flabby_logger_update.getValueInFile("webhooks_gamemode_player_killed", webhook_value);
			if (webhook_value.IsEmpty() == false && webhook_value != "_NONE")
			{
				// Send http post to webhook_value
				string LogToSend = string.Empty;
				log.build(LogToSend, flabby_log_output_extension.JSON);
				RestContext rc = GetGame().GetRestApi().GetContext(webhook_value);
				rc.SetHeaders("Content-Type,application/json");
				rc.POST(null, string.Empty, LogToSend);
			}
			break;
		}
		
		case flabby_log_identifier.SCR_GameMode_114:
		{
			string webhook_value = string.Empty;
			flabby_logger_update.getValueInFile("webhooks_gamemode_player_deleted", webhook_value);
			if (webhook_value.IsEmpty() == false && webhook_value != "_NONE")
			{
				// Send http post to webhook_value
				string LogToSend = string.Empty;
				log.build(LogToSend, flabby_log_output_extension.JSON);
				RestContext rc = GetGame().GetRestApi().GetContext(webhook_value);
				rc.SetHeaders("Content-Type,application/json");
				rc.POST(null, string.Empty, LogToSend);
			}
			break;
		}
		
		case flabby_log_identifier.SCR_ChatComponent_101:
		{
			string webhook_value = string.Empty;
			flabby_logger_update.getValueInFile("webhooks_gamemode_chat_onnewmessage", webhook_value);
			if (webhook_value.IsEmpty() == false && webhook_value != "_NONE")
			{
				// Send http post to webhook_value
				string LogToSend = string.Empty;
				log.build(LogToSend, flabby_log_output_extension.JSON);
				RestContext rc = GetGame().GetRestApi().GetContext(webhook_value);
				rc.SetHeaders("Content-Type,application/json");
				rc.POST(null, string.Empty, LogToSend);
			}
			break;
		}
		
		default:
		{
			string webhook_value = string.Empty;
			flabby_logger_update.getValueInFile("webhooks_all", webhook_value);
			if (webhook_value.IsEmpty() == false && webhook_value != "_NONE")
			{
				// Send http post to webhook_value
				string LogToSend = string.Empty;
				log.build(LogToSend, flabby_log_output_extension.JSON);
				RestContext rc = GetGame().GetRestApi().GetContext(webhook_value);
				rc.SetHeaders("Content-Type,application/json");
				rc.POST(null, string.Empty, LogToSend);
			}
			break;
		}
	}
	return;
}

void flabby_setWebhook()
{
	if (flabbyLogger)
	{
		flabby_logger.Event_OnLogStored.Insert(flabby_log_webhook_send);
		return;
	}
	
	GetGame().GetCallqueue().CallLater(flabby_setWebhook, 1000, false); // 1s
}

