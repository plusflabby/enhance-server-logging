/*


modded class SCR_GameModeEditor
{
	protected override void OnGameEnd()
	{
		setEditorScripts();
	}
	
	protected void setEditorScripts()
	{
		if (Replication.IsClient())
		{      
			return;
		}
		
		if (Replication.IsRunning() == false)
		{
			GetGame().GetCallqueue().CallLater(setEditorScripts, 500, false);
			return;
		}
		
		if (m_Core)
		{
			if (m_Core.Event_OnEditorManagerCreatedServer && m_Core.Event_OnEditorManagerPing)
			{
				m_Core.Event_OnEditorManagerCreatedServer.Insert(flabby_EditorCreated);
				m_Core.Event_OnEditorManagerPing.Insert(flabby_EditorPing);
				return;
			}
		}
		GetGame().GetCallqueue().CallLater(setEditorScripts, 500, false);
		return;
	}
	
	protected void flabby_EditorCreated(SCR_EditorManagerEntity managerEntity)
	{
		Print(111111, LogLevel.WARNING);
		Print(111111, LogLevel.WARNING);
		Print(111111, LogLevel.WARNING);
		Print(111111, LogLevel.WARNING);
	}
	
	protected void flabby_EditorPing(int reporterID, bool reporterInEditor, SCR_EditableEntityComponent reporterEntity, bool unlimitedOnly, vector position, RplId targetID)
	{
		Print(22222, LogLevel.WARNING);
		Print(22222, LogLevel.WARNING);
		Print(22222, LogLevel.WARNING);
		Print(22222, LogLevel.WARNING);
	}
}

modded class SCR_PingEditorComponent
{
	override protected void ReceivePingOwner(bool unlimitedOnly, vector position, RplId targetID)
	{
		super.ReceivePingOwner(unlimitedOnly, position, targetID);
		
		// Build log 
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_119);
		if (log && flabbyLogger)
		{
			// Add data 
			log.add("function", "SendPingServer");
			log.add("playerBiId", flabby_logger.getPlayerBohemiaId(playerId));
			log.add("playerName", flabby_logger.getPlayerName(playerId));
			log.add("playerFaction", flabby_logger.getPlayerFaction(playerId));
			
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
}


*/