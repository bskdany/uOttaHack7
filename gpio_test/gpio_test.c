#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define GPIO_DEVICE "/dev/gpio/16"

int write_to_gpio(const char *device, const char *value) {
    int fd = open(device, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open GPIO device");
        return -1;
    }

    // Write the value to the GPIO device
    if (write(fd, value, strlen(value)) < 0) {
        perror("Failed to write to GPIO device");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

int main() {
    if (write_to_gpio(GPIO_DEVICE, "out") < 0) {
        return 1;
    }
    printf("GPIO direction set to 'out'\n");

    while (1) {
        if (write_to_gpio(GPIO_DEVICE, "on") < 0) {
            return 1;
        }
        printf("GPIO set to 'on'\n");

        sleep(1);

        if (write_to_gpio(GPIO_DEVICE, "off") < 0) {
            return 1;
        }
        printf("GPIO set to 'off'\n");

        sleep(1);
    }

    return 0;
}
