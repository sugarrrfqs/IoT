systemctl disable WifiScanServer.service
systemctl disable WifiScan.service
systemctl daemon-reload

rm /etc/systemd/system/WifiScanServer.service
rm /etc/systemd/system/WifiScan.service
