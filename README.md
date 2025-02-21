Take control of your server’s data like never before with Enhance Logging, a powerful, customizable logging system designed to elevate your server management experience.

# Amra Reforger Mod Workshop
[Arma Reforger Workshop](https://reforger.armaplatform.com/workshop/6316335D6A19E51C)

# Description
**Introducing Enhance Logging by "flabby" for Arma Reforger**  

Take control of your server’s data like never before with Enhance Logging, a powerful, customizable logging system designed to elevate your server management experience.  

### **Key Features:**  
- **Detailed & Persistent Logs**: Track every critical event with logs stored locally as `.json` files or online (based on downloads).  
- **Categorized Data**: Separate logs into `debug`, `info`, `default`, and `error` for crystal-clear analysis.  
- **Customizable Formats**: Choose your style—compact, normal, or rich—tailored to your workflow.  
- **Developer Tools**: Access essential debugging data like system/server time, with seamless format changes via in-game commands.  

### **Designed for Power Users**  
Whether you’re a developer or a server operator, Enhance Logging is your solution for reliable tracking. The system currently focuses on `SCR_GameMode` logs, with planned online searchability if enough downloads are reached!  

### **Folder Structure Made Simple**  
Your logs are neatly organized in `ServerProfile/flabby/logs/YEAR/MONTH/DAY`. Open and format them effortlessly with tools like VSCode or your preferred methods.  

### **Easy-to-Use Commands:**  
- **#loghelp**: List all available commands.  
- **#log format [COMPACT|NORMAL|RICH]**: Adjust log detail level.  
- **#log category [DEBUG|INFO|ALL] (WIP)**: Fine-tune log categories.  
- **#log extension [JSON|LOG|TXT]**: Choose your file format.  

**Examples:**  
- `#log format RICH`  
- `#log category ALL` *(WIP)*  
- `#log extension TXT`  

**Download Enhance Logging now and redefine your Arma Reforger experience!**

Questions, Suggestions, and Issues @ [https://www.flabby.dev/discord](https://www.flabby.dev/discord)

# Source code is NOT Public

## ARMA PUBLIC LICENSE NO DERIVATIVES (APL-ND) [LINK](https://www.bohemia.net/community/licenses/arma-public-license-nd)


# Version 1.3.0
- Cache bohemia id and name
- Include player's name and bohemia id for logs

# Version 1.3.5
- Fix class flabby_logger
- Fix function removeOldIdentifiers

# Version 1.3.6
- Add identifiable name to each log

# Version 1.4.0
- Expose logs though a function
- Add public ScriptInvoker for modders

# Version 1.5.0
- Logging chat messages