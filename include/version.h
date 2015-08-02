#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "03";
	static const char MONTH[] = "08";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.08";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 8;
	static const long BUILD  = 5664;
	static const long REVISION  = 31276;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 9245;
	#define RC_FILEVERSION 1,8,5664,31276
	#define RC_FILEVERSION_STRING "1, 8, 5664, 31276\0"
	static const char FULLVERSION_STRING [] = "1.8.5664.31276";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 664;
	

}
#endif //VERSION_H
