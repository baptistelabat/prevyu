prevyu
======

A lamp with drop of water in oil to give rain forecast.
This project was developed during a workshop at Stereolux, Nantes, France.

Dataviz-tangible was used as API for fast development. It is a bit long to download, but provides an API to several other APIs.

INSTALLATION

First setup an internet connection.

To install on raspberry pi (type in a terminal):

sudo apt-get update

sudo apt-get upgrade -y

wget http://nodejs.org/dist/v0.10.24/node-v0.10.24-linux-arm-pi.tar.gz

tar xvfz node-v0.10.24-linux-arm-pi.tar.gz

sudo mv node-v0.10.24-linux-arm-pi /opt/node/

echo 'export PATH="$PATH:/opt/node/bin"' >> ~/.bashrc

source ~/.bashrc

git clone https://github.com/baptistelabat/prevyu.git

cd prevyu

npm install dataviz-tangible

npm install serialport

SETUP

nano server.js

Find 'myAPIKey' and replace it with your api key for forecast.io

To launch automatically at start up, refer to http://www.pihomeserver.fr/2013/05/27/raspberry-pi-home-server-lancer-un-programme-automatiquement-au-demarrage/

sudo mv prevyu.sh /etc/init.d
chmod 755 /etc/init.d/prevyu.sh
sudo update-rc.d prevyu.sh defaults





