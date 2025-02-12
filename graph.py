import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm
import matplotlib.image as mpimg

# Définition des couleurs pour chaque rang
RANK_S = (255/255, 127/255, 127/255)  # Couleur pour le rang S
RANK_A = (179/255, 239/255, 120/255)  # Couleur pour le rang A
RANK_B = (119/255, 236/255, 236/255)  # Couleur pour le rang B
RANK_C = (177/255, 118/255, 237/255)  # Couleur pour le rang C

def read_stats_from_file(filename):
    with open(filename, 'r') as file:
        lines = [line.strip() for line in file.readlines() if line.strip()]

    # Lire mu et sigma
    mu_sigma_line = lines[0]
    mu = float(mu_sigma_line.split('=')[1].split(',')[0].strip())
    sigma = float(mu_sigma_line.split('=')[2].split(',')[0].strip())

    # Lire les joueurs (éviter les lignes contenant "Mu", "Sigma", etc.)
    players = []
    points = []
    for line in lines:
        data = line.split()
        if len(data) >= 4 and data[1].replace('.', '', 1).isdigit():  # Vérifie si le second élément est un nombre
            player_name = data[0]
            try:
                player_points = float(data[3])  # Lire la colonne des points
                players.append(player_name)
                points.append(player_points)
            except ValueError:
                continue  # Ignore les lignes mal formatées

    return mu, sigma, players, points

def assign_rank_color(mu, sigma, points):
    """Assigner une couleur en fonction du rang basé sur mu et sigma"""
    colors = []
    for point in points:
        # Utiliser directement la comparaison des points avec mu et sigma
        if point > mu + sigma:
            colors.append(RANK_S)
        elif point > mu and point <= mu + sigma:
            colors.append(RANK_A)
        elif point < mu and point >= mu - sigma:
            colors.append(RANK_B)
        else:
            colors.append(RANK_C)
    return colors

def plot_normal_distribution(mu, sigma, players, points, background_image_path):
    # Créer une plage de valeurs pour l'axe des X (les scores)
    x = np.linspace(mu - 4*sigma, mu + 4*sigma, 1000)
    
    # Calculer la courbe de la loi normale
    y = norm.pdf(x, mu, sigma)
    
    # Créer le graphique avec une image en arrière-plan
    fig, ax = plt.subplots(figsize=(10, 6))  # Spécifier la taille de la figure
    
    # Charger l'image d'arrière-plan
    img = mpimg.imread(background_image_path)
    
    # Définir l'image de fond pour couvrir toute la fenêtre
    ax.imshow(img, aspect='auto', extent=[x.min(), x.max(), 0, max(y) * 1.2], alpha=0.4, zorder=-1)
    
    # Tracer la courbe normale
    ax.plot(x, y, label="Loi normale (mu={:.2f}, sigma={:.2f})".format(mu, sigma), color='black')
    
    # Assigner des couleurs selon les rangs
    colors = assign_rank_color(mu, sigma, points)
    legend_entries = []

    # Ajouter les joueurs sur le graphique avec des couleurs uniques
    for player, point, color in zip(players, points, colors):
        # Calculer la position de la densité pour ce joueur
        y_position = norm.pdf(point, mu, sigma)
        
        # Ajouter le point du joueur sur la courbe
        ax.scatter(point, y_position, color=color, zorder=5)
        
        # Ajouter le nom du joueur à côté de son point avec une taille de police plus grande
        ax.text(point, y_position, player, ha='center', va='bottom', color='white', fontsize=12, fontweight='bold', 
                bbox=dict(facecolor=color, alpha=0.7, edgecolor='none', boxstyle='round,pad=0.3'))

        # Ajouter une entrée à la légende
        legend_entries.append((player, color, point, y_position))

    # Ajouter des labels et un titre
    ax.set_xlabel('Points')
    ax.set_ylabel('Densité de probabilité')
    ax.set_title('Distribution normale des joueurs')

    # Ajouter des grandes lignes pour chaque écart-type jusqu'à la fin de la courbe
    for i in range(-4, 5):
        ax.axvline(mu + i * sigma, color='gray', linestyle='--', label=f'$\mu + {i}$σ' if i != 0 else '$\mu$')

    # Créer une légende à côté du graphique avec uniquement mu et sigma
    ax.legend([f"$\mu = {mu:.2f}$", f"$\sigma = {sigma:.2f}$"], loc='upper right')

    # Ajouter une légende détaillée avec les informations des joueurs
    from matplotlib.offsetbox import AnchoredText
    legend_text = "\n".join([f"{player}: {point:.2f}" for player, color, point, y_position in legend_entries])
    anchored_text = AnchoredText(legend_text, loc='upper left', prop={'size': 8}, frameon=True)
    ax.add_artist(anchored_text)

    # Ajuster l'espace autour du graphique pour s'assurer que l'image de fond remplit toute la fenêtre
    plt.tight_layout()  # Ajuste les marges pour remplir toute la fenêtre

    # Afficher le graphique
    plt.show()

# Exemple d'utilisation avec un fichier (remplace 'stats.txt' par ton fichier et 'background.png' par l'image de fond)
mu, sigma, players, points = read_stats_from_file('stats.txt')
plot_normal_distribution(mu, sigma, players, points, 'background.jpg')
