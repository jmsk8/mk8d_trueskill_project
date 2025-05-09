#!/bin/bash
# Installer un environnement virtuel et les dépendances
python3 -m venv Python
source Python/bin/activate
pip install trueskill
echo "Installation de ./venv/bin/python3 Trueskill.py terminée."
