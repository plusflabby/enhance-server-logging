modded class SCR_BaseScoringSystemComponent
{
	override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
		
		if (Replication.IsClient())
		{      
			return;
		}

		GetOnPlayerScoreChanged().Insert(flabby_PlayerScoreChange);
	}
	
	protected void flabby_PlayerScoreChange(int playerId, SCR_ScoreInfo scoreInfo)
	{
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_BaseScoringSystemComponent_101);
		if (log && flabbyLogger)
		{
			// Add data 
			log.add("function", "flabby_PlayerScoreChange");
			log.add("playerId", playerId.ToString());
			log.add("playerBiId", flabby_logger.getPlayerBohemiaId(playerId));
			log.add("playerName", flabby_logger.getPlayerName(playerId));
			log.add("playerFaction", flabby_logger.getPlayerFaction(playerId));
			log.add("playerKills", scoreInfo.m_iKills);
			log.add("playerDeaths", scoreInfo.m_iDeaths);
			log.add("playerSuicides", scoreInfo.m_iSuicides);
			log.add("playerTeamKills", scoreInfo.m_iTeamKills);
			log.add("playerObjectives", scoreInfo.m_iObjectives);
			
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			log.fileToStoreData.Insert(flabby_log_output_file.INFO);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
}