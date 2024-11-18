include("jaipur.jl")

## For the particular rules of the game, read the README.md
## You can start as many games as you want with
seed=Cuint(42)
game=create_game_data(seed)

## You can clone a game by doing
game_clone=clone_game_data(game)


## You can replicate a game state with different secret states by doing
new_seed=Cuint(42)
game_replicate=duplicate_game_data(game, new_seed)


## There are four game actions. You can perform them by setting a string vector with the action arguments 
### The take good action has two arguments, the action string and the desired good string
take_silver=[TAKE_GOOD_STR, SILVER_STR]
