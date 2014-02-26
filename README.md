prevyu
======

A lamp with drop of water in oil to give rain forecast

To install on raspberry pi (in progress):

sudo apt-get update
sudo apt-get upgrade -y

wget http://nodejs.org/dist/v0.10.24/node-v0.10.24-linux-arm-pi.tar.gz
tar xvfz node-v0.10.24-linux-arm-pi.tar.gz
sudo mv node-v0.10.24-linux-arm-pi /opt/node/

echo 'export PATH="$PATH:/opt/node/bin"' >> ~/.bashrc
source ~/.bashrc

npm config set registry http://registry.npmjs.org/

mkdir prevyu
cd prevyu
npm install serialport
npm install dataviz-tangible # not working for forecast so far...

