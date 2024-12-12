#!/bin/python3

import os
import sys
import subprocess

def IsLibInstalled(packet):
    try:
        subprocess.check_output(["pip", "show", packet])
        return True
    except subprocess.CalledProcessError:
        return False

def LibInstall(packet):
    result = subprocess.run(["pip3", "install", packet], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    return False if result.returncode !=0 else True

def parcours_dossier(path):
    fichiers = []
    dossiers = []

    for file_folder in os.listdir(path):
        element_path = os.path.join(path, file_folder)
        if os.path.isfile(element_path):
            if not file_folder.endswith(".srt"):
                fichiers.append(os.path.basename(element_path))
        elif os.path.isdir(element_path):
            dossiers.append(os.path.basename(element_path))
            sous_dossiers, sous_fichiers = parcours_dossier(element_path)
            fichiers += sous_fichiers
            dossiers += sous_dossiers
    return dossiers, fichiers

if __name__ == '__main__':
	try:
		packet = "pyfiglet"
		check = True
		if not IsLibInstalled(packet):
			if not LibInstall(packet):
				print(f"Impossible d'installer le packet : {packet}")
				print("Voulez vous continuer sans ? (Y/n)")
				choice = input("> ")
				if choice.lower() == 'n':
					exit(1)
				elif choice.lower() == 'y':
					check = False

		if check:
			import pyfiglet
			ascii_banner = pyfiglet.figlet_format("ScanFile")
			print(ascii_banner)
		print("Saisir le chemin d'accès à analyser:")
		PATH_parent = input("> ")
		exit(0) if PATH_parent.lower() == 'exit' else None

		if PATH_parent[-1] == '/' or PATH_parent[-1] == '\\':
			if os.name == 'nt':
				PATH_check = PATH_parent + "list.txt"
			else:
				PATH_check = PATH_parent + "list.txt"
		else:
			if os.name == 'nt':
				PATH_check = PATH_parent + '\\' + "list.txt"
			else:
				PATH_check = PATH_parent + '/' + "list.txt"

		try:
			list_fichier_dossier = os.listdir(PATH_parent)
		except:
			print("[-] Le chemin d'accès est incorrect.")
			sys.exit()

		print("\n[*] Analyse en cours ...")
		dossiers, fichiers = parcours_dossier(PATH_parent)

		lines = []
		doublons = []
		max_length = max(len(fichier) for fichier in fichiers)
		total_width = max_length + 4

		with open(PATH_check, 'w') as f:
			f.write(total_width * "#" + "\n")
			for fichier in fichiers:
				tab = total_width - len(fichier) - 2
				if fichier in lines:
					f.write("# " + fichier + " " * (tab - 1) + "# doublons\n")
					doublons.append(fichier)
				else:
					f.write("# " + fichier + " " * (tab - 1) + "#\n")
				lines.append(fichier)
			f.write(total_width * "#" + "\n")
		print(f"[!] {len(fichiers)} fichiers et {len(dossiers)} dossiers analysé.")

		if len(doublons) == 0:
			print(f"[-] Aucun doublons trouvé.")
		else:
			print(f"[!] {len(doublons)} doublons trouvé")
			print(f"Pour plus d'information voir {PATH_check}")
	except KeyboardInterrupt:
		print("[!] Intéruption du script.")
