#!/bin/python3

import matplotlib.pyplot as plt
import subprocess

df = subprocess.check_output("df -h | awk '/\/dev\/dm-0/ { print $2, $3, $4 }'", shell=True).decode().replace('\n', '').split(' ')

size = df[0][:-1]
use = df[1][:-1]
free = df[2][:-1]
system = round(int(size) - (int(use) + int(free)), 1)

use_label = "Place occupé :\n" + str(use) + df[1][-1]
free_label = "Place restante :\n" + str(free) + df[2][-1]
system_label = "Système :\n" + str(system) + df[2][-1]

# Données pour le diagramme en rond (exemples)
labels = [use_label, free_label, system_label]
sizes = [use, free, system]  # Les tailles représentent la proportion de chaque catégorie
colors = ["red", "blue", "purple"]  # Couleurs des parts de gâteau
explode = (0, 0.1, 0)  # Éclatement d'une part (0.1 signifie qu'elle est légèrement éloignée du reste)

# Titre de la fentre
plt.figure("Storage", facecolor='lightgray')

# Créer le diagramme en rond
plt.pie(sizes, labels=labels, colors=colors, explode=explode, autopct='%1.1f%%', startangle=140)

# Titre du diagramme
plt.title(f"Place total de la partition /home :\n{size}{df[0][-1]}")

# Afficher le diagramme
plt.axis("equal")  # Garantit que le diagramme est un cercle
plt.show()
