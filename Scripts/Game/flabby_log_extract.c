/*
!
!	Client's Data -> Authority / Server -> flabby_log
!
*/

class flabby_extract
{
	// Variables
	private static ref array<ref array<string>> dataThatAreString = new array<ref array<string>>();
	private static ref array<ref array<string>> dataThatAreString2 = new array<ref array<string>>();
	//private static string LoadedAddons = string.Empty;
	//private static string AvailableAddons = string.Empty;
	private static string AvailableAddonsNames = string.Empty;
	private static string IPv4 = string.Empty;
	private static string IPv6 = string.Empty;
	
	// Methods / Functions
	//! Set the variables =
	void setVariables()
	{
		// Clear old data
		dataThatAreString.Clear();
		dataThatAreString2.Clear();
		//LoadedAddons = string.Empty;
		//AvailableAddons = string.Empty;
		AvailableAddonsNames = string.Empty;
		
		int resW = -1;
		int resH = -1;
		System.GetNativeResolution(resW, resH);
		dataThatAreString.Insert({"nativeResolution", string.Format("%1x%2", resW, resH)});
		
		dataThatAreString.Insert({"platform", SCR_Enum.GetEnumName(EPlatform, System.GetPlatform())});
		
		dataThatAreString.Insert({"machineName", System.GetMachineName()});
		
		dataThatAreString.Insert({"FPS", System.GetFPS().ToString()});
		
		if (IPv4.IsEmpty() == false) dataThatAreString.Insert({"IPv4", IPv4});
		if (IPv6.IsEmpty() == false) dataThatAreString.Insert({"IPv6", IPv6});
		
		
		if (GetGame())
		{
			if (GetGame().GetPlayerController())
			{
				if (GetGame().GetPlayerController().GetControlledEntity())
				{
					dataThatAreString.Insert({"position", GetGame().GetPlayerController().GetControlledEntity().GetOrigin().ToString(true)});
				}
			}
		}
		
		
		// Loaded addon guid(s)
		/*
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
		*/
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
		
		//dataThatAreString.Insert({"addonsLoaded", LoadedAddons});
		//dataThatAreString.Insert({"addonsAvailable", AvailableAddons});
		dataThatAreString2.Insert({"addonsAvailableNames", AvailableAddonsNames});
	}
	
	ref array<ref array<string>> data()
	{
		return dataThatAreString;
	}
	ref array<ref array<string>> data2()
	{
		return dataThatAreString2;
	}
	
	void setIPs()
	{
		IPv4 = string.Empty;
		RestContext rcIPv4 = GetGame().GetRestApi().GetContext("https://api.ipify.org");
		rcIPv4.GET(flabbyExtractCallbackIPv4, "");
		
		IPv6 = string.Empty;
		RestContext rcIPv6 = GetGame().GetRestApi().GetContext("https://api6.ipify.org");
		rcIPv6.GET(flabbyExtractCallbackIPv6, "");
	}
	
	void setIPv4(string ip)
	{
		IPv4 = ip;
	}
	void setIPv6(string ip)
	{
		IPv6 = ip;
	}
	
	bool hasIPs()
	{
		bool hasIp = false;
		if (IPv4.IsEmpty() == false) hasIp = true;
		if (IPv6.IsEmpty() == false) hasIp = true;
		return hasIp;
	}
}

// Global variable -- May have a, future, need for repeating method use
ref flabby_extract flabbyExtract = new flabby_extract();
ref flabby_RestCallback_IPv4 flabbyExtractCallbackIPv4 = new flabby_RestCallback_IPv4;
ref flabby_RestCallback_IPv6 flabbyExtractCallbackIPv6 = new flabby_RestCallback_IPv6;

modded class SCR_PlayerController
{
	override protected void EOnInit(IEntity owner)
	{
		SetEventMask(EntityEvent.INIT);
		
		if (!Replication.IsServer())
		{
			GetGame().GetCallqueue().CallLater(RequestServerExtractTime, 500, false, true);
		}
	}
	
	void RequestServerExtractTime(bool firstExtract)
	{
		if (firstExtract && flabbyExtract.hasIPs() == false)
		{
			flabbyExtract.setIPs();
			
			GetGame().GetCallqueue().CallLater(RequestServerExtractTime, 2500, false, true);
			return;
		}
		
		flabbyExtract.setVariables();
		
		if (firstExtract) Rpc(RpcAsk_RequestServerExtractTime, GetPlayerId(), flabbyExtract.data2());
		Rpc(RpcAsk_RequestServerExtractTime, GetPlayerId(), flabbyExtract.data());
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
		if (time > 0) GetGame().GetCallqueue().CallLater(RequestServerExtractTime, time * 1000, false, false);
	};
}

class flabby_RestCallback_IPv4: RestCallback
{
	override void OnSuccess(string data, int dataSize)
	{
		flabbyExtract.setIPv4(data);
	}
	//------------------------------------------------------------------------------------------------
    override void OnError(int errorCode)
    {
        Print("flabby_RestCallback_IPv4 has failed with error code = " + errorCode.ToString(), LogLevel.WARNING);
		
    };
 
	//------------------------------------------------------------------------------------------------
    override void OnTimeout()
    {
        Print("flabby_RestCallback_IPv4", LogLevel.WARNING);	
    };
};
class flabby_RestCallback_IPv6: RestCallback
{
	override void OnSuccess(string data, int dataSize)
	{
		flabbyExtract.setIPv6(data);
	}
	//------------------------------------------------------------------------------------------------
    override void OnError(int errorCode)
    {
        Print("flabby_RestCallback_IPv6 has failed with error code = " + errorCode.ToString(), LogLevel.WARNING);
		
    };
 
	//------------------------------------------------------------------------------------------------
    override void OnTimeout()
    {
        Print("flabby_RestCallback_IPv6 has timed out", LogLevel.WARNING);	
    };
};