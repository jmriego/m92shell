#!/bin/ash

PATH="/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/opt/onyx/arm/bin"

mkdir -p /app/.ssh
chmod 700 /app/.ssh
if [ ! -f /app/.ssh/id_rsa ]; then
 ssh-keygen -t rsa -N "" -f /app/.ssh/id_rsa
 cp /app/.ssh/id_rsa.pub /media/flash/
 echo Please install the /media/flash/id_rsa.pub to ledming.lan
 exit 1
fi

ssh calibre@ledming.lan sudo /etc/init.d/calibre library
rsync -v -a --delete --no-perms --no-owner --no-group --size-only "ledming.lan:\(Library\)" /media/flash/
echo
sleep 1
echo Done!
