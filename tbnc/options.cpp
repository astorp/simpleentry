#include "options.h"


Options::Options()
{
	siteip = "";
	siteport = 0;
	idntcmd = 1;
	idnt = 1;
	listenport = 0;
	listenip = "";
	connectip = "";
	buffersize = 0;
	pidfile = "";
	sndrcvbufsize = 0;
	string certpath = "";
	ipfordata = 0;
	addtopasvport = 0;
	delay = 5;
	retrycount = 15;
	checkForIp = 1;
	logFile = "";
	logToScreen=0;
}

void Options::GetOptional(void)
{
	// optional options
	config.GetString("listen_ip",listenip);
	config.GetInt("idnt_command",idntcmd);
	config.GetInt("idnt_request",idnt);	
	config.GetString("connect_ip",connectip);
	config.GetInt("buffersize",buffersize);
	config.GetString("pidfile",pidfile);
	config.GetInt("sndrcvbufsize",sndrcvbufsize);
	config.GetString("entries",entries);
	config.GetInt("ipfordata",ipfordata);
	config.GetInt("addtopasvport",addtopasvport);
	config.GetInt("delay",delay);
	config.GetInt("retrycount",retrycount);
	config.GetString("natpasvip",natpasvip);
	config.GetInt("checkforip", checkForIp);
	if(entries != "")
	{
		split(entrylist,entries,',',false);
	}
	config.GetString("logFile", logFile);
	config.GetInt("logToScreen", logToScreen);
}

bool Options::GetRequired(void)
{
	// required options
	bool found = true;
	if(!config.GetString("site_ip",siteip)) found = false;
	if(!config.GetInt("site_port",siteport)) found = false;
	if(!config.GetInt("listen_port",listenport)) found = false;
	if(!config.GetString("cert_path",certpath)) found = false;	
	return found;
}

void Options::Log(string msg)
{
#ifdef _DEBUG
	if(logToScreen)
	{
		cout << msg << "\r\n";
	}
	if(logFile != "")
	{
		lock.lock();
		FILE * file;
		file = fopen(logFile.c_str(), "a");
		if (file != NULL)
		{
			fputs(msg.c_str(), file);
			fclose(file);
		}
		lock.unlock();
	}
#endif
}
