// fsoEnumDrv.js – вывод списка подключенных дисков
var fso=WScript.CreateObject("Scripting.FileSystemObject");
var e=new Enumerator(fso.Drives);
var s="";
var n="";
for(;!e.atEnd();e.moveNext())
{
	var x=e.item();
	s=s+x.DriveLetter;
	s+=" - ";
	switch(x.DriveType)
	{
	case 1: 
		n="Отключаемый";
		break;
	case 2: 
		n="Жёсткий";
		break;
	case 3: 
		n="Сетевой";
		break;
	case 4: 
		n="CD-ROM";
		break;
	case 5: 
		n="RAM диск";
		break;
	default:
		n="Unknown";
	}
	s+=n+", ";
	if(x.DriveType==3)
		n=x.ShareName;
	else if (x.IsReady)
		n=x.VolumeName;
	else
		n="[Drive not ready]";
	s+="\""+n+"\"\n";
}
WScript.Echo(s);