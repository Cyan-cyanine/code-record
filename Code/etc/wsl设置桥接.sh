#!/bin/bash
sudo ip addr del $(ip addr show eth0 | grep 'inet\b' | awk '{print $2}' | head -n 1) dev eth0
sudo ip addr add 192.168.11.150/24 broadcast 192.168.11.255 dev eth0
sudo ip route add 0.0.0.0/0 via 192.168.11.1 dev eth0
