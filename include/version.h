#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "18";
	static const char MONTH[] = "04";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.04";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 2;
	static const long MINOR  = 7;
	static const long BUILD  = 4680;
	static const long REVISION  = 25768;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 7917;
	#define RC_FILEVERSION 2,7,4680,25768
	#define RC_FILEVERSION_STRING "2, 7, 4680, 25768\0"
	static const char FULLVERSION_STRING [] = "2.7.4680.25768";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 680;
	

}
#endif //VERSION_H
