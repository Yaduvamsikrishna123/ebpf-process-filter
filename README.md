# eBPF Process-Based Port Filter

This project demonstrates process-aware network filtering using eBPF cgroup hooks.

## Features
- Allows traffic only on port 4040 for a specific process
- Blocks all other ports for that process
- Does not affect other applications

## Technologies
- eBPF
- libbpf
- Linux cgroups
# Process-Aware Network Filtering using eBPF

This project demonstrates syscall-level network enforcement using eBPF and Linux cgroup hooks.

It restricts outbound connections for a specific process, allowing traffic only on a defined TCP port while blocking all other ports.

## 🚀 Features
- Process-based network filtering
- Syscall interception using `BPF_CGROUP_INET4_CONNECT`
- Kernel-level enforcement (not firewall-based)
- Lightweight and efficient security control

## 🧠 How It Works
The eBPF program attaches to the cgroup connect hook and:

1. Detects the calling process name
2. Checks the destination port
3. Allows only port **4040**
4. Blocks all other outbound connections for that process

## 🛠 Tech Stack
- eBPF
- libbpf
- Linux Kernel (6.x)
- C
- cgroups

## ▶️ Build & Run

```bash
make
sudo ./loader

##✅ Test

Create a test process:

cp /bin/nc myprocess
chmod +x myprocess


Blocked connection:

./myprocess -vz 1.1.1.1 80


Expected:

Operation not permitted


Allowed for other processes:

nc -vz 1.1.1.1 80

##🎯 Use Cases

Runtime security agents

Container sandboxing

Zero-trust networking

Process-level firewall policies
