#!/bin/python3

print("[*] Initialisation des bibliothèques. Cette opération peut prendre un peu de temps.")
from rembg import remove
from pathlib import Path
from PIL import Image
import sys
import re

GREEN = "\033[32m"
RED = "\033[31m"
RESET = "\033[0m"

print("Saisir le chemin d'accès vers l'image dont le fond doit être enlevé. (absolu ou relatif, ex : groupe_froid.png)")
inputPath = input('>')

if not Path(inputPath).exists():
	print(f"{RED}[-] Fichier introuvable.{RESET}")
	input("PRESS ENTER")
	sys.exit(1)
elif not inputPath.endswith(".png"):
	print(f"{RED}[-] Le fichier doit avoir l'extention PNG, pour convertir l'image : https://convertio.co/fr/{RESET}")
	input("PRESS ENTER")
	sys.exit(1)

print("Saisir le chemin d'accès dans lequel sera stocker l'image sans fond. (absolu ou relatif, ex : groupe_froid_out.png)")
print("Par défaut (saisir enter) le chemin est le même que celui d'origine avec _out à la fin.")
outputPath = input('>')

if outputPath == "":
	outputPath = re.sub(r'\.(?=[^.]*$)', '_out.', inputPath)

image = Image.open(inputPath)
print("[*] Extraction de l'image...")
output = remove(image)
output.save(outputPath)
print(f"{GREEN}[+] Background supprimé. La nouvelle image est stocké dans {outputPath}.{RESET}")
input("PRESS ENTER")
