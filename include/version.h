#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "14";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.01";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 2;
	static const long MINOR  = 6;
	static const long BUILD  = 3475;
	static const long REVISION  = 19127;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 6345;
	#define RC_FILEVERSION 2,6,3475,19127
	#define RC_FILEVERSION_STRING "2, 6, 3475, 19127\0"
	static const char FULLVERSION_STRING [] = "2.6.3475.19127";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 475;
	

}
#endif //VERSION_H
