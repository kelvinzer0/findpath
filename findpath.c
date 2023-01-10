#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define MAX_PATH_LENGTH 256

// Fungsi untuk mencari file dalam direktori dan subdirektori
void findpath(const char *dirname, const char *search)
{
    // Membuka direktori
    DIR *dir = opendir(dirname);
    if (dir == NULL)
    {
        perror("Error opening directory");
        return;
    }

    // Iterasi melalui semua file dan folder dalam direktori
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        char path[MAX_PATH_LENGTH];
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);

        if (entry->d_type == DT_DIR)
        {
            // Jika direktori, rekursif mencari file dalam direktori tersebut
            findpath(path, search);
        }
        else
        {
            // Jika file, periksa apakah nama file cocok dengan yang dicari
            if (strstr(entry->d_name, search) != NULL)
            {
                printf("%s\n", path);
            }
        }
    }

    // Menutup direktori setelah selesai
    closedir(dir);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s [directory] [file]\n", argv[0]);
        return 1;
    }

    // Memanggil fungsi untuk mencari file
    findpath(argv[1], argv[2]);

    return 0;
}
