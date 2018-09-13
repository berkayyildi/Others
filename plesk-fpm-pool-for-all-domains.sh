#!/bin/bash

printf 'Islem Tamamlanana kadar lutfen bekleyin...\n';

for directory in /var/www/vhosts/system/*/conf/; do 

printf '[php-fpm-pool-settings]
pm = dynamic 
pm.max_children = 250 
pm.start_servers = 10 
pm.min_spare_servers = 10 
pm.max_spare_servers = 60 
pm.max_requests = 2048 
pm.status_path = /status ' > $directory/php.ini;

done

/usr/local/psa/bin/php_settings -u

#clear

printf 'Islem Tamamlandi\n'
