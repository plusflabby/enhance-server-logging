/*
!
!	Client's Data -> Authority / Server -> flabby_log
!
*/

class flabby_extract
{
	// Variables
	private static string platform = string.Empty;
	private static string nativeXresolution = string.Empty;
	private static string profileName = string.Empty;
	private static string machineName = string.Empty;
	private static string IP = string.Empty;
	private static ref array<string> addons = new array<string>();
	
	// Constructor
	void flabby_extract()
	{
		setVariables();
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
		gm.flabby_SendExtract(gg.GetPlayerController().GetPlayerId(), platform, nativeXresolution, profileName, machineName, IP, addons);
	}
	//! Set the variables =
	private void setVariables()
	{
		platform = SCR_Enum.GetEnumName(EPlatform, System.GetPlatform());
		
		int resW = -1;
		int resH = -1;
		System.GetNativeResolution(resW, resH);
		nativeXresolution = string.Format("%1x%2", resW, resH);
		
		profileName = System.GetProfileName();
		
		machineName = System.GetMachineName();
		
		IP = GetGame().GetBackendApi().GetClientLobby().GetMyIP();
		
		addons.Clear();
		array<string> addonOutput = new array<string>();
		GameProject.GetLoadedAddons(addonOutput);
		addons.InsertAll(addonOutput);
		
		eventVariables();
	}
}

// Global variable -- May have a, future, need for repeating method use
//ref flabby_extract flabbyExtract = null;

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
		
		new flabby_extract();
	}
	
	void flabby_SendExtract(int playerId, string platform, string nativeXresolution, string profileName, string machineName, string IP, notnull array<string> addons)
	{
		Rpc(flabby_OnExtract, playerId, platform, nativeXresolution, profileName, machineName, IP, addons);
	}
	
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void flabby_OnExtract(int playerId, string platform, string nativeXresolution, string profileName, string machineName, string IP, notnull array<string> addons)
	{
		ref flabby_log log = new flabby_log(flabby_log_identifier.CUSTOM_Extract);
		if (log && flabbyLogger)
		{
			// Add data 
			log.add("function", "flabby_OnExtract");
			log.add("platform", platform);
			log.add("nativeXresolution", nativeXresolution);
			log.add("profileName", profileName);
			log.add("machineName", machineName);
			log.add("IP", IP);
			log.add("addons", addons.ToString());
			log.add("playerBiId", flabby_logger.getPlayerBohemiaId(playerId));
			log.add("playerName", flabby_logger.getPlayerName(playerId));
			
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			log.fileToStoreData.Insert(flabby_log_output_file.PLAYERS);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
			
			Rpc(flabby_AfterExtract, flabbyLogger.extractPlayerDataSeconds);
			return;
		}
		
		GetGame().GetCallqueue().CallLater(flabby_OnExtract, 3000, false, playerId, platform, nativeXresolution, profileName, machineName, IP, addons); // 3s
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