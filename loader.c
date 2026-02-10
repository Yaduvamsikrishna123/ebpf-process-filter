#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <bpf/libbpf.h>
#include <bpf/bpf.h>

int main()
{
    struct bpf_object *obj;
    int prog_fd, cg_fd;

    obj = bpf_object__open_file("block_process_port.bpf.o", NULL);
    if (!obj) {
        printf("Failed to open BPF object\n");
        return 1;
    }

    if (bpf_object__load(obj)) {
        printf("Failed to load BPF object\n");
        return 1;
    }

    prog_fd = bpf_program__fd(bpf_object__find_program_by_name(obj, "block_ports"));

    cg_fd = open("/sys/fs/cgroup", O_DIRECTORY | O_RDONLY);
    if (cg_fd < 0) {
        printf("Failed to open cgroup\n");
        return 1;
    }

    if (bpf_prog_attach(prog_fd, cg_fd, BPF_CGROUP_INET4_CONNECT, 0)) {
        printf("Failed to attach program\n");
        return 1;
    }

    printf("Program attached. Press Ctrl+C to exit.\n");
    while (1) sleep(1);
}
