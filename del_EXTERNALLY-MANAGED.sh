#!/bin/bash

FILE="/usr/lib/python3.11/EXTERNALLY-MANAGED"
BACKUP="$FILE.old"

if [ -f "$FILE" ]; then
	if [ -f "BACKUP" ]; then
   		sudo rm -f "$FILE.old"
   	fi
   	sudo mv "$FILE" "$FILE".old
   	if [ $? -eq 0 ]; then
   		echo -e "\n[+] Backup de EXTERNALLY-MANAGED crée."
   	else
   		echo -e "\n[-] Erreur lors du changement de nom du fichier EXTERNALLY-MANAGED."
   	fi
fi
