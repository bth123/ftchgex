#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h>

const char logo_padding = 4;

void read_logo(char* path, char* out) {
	FILE* logo_file = fopen(path, "r");
	char[72] buf;
	
	fclose(logo_file);
}

int count_termux_packages() {
	FILE *status_list = fopen("/data/data/com.termux/files/usr/var/lib/dpkg/status", "r");
	if (status_list == NULL) {
		return -1;
	}

	int count = 0;
	char buf[256];
	if (fscanf(status_list, "Status: install ok installed", buf)) {
		count++;
	}
}


char is_android(void) {
	return getenv("ANDROID_ROOT") != NULL;
}

void get_sysname(char* os_name) {
    struct utsname buffer;

    if (uname(&buffer) != 0) {
        strcpy(os_name, "Unknown");
        return;
    }

    if (strcmp(buffer.sysname, "Linux") == 0) {
        strcpy(os_name, buffer.sysname);

        FILE* distro_meta = fopen("/etc/os-release", "r");
        if (distro_meta != NULL) {
            char buf[72];
            if (fscanf(distro_meta, "NAME=\"%s\"", buf) == 1) {
                strcpy(os_name, buf);
            }
        } else if (is_android()) {
            strcpy(os_name, "Android");
        }
        fclose(distro_meta);
    }
}

int main() {
    struct utsname buffer;

    if (uname(&buffer) != 0) {
        perror("uname system call failed");
        return 0;
    }

    char os_name[72];
    get_sysname(os_name);

    printf("OS Name:    %s\n", os_name);
    printf("Release:    %s\n", buffer.release);
    printf("Version:    %s\n", buffer.version);
    printf("Hardware:   %s\n", buffer.machine);

    return 0;
}
