#!/bin/ash

PATH="/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/opt/onyx/arm/bin"

ssh ledming.lan sudo /etc/init.d/calibre library
rsync -v -a --delete --no-perms --no-owner --no-group --size-only "ledming.lan:\(Library\)" /media/flash/
echo
sleep 1
echo Done!
