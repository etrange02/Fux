#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "23";
	static const char MONTH[] = "07";
	static const char YEAR[] = "2016";
	static const char UBUNTU_VERSION_STYLE[] =  "16.07";
	
	//Software Status
	static const char STATUS[] =  "Beta";
	static const char STATUS_SHORT[] =  "b";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 9;
	static const long BUILD  = 6647;
	static const long REVISION  = 36698;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 10679;
	#define RC_FILEVERSION 1,9,6647,36698
	#define RC_FILEVERSION_STRING "1, 9, 6647, 36698\0"
	static const char FULLVERSION_STRING [] = "1.9.6647.36698";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 647;
	

}
#endif //VERSION_H
