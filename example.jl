include("jaipur.jl")

## For the particular rules of the game, read the README.md
## You can start as many games as you want with
seed=42
game=create_game_data(seed)

## You can clone a game by doing
game_clone=clone_game_data(game)

## You can replicate a game state with different secret states by doing
new_seed=42
game_replicate=duplicate_game_data(game, new_seed)

## There are four game actions. You can perform them by setting a string vector with the action arguments 
### The exchange action has three arguments, the action, the cards you want to give back and the cards you want to take
exchange=[EXCHANGE_STR,LEATHER_STR*DIAMOND_STR,SPICE_STR*LEATHER_STR]
result_flags=process_game_action(game_clone,exchange,false) 
auto_round_management(game_clone,result_flags)
### The take all camels action has only one argument
take_all_camels=[TAKE_CAMELS_STR]
result_flags=process_game_action(game_clone,take_all_camels,false) 
auto_round_management(game_clone,result_flags)

### The take good action has two arguments, the action string and the desired good string
take_diamond=[TAKE_GOOD_STR, DIAMOND_STR]
result_flags=process_game_action(game_clone,take_diamond,false) #Last bool prints errors
#Always store the flags! They tell you what happened during, after or if even the action itself happened
auto_round_management(game_clone,result_flags) #You can set-up your own print functions for round, game or player winning.

### The sell action has three arguments, the action, the type of card to sell, and the number of cards to sell.
sale=[SELL_GOOD_STR,LEATHER_STR,string(2)]
result_flags=process_game_action(game_clone,sale,false)
auto_round_management(game_clone,result_flags) #You can set-up your own print functions for round, game or player winning.

#Finally, remember to free all the games you created!
game_clone=free_game_data(game_clone) #Advised to assign too, to null the pointer and avoid double freeing
game=free_game_data(game)
game_replicate=free_game_data(game_replicate)
println("End")