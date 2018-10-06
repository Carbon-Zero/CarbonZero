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

git clone https://github.com/Carbon-Zero/CarbonZero.git

cd ./CarbonZero/src

./autogen.sh
./configure
make

Once completed, you can edit the carbonzero.conf file to include the necessary configuration

To start, go back to the /home/CarbonZero/src directory and type
./carbonzerod

More detailed instructions and human assistance can be found at our Discord Channel.
You also have the option of using our one-click install script coming shortly.

For the emission schedule and other statistics, please see the following document https://1drv.ms/x/s!Ak29tYPgxTFlhLsgwyhoSImOp2OMCw

You can also find this information in a simplified format in our Discord.
