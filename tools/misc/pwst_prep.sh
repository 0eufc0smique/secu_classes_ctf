#!/usr/bin/zsh

cd
sudo timedatectl set-timezone Europe/Paris
sudo apt update && sudo apt autoremove -y && sudo apt full-upgrade -y && sudo apt install vim zsh net-tools konsole curl seclists zaproxy python3-pip -y
sudo update-alternatives --config x-terminal-emulator
echo "####################################### INSTALLING BRAVE ######################################"
sudo curl -fsSLo /usr/share/keyrings/brave-browser-archive-keyring.gpg https://brave-browser-apt-release.s3.brave.com/brave-browser-archive-keyring.gpg
echo "deb [signed-by=/usr/share/keyrings/brave-browser-archive-keyring.gpg] https://brave-browser-apt-release.s3.brave.com/ stable main"|sudo tee /etc/apt/sources.list.d/brave-browser-release.list
sudo apt update && sudo apt install brave-browser -y

#prep for RUST:
echo "###################################### PREPARING FOR RUST ######################################"
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh # choix 1
cargo install feroxbuster && feroxbuster --version
sudo apt update && sudo apt full-upgrade -y
mkdir Scripts && cd Scripts && git clone https://github.com/mttaggart/shell-setup && cd shell-setup && ./setup.sh && cd

#install ohmyzsh, config vim and download pwst-ressources
echo "###################################### INSTALLING OHMYZSH, SETTING UP VIM AND CLONING RESSOURCES ######################################"
git clone https://github.com/gobelinor/vimconfig.git && cd vimconfig && sudo chmod +x install_plugins.sh && ./install_plugins.sh && cd ../ && rm -rf vimconfig/
git clone https://github.com/mttaggart/pwst-resources.git
sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
echo -e "alias llah='ls -lahF'\nalias lah='ls -ahF'\nalias llh='ls -lhF'\nalias lh='ls -hF'\nalias lla='ls -laF'\nalias la='ls -aF'\nalias ll='ls -lF'\nalias l='ls -CF'\nalias p='python3'\nalias upgradz='sudo apt update && sudo apt full-upgrade && sudo apt autoremove -y && sudo apt autoclean -y'" >> ~/.zshrc && source ~/.zshrc && cd
