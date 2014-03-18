#include "Utility.h"
#include "time.h" 
#include <io.h>
#include "GameConst.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

vector<string> Utility::iterateFolder(const char* path)
{
	vector<string> vecResult;

	struct   _finddata_t   filefind; 
	string   curr = string(path) + "\\*.* "; 
	int   done = 0, i, handle; 
	if((handle = _findfirst(curr.c_str(),&filefind)) == -1)
		return vecResult; 
	while(!(done = _findnext(handle, &filefind))) 
	{ 
		if(!strcmp(filefind.name, ".."))
			continue; 

		if   ((_A_SUBDIR == filefind.attrib)) 
		{
			continue;
// 			curr= string(path) + "\\" + filefind.name; 
// 			iterateFolder(curr.c_str(), target, selector); 
		} 
		else
		{ 
			string str = filefind.name;
			vecResult.push_back(str);
		} 
	}
	_findclose(handle);

	return vecResult;
}

void Utility::rateThisApp()
{

}