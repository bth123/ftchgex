#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h>

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
                fclose(distro_meta);
            }
        } else if (is_android()) {
            strcpy(os_name, "Android");
        }
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
