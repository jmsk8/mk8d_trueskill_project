from trueskill import Rating, quality_1vs1, rate
import trueskill
import re

def load_ratings_from_file(file_path):
    ratings = {}
    positions = {}
    
    with open(file_path, 'r') as file:
        for line in file:
            match = re.match(r"(\w+) = mu=([\d\.]+), sigma=([\d\.]+) pos=(\d+)", line.strip())
            if match:
                player_name = match.group(1)
                mu = float(match.group(2))
                sigma = float(match.group(3))
                pos = int(match.group(4))
                ratings[player_name] = trueskill.Rating(mu=mu, sigma=sigma)
                positions[player_name] = pos
    
    return ratings, positions

def update_ratings(ratings, positions):
    sorted_players = sorted(ratings.keys(), key=lambda x: positions[x])
    player_ratings = [[ratings[player]] for player in sorted_players]
    ranks = [positions[player] for player in sorted_players]
    
    new_ratings = rate(player_ratings, ranks=ranks)
    
    updated_ratings = {sorted_players[i]: new_ratings[i][0] for i in range(len(sorted_players))}
    
    return updated_ratings

def save_ratings_to_file(file_path, ratings):
    with open(file_path, 'w') as file:
        for player, rating in ratings.items():
            file.write(f"{player} = mu={rating.mu:.3f}, sigma={rating.sigma:.3f}\n")

file_path = 'data/tmp_data.log'
ratings, positions = load_ratings_from_file(file_path)

#print("Ratings avant mise à jour:")
#for player, rating in ratings.items():
#    position = positions.get(player, "N/A")  
#    print(f"{player}: mu={rating.mu:.3f}, sigma={rating.sigma:.3f}, position={position}")

ratings = update_ratings(ratings, positions)

save_ratings_to_file(file_path, ratings)

#print("\nRatings après mise à jour:")
#for player, rating in ratings.items():
#    print(f"{player}: mu={rating.mu:.3f}, sigma={rating.sigma:.3f}")
