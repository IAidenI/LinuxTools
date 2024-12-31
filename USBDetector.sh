#!/bin/bash

# Fichiers sysfs pour les informations USB
USB_Info="/sys/kernel/usb_monitor/info"
USB_Connect="/sys/kernel/usb_monitor/connected"

# Vérifie l'existence des fichiers sysfs
if [ ! -e "$USB_Info" ] || [ ! -e "$USB_Connect" ]; then
    notify-send -u critical "Erreur" "Veillez lancer le kernel module associé."
    exit 1
fi

# Fonction pour récupérer le dernier périphérique connecté
get_last_vendor() {
    # Recherche le dernier bloc de périphérique en lisant à l'envers
    LAST_DEVICE=$(tac "$USB_Info" | awk '/Périphérique/ {block = $0} /Vendor/ {print block; print; exit}')

    # Récupère uniquement la partie après 'Name ='
    VENDOR_NAME=$(echo "$LAST_DEVICE" | grep "Vendor" | sed -n 's/.*Name =\(.*\)/\1/p' | sed 's/^ *//g' | sed 's/ *$//g')

    # Si le nom est vide, remplacer par "Inconnu"
    [ -z "$VENDOR_NAME" ] && VENDOR_NAME="Inconnu"

    # Retourne uniquement le nom extrait
    echo "$VENDOR_NAME"
}

# Notification d'initialisation
notify-send -u normal "USB Detector" "USB Detector chargé correctement."

# Boucle infinie pour surveiller les modifications
while true; do
    # Attend les modifications sur le fichier connecté
    inotifywait -e modify,attrib "$USB_Connect" > /dev/null 2>&1

    # Vérifie l'état actuel
    STATUS=$(cat "$USB_Connect")
    if [ "$STATUS" == "CONNECTED" ]; then
        # Récupère le nom du dernier périphérique connecté
        VENDOR_NAME=$(get_last_vendor)
        notify-send -u normal "USB Detector" "$VENDOR_NAME s'est connecté."
    elif [ "$STATUS" == "DISCONNECTED" ]; then
        notify-send -u normal "USB Detector" "Un périphérique USB s'est déconnecté."
    else
        notify-send -u low "USB Detector" "Statut inconnu : $STATUS"
    fi
done
