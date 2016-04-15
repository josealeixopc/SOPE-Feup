#include <stdio.h>
/*For directory related functions (DIRectory ENTries)*/
#include <dirent.h>	

/*stat function includes*/
/*See: http://linux.die.net/man/2/stat*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

/*for time functions and structs*/
#include <time.h>


/*
 * Struct that'll be used to store regular files' properties. 
 * */
typedef struct 
{
	char* name;			// file's name
	long long size;		// file's size in bytes
	unsigned long mode;	// file permissions in decimal representation
	time_t lastMDate;	// last file modification date in time_t struct
	char* absolutePath;	// file's absolute path in the system
}RFile;

/*TODO: TO GET FILE INFORMATION USE STAT() FUNCTION*/

/* Saves a file's info to a RFile struct. DON'T FORGET TO FREE MEMORY AFTER USING IT! @see RFile.
 * */
RFile* getInfoFromFile (char* filePath)
{
	struct stat s;		// get file data
	RFile* file = (RFile*)malloc(sizeof(RFile));	// store file data
	
	stat (filePath, &s);
	
	file->size = (long long) s.st_size;
	file->mode = (unsigned long) (s.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
	file->lastMDate = s.st_mtime;	
	file->absolutePath = filePath;
	
	return file;
}

/* Converts RFile data to a string that can be saved in a .txt file.
 * */
char* rFileToString(RFile file)
{
	char* ret = (char*)malloc(sizeof(char));
	
	sprintf(ret, "%s %lld %lo %s %s", file.name, file.size, file.mode, file.absolutePath, ctime(&file.lastMDate));	// %lo prints in long octal
	
	return ret;
}

/**
 * Saves to a text file the name of the regular files present in the directory.
 */
int writeFilesFromDir(char* directory){
	DIR *dir;
	struct dirent *ent;
	
	if ((dir = opendir (directory)) != NULL) 
	{
		FILE *files;

		files = fopen("files.txt", "w");	// opens or creates for writing only
	
		/*Write all file names to a file.*/
		while ((ent = readdir (dir)) != NULL) 
		{
			char* fileName = ent->d_name;

			fputs(fileName, files);
			fputs("\n", files);
		}
		
		fclose(files);
			
		closedir(dir);
	} else {
		/* could not open directory */
		perror ("");
		return -1;
	}

	return 0;
}


int main()
{
	char* testDirectory = "/usr/users2/mieic2014/up201403526/Downloads";
	char* filePath = "/home/jazz/Desktop/SOPE-Feup/Trabalho 1/rmdup.c";
	
	time_t t = time(NULL);
	
	RFile* testfile = getInfoFromFile(filePath);
	
	//writeFilesFromDir(testDirectory);
	
	char* c = rFileToString(*testfile);	// since the pointer becomes a local variable in this main() function, it doesn't need to be freed (???) -> if freed gives error
	
	printf ("%s", c);
	
	
}
