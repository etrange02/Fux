#include "FileRenamingThread.h"

using namespace tools::thread;

FileRenamingThread::FileRenamingThread(const wxArrayString& files) :
    m_files(files)
{
    //ctor
}

FileRenamingThread::~FileRenamingThread()
{
    //dtor
}

void FileRenamingThread::process()
{

}

