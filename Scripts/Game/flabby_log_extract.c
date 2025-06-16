/*
!
!	Client's Data -> Authority / Server -> flabby_log
!
*/

class flabby_extract
{
	// Variables
	private static ref array<ref array<string>> dataThatAreString = new array<ref array<string>>();
	private static ref array<string> addonsLoaded = new array<string>();
	private static ref array<string> addonsAvailable = new array<string>();
	private static ref array<string> addonsAvailableNames = new array<string>();
	
	// Constructor
	void flabby_extract()
	{
		setVariables();
	}
	// De-Constructor
	void ~flabby_extract()
	{
		dataThatAreString.Clear();
		addonsLoaded.Clear();
		addonsAvailable.Clear();
		addonsAvailableNames.Clear();
	}
	
	// Methods / Functions
	// Send event to flabby_logger
	private void eventVariables()
	{
		ArmaReforgerScripted gg = GetGame();
		if (!gg)
		{
			GetGame().GetCallqueue().CallLater(eventVariables, 1300, false); // 1.3s
			return;
		}
		if (!gg.GetPlayerController())
		{
			GetGame().GetCallqueue().CallLater(eventVariables, 1300, false); // 1.3s
			return;
		}
		SCR_BaseGameMode gm = SCR_BaseGameMode.Cast(gg.GetGameMode());
		if (!gm)
		{
			GetGame().GetCallqueue().CallLater(eventVariables, 1300, false); // 1.3s
			return;
		}
		gm.flabby_SendExtract(gg.GetPlayerController().GetPlayerId(), dataThatAreString);
	}
	//! Set the variables =
	private void setVariables()
	{
		int resW = -1;
		int resH = -1;
		System.GetNativeResolution(resW, resH);
		dataThatAreString.Insert({"nativeResolution", string.Format("%1x%2", resW, resH)});
		
		dataThatAreString.Insert({"platform", SCR_Enum.GetEnumName(EPlatform, System.GetPlatform())});
		
		dataThatAreString.Insert({"profileName", System.GetProfileName()});
		
		dataThatAreString.Insert({"machineName", System.GetMachineName()});
		
		dataThatAreString.Insert({"FPS", System.GetFPS().ToString()});
		
		if (GetGame())
		{
			if (GetGame().GetPlayerController())
			{
				dataThatAreString.Insert({"position", GetGame().GetPlayerController().GetOrigin().ToString(true)});
			}
			
			if (GetGame().GetBackendApi())
			{
				if (GetGame().GetBackendApi().GetClientLobby())
				{
					dataThatAreString.Insert({"IP", GetGame().GetBackendApi().GetClientLobby().GetMyIP()});
				}
			}
		}
		
		// Loaded addon guid(s)
		array<string> addonsLoadedTEMP = new array<string>();
		GameProject.GetLoadedAddons(addonsLoadedTEMP);
		addonsLoaded.Clear();
		for (int i = 0; i < addonsLoadedTEMP.Count(); i++)
		{
			addonsLoaded.Insert(string.Format("%1", addonsLoadedTEMP.Get(i)));
		}
		addonsLoadedTEMP.Clear();
		
		// Available addon guid(s)
		array<string> addonsAvailableTEMP = new array<string>();
		GameProject.GetLoadedAddons(addonsAvailableTEMP);
		addonsAvailable.Clear();
		for (int i = 0; i < addonsAvailableTEMP.Count(); i++)
		{
			addonsAvailable.Insert(string.Format("%1", addonsAvailableTEMP.Get(i)));
		}
		addonsAvailableTEMP.Clear();
		
		// Available addon name(s)
		array<string> addonsAvailableNamesTEMP = new array<string>();
		GameProject.GetLoadedAddons(addonsAvailableNamesTEMP);
		addonsAvailableNames.Clear();
		for (int i = 0; i < addonsAvailableNamesTEMP.Count(); i++)
		{
			addonsAvailableNames.Insert(GameProject.GetAddonTitle(addonsAvailableNamesTEMP.Get(i)));
		}
		addonsAvailableNamesTEMP.Clear();
		
		dataThatAreString.Insert({"addonsLoaded", addonsLoaded.ToString()});
		dataThatAreString.Insert({"addonsAvailable", addonsAvailable.ToString()});
		dataThatAreString.Insert({"addonsAvailableNames", addonsAvailableNames.ToString()});
		
		eventVariables();
	}
}

// Global variable -- May have a, future, need for repeating method use
ref flabby_extract flabbyExtract = null;

modded class SCR_BaseGameMode
{
	override protected void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
		
		setGlobalFlabbyExtract();
	}
	
	protected void setGlobalFlabbyExtract() 
	{
		if (Replication.IsRunning() == false)
		{
			GetGame().GetCallqueue().CallLater(setGlobalFlabbyExtract, 1500, false); // 1.5s
			return;
		}
		
		delete flabbyExtract;
		flabbyExtract = new flabby_extract();
	}
	
	void flabby_SendExtract(int playerId, notnull array<ref array<string>> dataThatAreString)
	{
		Rpc(flabby_OnExtract, playerId, dataThatAreString);
	}
	
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void flabby_OnExtract(int playerId, notnull array<ref array<string>> dataThatAreString)
	{
		ref flabby_log log = new flabby_log(flabby_log_identifier.CUSTOM_Extract);
		if (log && flabbyLogger)
		{
			// Add data 
			log.add("function", "flabby_OnExtract");
			log.add("playerId", playerId.ToString());
			log.add("playerBiId", flabby_logger.getPlayerBohemiaId(playerId));
			log.add("playerName", flabby_logger.getPlayerName(playerId));
			log.add("playerFaction", flabby_logger.getPlayerFaction(playerId));
			
			foreach (ref array<string> value : dataThatAreString)
			{
				log.add(value.Get(0), value.Get(1));
			}
			
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			log.fileToStoreData.Insert(flabby_log_output_file.PLAYERS);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
			
			Rpc(flabby_AfterExtract, flabbyLogger.extractPlayerDataSeconds);
			return;
		}
		
		GetGame().GetCallqueue().CallLater(flabby_OnExtract, 3000, false, playerId, dataThatAreString); // 3s
	}
	
	[RplRpc(RplChannel.Reliable, RplRcver.Owner)]
	protected void flabby_AfterExtract(int repeatInSeconds)
	{
		if (repeatInSeconds > 0)
		{
			GetGame().GetCallqueue().CallLater(setGlobalFlabbyExtract, repeatInSeconds * 1000, false);
		}
	}
}