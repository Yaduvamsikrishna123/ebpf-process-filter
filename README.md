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
