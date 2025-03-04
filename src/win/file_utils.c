#include <win/lightbase/file_utils.h>


void make_directory(const char *directory)
{
	CreateDirectoryA(directory, NULL);
}

char **get_filenames(const char *directory, int *count)
{
	setlocale(LC_ALL, "en_US.UTF-8");
	DIR *dir;
	struct dirent *ent;
	int i = 0;
	char **filenames = NULL;

	dir = opendir(directory);
	if (dir == NULL) {
		make_directory(directory);
		*count = 0;
		return filenames;
	}

	while ((ent = readdir(dir)) != NULL) {
		if (ent->d_type == DT_REG && ent->d_name[0] != '.') {
			char *filename = malloc(sizeof(ent->d_name) + 1);
			strcpy(filename, ent->d_name);

			filenames = realloc(filenames, sizeof(char *) * (i + 1));
			filenames[i] = filename;
			i++;
		}
	}

	closedir(dir);

	*count = i;
	return filenames;
}


char **get_foldernames(const char *directory, int *count)
{
	setlocale(LC_ALL, "en_US.UTF-8");
	DIR *dir;
	struct dirent *ent;
	int i = 0;
	char **foldernames = NULL;

	dir = opendir(directory);
	if (dir == NULL) {
		make_directory(directory);
		*count = 0;
		return foldernames;
	}

	while ((ent = readdir(dir)) != NULL) {
		if (ent->d_type == DT_DIR && ent->d_name[0] != '.') {
			char *foldername = malloc(sizeof(ent->d_name) + 1);
			strcpy(foldername, ent->d_name);

			foldernames = realloc(foldernames, sizeof(char *) * (i + 1));
			foldernames[i] = foldername;
			i++;
		}
	}

	closedir(dir);

	*count = i;
	return foldernames;
}


void free_filenames(char **filenames, int count)
{
	for (int i = 0; i < count; i++) {
		free(filenames[i]);
	}
	free(filenames);
}


void free_foldernames(char **foldernames, int count)
{
	for (int i = 0; i < count; i++) {
		free(foldernames[i]);
	}
	free(foldernames);
}


bool is_file_exist(const char *path)
{
	FILE *fp;
	fopen_s(&fp, path, "rb");
	if (fp) {
		fclose(fp);
		return true;
	} else {
		return false;
	}
}
