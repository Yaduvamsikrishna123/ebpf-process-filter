#include <linux/bpf.h>
#include <linux/in.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>

char LICENSE[] SEC("license") = "GPL";

SEC("cgroup/connect4")
int block_ports(struct bpf_sock_addr *ctx)
{
    char comm[16];
    bpf_get_current_comm(&comm, sizeof(comm));

    // Change this to your test process name
    const char target[] = "myprocess";

    // Compare process name
    int match = 1;
#pragma unroll
    for (int i = 0; i < sizeof(target) - 1; i++) {
        if (comm[i] != target[i]) {
            match = 0;
            break;
        }
    }

    // If it's NOT our process -> allow
    if (!match)
        return 1;

    // Convert port
    __u16 port = bpf_ntohs(ctx->user_port);

    // Allow only 4040
    if (port == 4040)
        return 1;

    // Block everything else
    return 0;
}
