# Amra Reforger Mod Workshop
[Arma Reforger Workshop](https://reforger.armaplatform.com/workshop/6316335D6A19E51C)

# Description
**Introducing Enhance Logging by "flabby" for Arma Reforger**  

Take control of your server’s data like never before with Enhance Logging, a powerful, customizable logging system designed to elevate your server management experience.  

![](./thumbnail.png)

### **Latest Features**
- **Custom Logs & Webhooks**: Create your own logs and webhooks for advanced integrations.
- **Expanded Kill & Connection Data**: More detailed information for kills, connections, and deconstruction events, including player faction and IP addresses (IPv4/IPv6).
- **Game Start Event Webhook**: Trigger webhooks on game start for automation.
- **Score Change Tracking**: Monitor changes in player scores.
- **Structure Deletion Logging**: Track when structures are deleted.
- **Weapon Details in Kill Logs**: Weapon name and type included in kill events.
- **Configurable Logging**: Enable/disable file and console logging with commands (`#log file`, `#log print`).
- **Rich Data Format**: All logs now include timestamps and more context.
- **Discord Webhook Support**: Send logs directly to Discord channels.
- **Configuration File**: Easily manage settings with a formatted config file.
- **Documentation Improvements**: Enhanced documentation for easier setup and usage.

### **Folder Structure Made Simple**  
Your logs are neatly organized in `ServerProfile/flabby/YEAR/MONTH/DAY`. Open and format them effortlessly with tools like VSCode or your preferred methods.  

### **Easy-to-Use Commands:**  
- **#loghelp**: List all available commands.  
- **#log file [TRUE|FALSE]**: Control log to files.  
- **#log print [TRUE|FALSE]**: Control log to server console.  
- **#log extension [JSON|LOG|TXT]**: Choose your file format.  

**Examples:**  
- `#loghelp`  
- `#log file false`  
- `#log print true`
- `#log extension json`  

**Download Enhance Logging now and redefine your Arma Reforger experience!**

Questions, Suggestions, and Issues @ [https://www.flabby.dev/discord](https://www.flabby.dev/discord)

# Version 1.3.0
## Summary: Introduced player identification in logs, including caching of Bohemia ID and player names for better tracking.
- Cache bohemia id and name
- Include player's name and bohemia id for logs

# Version 1.3.5
## Summary: Bug fixes for logger class and identifier removal, improving reliability.
- Fix class flabby_logger
- Fix function removeOldIdentifiers

# Version 1.3.6
## Summary: Each log entry now includes a unique, identifiable name for easier reference.
- Add identifiable name to each log

# Version 1.4.0
## Summary: Added public functions and ScriptInvoker for modders to access and use logs programmatically.
- Expose logs though a function
- Add public ScriptInvoker for modders

# Version 1.5.0
## Summary: Chat messages are now logged for improved communication tracking.
- Logging chat messages

# Version 1.6.0
# Summary: Added faction data to kill logs, Discord webhook support, and a formatted configuration file for easier setup.
- Add data point to killing (factions of each side)
- Discord Webhook(s)
- Configuration File (formatted / pretty)

# Version 1.7.0
## Summary: Expanded data points, event-specific webhooks, server name in logs, and new options to control print logging and message faction tracking.
- More data pointsGrab the data from the client
- Specific webhook for events
- Add server name in config to be added to all logs
- Command and config value to disable print log
- Add faction to message logs

# Version 1.8.0
## Summary: Kill logs now include weapon name and type for more detailed event tracking.
- Add weapon name and type to kills

# Version 1.9.0
## Summary: Structure deletion events are now logged for improved server management.
- Add structure deletion log

# Version 2.0.0
## Summary: Major update with new logging commands, enhanced data, improved webhook features, and refined log formatting and control options.
- Add #log print true command to disable printing to server console
- Add #log file true command to disable making log files
- Remove #log category ALL so every log is logged
- Remove #log format RICH to show all data for logs
- Add time to every log
- Add repeating option for class flabby_extract
- More data
- Webhook enhancements
- Disable ControllableDestroyed log as it's same as kill log
- Change command #loghelp for new and removed commands

# Version 2.1.0
## Summary: Added more detailed kill, connection, and deconstruction data, score change tracking, game start webhook, and IP address extraction.
- Kill data additions
- Connection data additions
- Deconstruction - Add player faction
- Change of player scores
- Game Start Event Webhook
- Add IPv4 and IPv6 to extracts

# Version 2.2.0
## Summary: Documentation improvements and support for custom logs and webhooks for advanced customization.
- Documentation
- Enable making custom logs
- Enable making custom webhooks