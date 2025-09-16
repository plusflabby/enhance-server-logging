/*
 * flabby_log_chat.c
 *
 * Purpose: Handles logging for chat events and messages in the game.
 * Contains functions for capturing, formatting, and outputting chat logs.
  * Author: https://github.com/plusflabby
 */

modded class SCR_ChatComponent
{
	// RPC: Called on server when a new chat message is sent by a player.
	// Params: msg - message text, channelId - chat channel, senderId - player id.
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void flabby_OnNewMessage(string msg, int channelId, int senderId)
	{
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_ChatComponent_101);
		if (log && flabbyLogger)
		{
			// Add chat message details to log
			log.add("function", "OnNewMessage");
			log.add("msg", msg);
			log.add("channelId", channelId.ToString());
			log.add("senderId", senderId.ToString());
			log.add("playerBiId", flabby_logger.getPlayerBohemiaId(senderId));
			log.add("playerName", flabby_logger.getPlayerName(senderId));

			// Sender Faction
			log.add("senderFaction", flabby_logger.getPlayerFaction(senderId));

			// Mark log for ALL and CHAT files
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			log.fileToStoreData.Insert(flabby_log_output_file.CHAT);
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	
	// Override: Called when a new chat message is sent. Triggers RPC if sender is local player.
	override void OnNewMessage(string msg, int channelId, int senderId)
	{
		super.OnNewMessage(msg, channelId, senderId);

		if (GetGame().GetPlayerController().GetPlayerId() == senderId)
			Rpc(flabby_OnNewMessage, msg, channelId, senderId);
	}
	
	// RPC: Called on server when a private message is sent.
	// Params: msg - message text, senderId - sender player id, receiverId - receiver player id.
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void flabby_OnNewPrivateMessage(string msg, int senderId, int receiverId)
	{
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_ChatComponent_101);
		if (log && flabbyLogger)
		{
			// Add private message details to log
			log.add("function", "OnNewPrivateMessage");
			log.add("msg", msg);
			log.add("receiverId", receiverId.ToString());
			log.add("receiverBiId", flabby_logger.getPlayerBohemiaId(receiverId));
			log.add("receiverName", flabby_logger.getPlayerName(receiverId));

			// Receiver Faction
			log.add("receiverFaction", flabby_logger.getPlayerFaction(receiverId));

			log.add("senderId", senderId.ToString());
			log.add("senderBiId", flabby_logger.getPlayerBohemiaId(senderId));
			log.add("senderName", flabby_logger.getPlayerName(senderId));

			// Sender Faction
			log.add("senderFaction", flabby_logger.getPlayerFaction(senderId));

			// Mark log for ALL and CHAT files
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			log.fileToStoreData.Insert(flabby_log_output_file.CHAT);
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	
	// Override: Called when a new private message is sent. Triggers RPC if sender is local player.
	override void OnNewPrivateMessage(string msg, int senderId, int receiverId)
	{
		super.OnNewPrivateMessage(msg, senderId, receiverId);

		if (GetGame().GetPlayerController().GetPlayerId() == senderId)
			Rpc(flabby_OnNewPrivateMessage, msg, senderId, receiverId);
	}
}