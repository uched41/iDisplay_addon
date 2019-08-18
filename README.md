## Steps
cd ~
git clone https://github.com/uched41/iDisplay_addon.git
cd node_js
export LD_LIBRARY_PATH=/home/$USER/node_js/idisplay_addon/lib
npm install
npm run build 
node index.js