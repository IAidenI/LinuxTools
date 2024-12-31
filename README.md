# LinuxTools

**Une collection de commandes pour Linux, développés pour faciliter diverses tâches.**

---

## Outils disponibles

### 1. [`perm`](https://github.com/IAidenI/LinuxTools/tree/main/Permissions)
- **Description** : Interprète et convertit les permissions de fichiers UNIX/Linux (ex. `rwxr-xr-x`) en formats octal et binaire.
- **Fonctionnalités** :
  - Description détaillée des droits associés.
  - Mode interactif et cheat sheets.
  - Options CLI avec une interface colorée pour une meilleure lisibilité.
- **Utilisation idéale** : Simplifier l’analyse et la manipulation des permissions.

---

### 2. [`store`](https://github.com/IAidenI/LinuxTools/tree/main/Storage/V2)
- **Description** : Affiche les informations des systèmes de fichiers montés sur Linux en lisant `/proc/mounts`.
- **Fonctionnalités** :
  - Lecture des points de montage, types, tailles, et espaces utilisés.
  - Calcul des pourcentages d’utilisation avec des barres de progression colorées.
  - Distinction entre systèmes locaux et dispositifs spéciaux.
- **Utilisation idéale** : Visualisation claire et informative des systèmes de fichiers.

---

### 3. [`raddr`](https://github.com/IAidenI/LinuxTools/tree/main/ReverseAddress)
- **Description** : Manipule des chaînes hexadécimales en les inversant selon différents formats.
- **Fonctionnalités** :
  - Prise en charge de formats variés (ex. `0xf7f5523e` ou `\xf7\xf5\x52\x3e`).
  - Vérification de validité des entrées et options CLI intuitives.
  - Affichage des résultats avec informations claires.
- **Utilisation idéale** : Transformation et manipulation avancée des données hexadécimales.

---

### 4. [`color`](https://github.com/IAidenI/LinuxTools/tree/main/color_list)
- **Description** : Illustre l’utilisation des codes ANSI pour styliser du texte dans la console.
- **Fonctionnalités** :
  - Affichage des couleurs standard (16 couleurs) et RGB (0-255).
  - Démonstration des styles de texte (gras, souligné, italique, etc.).
  - Légende explicative pour chaque style.
- **Utilisation idéale** : Styliser du texte dans les scripts ou la console.

---

### 5. [`storeV1`](https://github.com/IAidenI/LinuxTools/tree/main/Storage/V1)
- **Description** : Affiche l'état de l'espace disque de la partition racine (`/`).
- **Fonctionnalités** :
  - Barre de progression colorée (vert, jaune, rouge) pour représenter l’espace utilisé.
  - Calcul et affichage des pourcentages d’espace total, utilisé, et disponible.
- **Utilisation idéale** : Monitoring simple de l’espace disque.

---

### 6. [`storage.py`](https://github.com/IAidenI/LinuxTools/blob/main/StorageGUI/storage.py)
- **Description** : Génère un diagramme circulaire pour visualiser l’utilisation de l’espace disque.
- **Utilisation idéale** : Analyse visuelle de l’utilisation de l’espace disque.

---

### 7. [`autoTOR.py`](https://github.com/IAidenI/LinuxTools/blob/main/IpChange/autoTOR.py)
- **Description** : Automatise l’anonymat en ligne via Tor.
- **Fonctionnalités** :
  - Personnalisation de la fréquence de rotation des adresses IP.
  - Configuration des proxys.
  - Inspiré de [Auto_Tor_IP_changer](https://github.com/FDX100/Auto_Tor_IP_changer).
- **Utilisation idéale** : Assurer un anonymat en ligne avec Tor.

---

### 8. [`del_EXTERNALLY-MANAGED.sh`](https://github.com/IAidenI/LinuxTools/blob/main/del_EXTERNALLY-MANAGED.sh)
- **Description** : Supprime le fichier `/usr/lib/python3.11/EXTERNALLY-MANAGED` pour activer `pip`.
- **Utilisation idéale** : Gérer les dépendances Python sur un système Linux.

---

### 9. [`update.sh`](https://github.com/IAidenI/LinuxTools/blob/main/update.sh)
- **Description** : Met à jour tout le système Linux.
- **Fonctionnalités** :
  - Vérifie que le fichier `/usr/lib/python3.11/EXTERNALLY-MANAGED` est désactivé.
- **Utilisation idéale** : Maintenir un système Linux à jour.

---

### 10. [`Check_Film.py`](https://github.com/IAidenI/LinuxTools/blob/main/Check_Film.py)
- **Description** : Scanne un dossier et ses sous-dossiers pour répertorier les fichiers et dossiers.
- **Fonctionnalités** :
  - Exclusion des fichiers `.srt`.
  - Génération d’un fichier `list.txt` avec résumé des doublons.
- **Utilisation idéale** : Organisation et audit des fichiers multimédias.

---

### 11. [`BackgroundRemover.py`](https://github.com/IAidenI/LinuxTools/blob/main/BackgroundRemover/BackgroundRemover.py)
- **Description** : Supprime le fond d’une image PNG.
- **Fonctionnalités** :
  - Génération d’images PNG avec fond transparent.
- **Utilisation idéale** : Création rapide de visuels pour le web ou le design.

---

### 12. [`USBDetector.sh`](https://github.com/IAidenI/LinuxTools/tree/main/USBDetector.sh)
- **Description** : Surveille en temps réel la connexion et la déconnexion des périphériques USB sur un système Linux.
- **Fonctionnalités** :
  - Surveillance continue des événements USB en utilisant `inotifywait`.
  - Affichage de notifications lorsqu'un périphérique est connecté ou déconnecté.
  - Identification du fabricant (vendor) du dernier périphérique connecté.
  - Gestion des erreurs lorsque les fichiers système requis ne sont pas disponibles.
- **Utilisation idéale** :
  - Suivre et identifier les périphériques USB branchés sur le système pour des raisons de sécurité ou de gestion des périphériques.
> Est un projet en lien avec [`usb_monitor`](https://github.com/IAidenI/Linux-Modules/blob/main/bin/USBMonitor/usb_monitor.c), tout seul il ne sert à rien.

---

## Installation

1. **Pré-requis** :
   - [Python](https://www.python.org/) installé sur votre machine.
   - Les bibliothèques nécessaires (peuvent être installées via `pip`).

2. **Cloner le dépôt** :
   ```bash
   git clone https://github.com/votre_nom/LinuxTools.git
   cd LinuxTools
