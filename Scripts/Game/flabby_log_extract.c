/*
!
!	Client's Data -> Authority / Server -> flabby_log
!
*/

class flabby_extract
{
	// Variables
	private static ref array<ref array<string>> dataThatAreString = new array<ref array<string>>();
	private static string LoadedAddons = string.Empty;
	private static string AvailableAddons = string.Empty;
	private static string AvailableAddonsNames = string.Empty;
	
	// Methods / Functions
	//! Set the variables =
	void setVariables()
	{
		// Clear old data
		dataThatAreString.Clear();
		LoadedAddons = string.Empty;
		AvailableAddons = string.Empty;
		AvailableAddonsNames = string.Empty;
		
		int resW = -1;
		int resH = -1;
		System.GetNativeResolution(resW, resH);
		dataThatAreString.Insert({"nativeResolution", string.Format("%1x%2", resW, resH)});
		
		dataThatAreString.Insert({"platform", SCR_Enum.GetEnumName(EPlatform, System.GetPlatform())});
		
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
		LoadedAddons = string.Empty;
		for (int i = 0; i < addonsLoadedTEMP.Count(); i++)
		{
			if (LoadedAddons.IsEmpty()) LoadedAddons = LoadedAddons + string.Format("%1", addonsLoadedTEMP.Get(i));
			else LoadedAddons = LoadedAddons + ", " + string.Format("%1", addonsLoadedTEMP.Get(i));
		}
		addonsLoadedTEMP.Clear();
		
		// Available addon guid(s)
		array<string> addonsAvailableTEMP = new array<string>();
		GameProject.GetLoadedAddons(addonsAvailableTEMP);
		AvailableAddons = string.Empty;
		for (int i = 0; i < addonsAvailableTEMP.Count(); i++)
		{
			if (AvailableAddons.IsEmpty()) AvailableAddons = AvailableAddons + string.Format("%1", addonsAvailableTEMP.Get(i));
			else AvailableAddons = AvailableAddons + ", " + string.Format("%1", addonsAvailableTEMP.Get(i));
		}
		addonsAvailableTEMP.Clear();
		
		// Available addon name(s)
		array<string> addonsAvailableNamesTEMP = new array<string>();
		GameProject.GetLoadedAddons(addonsAvailableNamesTEMP);
		AvailableAddonsNames = string.Empty;
		for (int i = 0; i < addonsAvailableNamesTEMP.Count(); i++)
		{
			if (AvailableAddonsNames.IsEmpty()) AvailableAddonsNames = AvailableAddonsNames + GameProject.GetAddonTitle(addonsAvailableNamesTEMP.Get(i));
			else AvailableAddonsNames = AvailableAddonsNames + ", "  + GameProject.GetAddonTitle(addonsAvailableNamesTEMP.Get(i));
		}
		addonsAvailableNamesTEMP.Clear();
		
		dataThatAreString.Insert({"addonsLoaded", LoadedAddons});
		dataThatAreString.Insert({"addonsAvailable", AvailableAddons});
		dataThatAreString.Insert({"addonsAvailableNames", AvailableAddonsNames});
	}
	
	ref array<ref array<string>> data()
	{
		return dataThatAreString;
	}
}

// Global variable -- May have a, future, need for repeating method use
ref flabby_extract flabbyExtract = new flabby_extract();

modded class SCR_PlayerController
{
	override protected void EOnInit(IEntity owner)
	{
		SetEventMask(EntityEvent.INIT);
		
		if (!Replication.IsServer())
		{
			GetGame().GetCallqueue().CallLater(RequestServerExtractTime, 500, false);
		}
	}
	
	void RequestServerExtractTime()
	{
		flabbyExtract.setVariables();
		
		Rpc(RpcAsk_RequestServerExtractTime, GetPlayerId() ,flabbyExtract.data());
	};

	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	void RpcAsk_RequestServerExtractTime(int playerId, notnull array<ref array<string>> extractData)
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
			
			foreach (ref array<string> value : extractData)
			{
				log.add(value.Get(0), value.Get(1));
			}
			
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			log.fileToStoreData.Insert(flabby_log_output_file.PLAYERS);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
		
		if (flabbyLogger) Rpc(RpcDo_RequestServerExtractTime, flabbyLogger.extractPlayerDataSeconds);
		else Rpc(RpcDo_RequestServerExtractTime, 0);
	};

	[RplRpc(RplChannel.Reliable, RplRcver.Owner)]
	void RpcDo_RequestServerExtractTime(int time) 
	{
		//GetGame().GetCallqueue().Remove(RequestServerExtractTime);
		if (time > 0) GetGame().GetCallqueue().CallLater(RequestServerExtractTime, time * 1000, false);
	};
}