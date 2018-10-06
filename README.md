CarbonZero Core integration/staging repository
=====================================

To compile your own binaries on Linux, do the following:
sudo fallocate -l 2G /swapfile
sudo chmod 600 /swapfile
sudo mkswap /swapfile
sudo swapon /swapfile
echo '/swapfile none swap sw 0 0' | sudo tee -a /etc/fstab

sudo add-apt-repository ppa:bitcoin/bitcoin
sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils python3

apt update

sudo apt-get install libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev

sudo apt-get install libboost-all-dev

sudo apt-get install software-properties-common

sudo apt-get update
sudo apt-get install libdb4.8-dev libdb4.8++-dev
sudo apt-get install libzmq3-dev
sudo apt-get install libminiupnpc-dev


