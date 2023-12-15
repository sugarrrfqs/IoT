touch /etc/systemd/system/WifiScanServer.service
chmod +x /etc/systemd/system/WifiScanServer.service

echo "[Unit]" >> /etc/systemd/system/WifiScanServer.service
echo "Description=Template Settings Service" >> /etc/systemd/system/WifiScanServer.service
echo "After=network.target" >> /etc/systemd/system/WifiScanServer.service
echo "[Service]" >> /etc/systemd/system/WifiScanServer.service
echo "Type=simple" >> /etc/systemd/system/WifiScanServer.service
echo "User=root" >> /etc/systemd/system/WifiScanServer.service
echo "ExecStart=/home/sugar/iot/serv" >> /etc/systemd/system/WifiScanServer.service
echo "TimeoutStartSec=5" >> /etc/systemd/system/WifiScanServer.service
echo "[Install]" >> /etc/systemd/system/WifiScanServer.service
echo "WantedBy=multi-user.target" >> /etc/systemd/system/WifiScanServer.service


touch /etc/systemd/system/WifiScan.service
chmod +x /etc/systemd/system/WifiScan.service

echo "[Unit]" >> /etc/systemd/system/WifiScan.service
echo "Requires=WifiScanServer.service" >> /etc/systemd/system/WifiScan.service
echo "Description=Template Settings Service" >> /etc/systemd/system/WifiScan.service
echo "After=network.target" >> /etc/systemd/system/WifiScan.service
echo "[Service]" >> /etc/systemd/system/WifiScan.service
echo "Type=simple" >> /etc/systemd/system/WifiScan.service
echo "User=root" >> /etc/systemd/system/WifiScan.service
echo "ExecStart=//home/sugar/iot/emb" >> /etc/systemd/system/WifiScan.service
echo "TimeoutStartSec=5" >> /etc/systemd/system/WifiScan.service
echo "[Install]" >> /etc/systemd/system/WifiScan.service
echo "WantedBy=multi-user.target" >> /etc/systemd/system/WifiScan.service 

systemctl daemon-reload
systemctl status WifiScanServer.service
systemctl status WifiScan.service

systemctl enable WifiScanServer.service
systemctl enable WifiScan.service
