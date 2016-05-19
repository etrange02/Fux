#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "15";
	static const char MONTH[] = "05";
	static const char YEAR[] = "2016";
	static const char UBUNTU_VERSION_STYLE[] =  "16.05";
	
	//Software Status
	static const char STATUS[] =  "Beta";
	static const char STATUS_SHORT[] =  "b";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 9;
	static const long BUILD  = 6612;
	static const long REVISION  = 36489;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 10624;
	#define RC_FILEVERSION 1,9,6612,36489
	#define RC_FILEVERSION_STRING "1, 9, 6612, 36489\0"
	static const char FULLVERSION_STRING [] = "1.9.6612.36489";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 612;
	

}
#endif //VERSION_H
