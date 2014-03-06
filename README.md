prevyu
======

A lamp with drop of water in oil to give rain forecast.
This project was developed during a workshop at Stereolux, Nantes, France.

Dataviz-tangible was used as API for fast development. It is a bit long to download, but provides an API to several other APIs.

INSTALLATION

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



