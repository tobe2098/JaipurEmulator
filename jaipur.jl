import .Sys
import Libdl

# Determine the appropriate library file name based on the operating system
libname = "libjaipur"

if Sys.iswindows()
    library_name=libname*".dll"
    library_name = joinpath("bin", library_name)
elseif Sys.islinux()
    library_name = "./bin/libjaipur.so"
else
    library_name = "./bin/libjaipur.dylib"
end

# Check if the library file exists and try to load it
if isfile(library_name)
    # println("File exists at $libname")
    global library = Libdl.dlopen_e(library_name)
    if library == C_NULL
        println("Failed to load library.")
    else
        println("Library loaded successfully.")
        print("Testing the dynamic library linking...")

        local c_array = Vector{Cint}(undef, 7)
        local test_result=0
        for i in 1:7
            c_array[i] = i
            test_result+=i
        end

        sumOfCardsGroup_func = Libdl.dlsym(library, :sumOfCardsGroup)
        result = test_result==ccall(sumOfCardsGroup_func, Cint, (Ptr{Cint}, Cint), c_array, 0)
        if  !result
            error("The test of the dynamic library failed")
        end
        print("OK\n")
    end
else
    error("Library not found at $library_name")
end
#Constants
# Define the necessary constants
const TRUE =1
const FALSE =0
const GOOD_TYPES = 6
const BONUS_TOKEN_TYPES = 3
const MAX_BONUS_TOKENS = 6
const BONUS_TOKENS_DATA_ARRAY = 9
const BONUS_TOKENS_PER_VALUE = 2
const FINISHED_GOODS_LIMIT = 3
const CAMEL_TOKEN_VAL = 5
const CAMELS_TOTAL = 11
const SEALS_TO_WIN = 2
const INITIAL_HAND_SIZE = 5
const MAX_CARDS_HAND = 7
const STARTING_MARKET_CAMELS = 3
const CARDS_IN_MARKET = 5
const DIAMONDS_STARTING_DECK = 6
const GOLD_STARTING_DECK = 6
const SILVER_STARTING_DECK = 6
const SPICE_STARTING_DECK = 8
const CLOTH_STARTING_DECK = 8
const LEATHER_STARTING_DECK = 10
const CAMELS_STARTING_MARKET = 3
const CAMELS_STARTING_DECK = CAMELS_TOTAL-CAMELS_STARTING_MARKET
const DIAMONDS_TOKEN_SIZE=DIAMONDS_STARTING_DECK-1
const GOLD_TOKEN_SIZE=GOLD_STARTING_DECK-1
const SILVER_TOKEN_SIZE=SILVER_STARTING_DECK-1
const SPICE_TOKEN_SIZE=SPICE_STARTING_DECK-1
const CLOTH_TOKEN_SIZE=CLOTH_STARTING_DECK-1
const LEATHER_TOKEN_SIZE=LEATHER_STARTING_DECK-1
const DECK_SIZE = 55-CAMELS_STARTING_MARKET #Assumes three camels are already out
const CARD_GROUP_SIZE=7
const diamonds=0 +1#Julia indexing is 1-based
const golds=1+1#Julia indexing is 1-based
const silvers=2+1#Julia indexing is 1-based
const spices=3+1#Julia indexing is 1-based
const cloths=4+1#Julia indexing is 1-based
const leather=5+1#Julia indexing is 1-based
const camels=6+1#Julia indexing is 1-based

const PLAYER_A_NUM =0
const PLAYER_B_NUM =1

#Info/data flags

const DATA_WAS_INIT::Cint          =1 << 0 
const TURN_HAPPENED_FLAG::Cint     =1 << 1
const DATA_NOT_INIT_FLAG::Cint     =1 << 2
const TOO_FEW_ARGS_FLAG::Cint      =1 << 3
const ERROR_PRINTING_FLAG::Cint    =1 << 4
const TOO_MANY_C_MARKET_FLAG::Cint =1 << 5
const TOO_MANY_C_HAND_FLAG::Cint   =1 << 6
const TOO_FEW_C_MARKET_FLAG::Cint  =1 << 7  
const TOO_FEW_C_HAND_FLAG::Cint    =1 << 8  
const ARGS_MISS_MATCH_FLAG::Cint   =1 << 9   
const ARG_OVERFLOW_FLAG::Cint      =1 << 10  
const NOT_ALLOWED_FLAG::Cint       =1 << 11
const MISSING_CARD_FLAG::Cint      =1 << 12
const MIXING_GOODS_CAMELS::Cint    =1 << 13
const DATA_CORRUPTED_FLAG::Cint    =1 << 14
const DATA_OKAY_FLAG::Cint         =1 << 15
const DRAW_FLAG::Cint              =1 << 16
const NO_CAMELS::Cint              =1 << 17
const GAME_OVER::Cint              =1 << 18
const ROUND_OVER::Cint             =1 << 19
const NO_GAME_PRINT_FLAG::Cint     =1 << 20
const TOO_FEW_CARDS_SALE::Cint     =1 << 21
const CANNOT_SELL_CAMELS::Cint     =1 << 22
const ONLY_PRINT_HAND::Cint        =1 << 23
const CARD_DOES_NOT_EXIST::Cint    =1 << 24
const LOGIC_ERROR_FLAG::Cint       =1 << 25
const ONLY_PRINT_MARKET::Cint      =1 << 26
const PLAYER_A_WINS::Cint          =1 << 27

#Actions
const EXCHANGE_STR="-e"
const TAKE_GOOD_STR="-t"
const SELL_GOOD_STR="-s"
const TAKE_CAMELS_STR="-c"

#Card strings
const DIAMOND_STR="d"
const GOLD_STR="g"
const SILVER_STR="s"
const SPICE_STR="p"
const CLOTH_STR="h"
const LEATHER_STR="l"
const CAMELS_STR="c"



#Define the data struct for the library
struct PlayerScore 
  points::Cint
  no_bonus_tokens::Cint
  no_goods_tokens::Cint
  seals::Cint
end
# println(Core.sizeof(PlayerScore))
# println(Base.isbitstype(PlayerScore))
# Base.isbitstype(::Type{PlayerScore}) = true
# Base.isbits(::PlayerScore) = true

struct  GameData 
    init::Cint #State
    seed::Cuint #Secret
    turn_of::Cint #State
    
    market::NTuple{CARD_GROUP_SIZE,Cint} #State
    hand_plA::NTuple{CARD_GROUP_SIZE,Cint} #State
    hand_plB::NTuple{CARD_GROUP_SIZE,Cint} #State
    
    playerA::PlayerScore #State
    playerB::PlayerScore #State
    
    good_tk_ptrs::NTuple{GOOD_TYPES,Cint} #State
    
    bonus_tk_ptrs::NTuple{BONUS_TOKEN_TYPES,Cint} #State
    bonus_tk_arrays::NTuple{BONUS_TOKEN_TYPES, NTuple{MAX_BONUS_TOKENS, Cint}}#Secret

    deck_ptr::Cint #State
    deck::NTuple{DECK_SIZE,Cchar}#Secret
    
    #This are input vars only
    cards_in_deck::Cint #State
    good_tks::NTuple{GOOD_TYPES,Cint} #State
    bonus_tks::NTuple{BONUS_TOKEN_TYPES,Cint} #State
    bonus_used::NTuple{BONUS_TOKENS_DATA_ARRAY,Cint} #State
end
# game_data=GameData
# for (i, field) in enumerate(fieldnames(GameData))
#     offset = fieldoffset(GameData, i)
#     println("Field: $(field), Offset: $(offset), Type: $(fieldtype(GameData, field))")
# end
@assert(Core.sizeof(GameData)==368)

# println(Base.isbitstype(GameData))
# println(Core.sizeof(GameData))

# println(Base.isbitstype(GameData))
# initGameDataScratch = Libdl.dlsym(library, :initLibGameDataScratch)
# initGameDataCustom = Libdl.dlsym(library, :initLibGameDataCustom)
# cloneGameData = Libdl.dlsym(library, :cloneLibGameData)
# processAction = Libdl.dlsym(library, :processLibAction)
# freeGameData = Libdl.dlsym(library, :freeLibGameData)

function create_game_data(seed::Cuint=Cuint(0))::Ptr{GameData}
    #Function wrapper to create a random game.
    #All allocations in the library are currently handled by malloc()
    #Seed=0 will give you a random seed
    output_ptr=@ccall libname.initLibGameDataScratch(seed::Cuint)::Ptr{GameData}
    if output_ptr == C_NULL # Could not allocate memory
        throw(OutOfMemoryError())
    end
    return output_ptr
end

function duplicate_game_data(game_ptr::Ptr{GameData},seed::Int64=0)::Ptr{GameData}
    #Function wrapper to create a game in the same public state, but different secret state.
    #All allocations in the library are currently handled by malloc()
    #Seed=0 will give you a random seed
    output_ptr=@ccall libname.initLibGameDataCustom(game_ptr::Ptr{GameData},seed::Cuint)::Ptr{GameData}
    if output_ptr == C_NULL # Could not allocate memory
        throw(OutOfMemoryError())
    end
    return output_ptr
end

function clone_game_data(game_ptr::Ptr{GameData})::Ptr{GameData}
    #Function wrapper to create an exact copy of the game
    #All allocations in the library are currently handled by malloc()
    output_ptr=@ccall libname.cloneLibGameData(game_ptr::Ptr{GameData})::Ptr{GameData}
    if output_ptr == C_NULL # Could not allocate memory
        throw(OutOfMemoryError())
    end
    return output_ptr
end

function process_game_action(game_ptr::Ptr{GameData}, argv::Vector{String},error_print::Bool)::Cint
    #Function wrapper to perform actions in the game
    #It returns an int with flag bits set. Look in the constants for checking
    if game_ptr == C_NULL # Could not allocate memory
        throw(UndefVarError("`game_ptr` not properly allocated GameData"))
    end
    #The function assumes that a non-null pointer is a correctly allocated GameData
    error_flag=0
    if error_print
        error_flag=ERROR_PRINTING_FLAG
    end
    pushfirst!(argv,"jaipur")
    return @ccall libname.processLibAction(game_ptr::Ptr{GameData},length(argv)::Cint,argv::Ptr{Ptr{UInt8}},error_flag::Cint)::Cint
end

function reset_game(game_ptr::Ptr{GameData},seed::Int64=0)::Cvoid
    #Restart the game from scratch with the given seed (or random if seed is 0)
    if game_ptr == C_NULL # Could not allocate memory
        throw(UndefVarError("`game_ptr` not properly allocated GameData"))
    end
    #The function assumes that a non-null pointer is a correctly allocated GameData
    return  @ccall libname.startGame(game_ptr::Ptr{GameData},seed::Cuint)::Cvoid
end

function reset_round(game_ptr::Ptr{GameData},seed::Int64=0)::Cvoid
    if game_ptr == C_NULL # Could not allocate memory
        throw(UndefVarError("`game_ptr` not properly allocated GameData"))
    end
    #The function assumes that a non-null pointer is a correctly allocated GameData
    #Same as reset_game, but seals are kept between rounds, and the turn is determined by the non-winning player
    return  @ccall libname.startNextRound(game_ptr::Ptr{GameData},seed::Cuint)::Cvoid
end

function give_rewards(game_ptr::Ptr{GameData},flags::Cint)::Cvoid
    #Same as reset_game, but seals are kept between rounds, and the turn is determined by the non-winning player
    if game_ptr == C_NULL # Could not allocate memory
        throw(UndefVarError("`game_ptr` not properly allocated GameData"))
    end
    #The function assumes that a non-null pointer is a correctly allocated GameData
    return  @ccall libname.giveRewards(game_ptr::Ptr{GameData},flags::Cint)::Cvoid
end

function is_round_over(flag::Int32)::Bool
    return flag&ROUND_OVER !=0
end

function is_game_over(flag::Int32)::Bool
    return flag&GAME_OVER !=0
end


function did_player_A_win(flag::Int32)::Bool
    return flag&PLAYER_A_WINS !=0
end

function game_over_print()
    print("The game is over, ")
end

function round_over_print()
    print("The round is over, ")
end

function player_A_wins()
    print("player A won!\n")
end

function player_B_wins()
    print("player B won!\n")
end

function round_management(game_ptr::Ptr{GameData},flags::Cint, round_print::Function=round_over_print,game_print::Function=game_over_print,player_A_p::Function=player_A_wins,player_B_p::Function=player_B_wins)::Cvoid
    #This will automatically handle round and game finishing
    if is_round_over(flags)
        if is_game_over(flags)
            game_print()
            reset_game(game_ptr)
        else
            round_print()
            give_rewards(game_ptr,flags)
            reset_round(game_ptr)
        end
        if did_player_A_win(flags)
            player_A_p()
        else
            player_B_p()
        end
    end
end


function free_game_data(game_ptr::Ptr{GameData})::Ptr{GameData}
    # To free
    if game_ptr == C_NULL # Memory was not allocated or already freed
        throw(UndefVarError("`game_ptr` not properly allocated GameData"))
    end
    #The function assumes that a non-null pointer is a C-allocated pointer
    #Returns the null pointer to reassign to your pointer
    return  @ccall libname.freeLibGameData(game_ptr::Ptr{GameData})::Ptr{GameData}
end

function flag_set_bit_positions(flag::Cint)
    flag_str=bitstring(flag)
    println("Flag: $flag_str")
    # For debugging
    positions = []  # Array to store positions of set bits
    pos = 0         # Bit position counter

    while flag > 0
        if flag & 1 == 1
            push!(positions, pos)  # Record the position if bit is set
        end
        flag >>= 1      # Shift bits to the right
        pos += 1     # Increment position counter
    end

    println("Flag bit positions: ", positions)
end
function flag_identifiers(flag::Cint)
    if DATA_WAS_INIT&flag>0
        println("Data was initialized")
    end 
    if TURN_HAPPENED_FLAG&flag>0
        println("Turn happened")
    end
    if DATA_NOT_INIT_FLAG&flag>0
        println("Data was not initialized")
    end
    if TOO_FEW_ARGS_FLAG&flag>0
        println("Too few arguments for the action")
    end
    if ERROR_PRINTING_FLAG&flag>0
        println("Printing errors flag")
    end
    if TOO_MANY_C_MARKET_FLAG&flag>0
        println("Too many cards in the market")
    end
    if TOO_MANY_C_HAND_FLAG&flag>0
        println("Too many cards in hand")
    end
    if TOO_FEW_C_MARKET_FLAG&flag>0
        println("Too few cards in the market")
    end 
    if TOO_FEW_C_HAND_FLAG&flag>0
        println("Too few cards in hand")
    end 
    if ARGS_MISS_MATCH_FLAG&flag>0
        println("Number of exchanged cards does not match")
    end  
    if ARG_OVERFLOW_FLAG&flag>0
        println("Cannot use more than 5 cards for exchanges")
    end  
    if NOT_ALLOWED_FLAG&flag>0
        println("The action is not allowed")
    end
    if MISSING_CARD_FLAG&flag>0
        println("The market does not have that card")
    end
    if MIXING_GOODS_CAMELS&flag>0
        println("You cannot trade cards for camels")
    end
    if DATA_CORRUPTED_FLAG&flag>0
        println("The data is corrupt, does not conform to boundaries")
    end
    if DATA_OKAY_FLAG&flag>0
        println("The data is okay")
    end
    if DRAW_FLAG&flag>0
        println("The round was drawn")
    end
    if NO_CAMELS&flag>0
        println("There are no camels in the market")
    end
    if GAME_OVER&flag>0
        println("The game is over")
    end
    if ROUND_OVER&flag>0
        println("The round is over")
    end
    if NO_GAME_PRINT_FLAG&flag>0
        println("Do not print the game state (ignore this)")
    end
    if TOO_FEW_CARDS_SALE&flag>0
        println("Cannot sell less than 1 card")
    end
    if CANNOT_SELL_CAMELS&flag>0
        println("Cannot sell camels")
    end
    if ONLY_PRINT_HAND&flag>0
        println("Print only the hand (ignore this)")
    end
    if CARD_DOES_NOT_EXIST&flag>0
        println("Card does not exist")
    end
    if ONLY_PRINT_MARKET&flag>0
        println("Print only the market (ignore this)")
    end
    if PLAYER_A_WINS&flag>0
        println("Player A won, if not player B won. Only interpret if round over.")
    end 
end
# Tests for the library's functionality
# println("Testing the library's functionality...")
## Test the pointer is allocated
print("Testing pointer allocation...")
game_data_ptr=create_game_data(Cuint(42))
if game_data_ptr == C_NULL
    error("Failed to allocate GameData struct in the library test")
end
print("OK\n")
## Test loading the data into Julia struct
print("Testing unsafe_load'ing...")
game_data = unsafe_load(game_data_ptr)
if game_data.seed!=Cuint(42) || game_data.init!=1
    error("The data was not properly unsafe_load'ed into Julia")
end
print("OK\n")
## Test the data was properly initialized
print("Testing data initialization...")
flag=process_game_action(game_data_ptr, String[],true)
game_data = unsafe_load(game_data_ptr)
if flag&DATA_OKAY_FLAG==0 || game_data.seed!=Cuint(42)
    # flag_identifiers(flag)
    error("The data was not properly initialized in the library test")
end
print("OK\n")

## Test the exchange function works
print("Testing exchange action...")
action=EXCHANGE_STR
hand_card=LEATHER_STR
market_card=SPICE_STR
action_arr=[action,hand_card,market_card]
flag=process_game_action(game_data_ptr, action_arr,true)
game_data = unsafe_load(game_data_ptr)
if  flag&DATA_OKAY_FLAG==0||flag&TURN_HAPPENED_FLAG ==0||game_data.hand_plB[spices]!=Cint(2)
    # flag_identifiers(flag)
    error("The exchange action test failed in the library test")
end
print("OK\n")
## Test the take camels function works
print("Testing take all camels action...")
action=TAKE_CAMELS_STR
action_arr=[action]
flag=process_game_action(game_data_ptr, action_arr,true)
game_data = unsafe_load(game_data_ptr)
if  flag&DATA_OKAY_FLAG==0||flag&TURN_HAPPENED_FLAG ==0 || game_data.hand_plA[camels]!=Cint(3)
    # flag_identifiers(flag)
    error("The take all camels action test failed in the library test")
end
print("OK\n")

## Test the take goods function works
print("Testing take single good action...")
action=TAKE_GOOD_STR
market_card=DIAMOND_STR
action_arr=[action,market_card]
flag=process_game_action(game_data_ptr, action_arr,true)
game_data = unsafe_load(game_data_ptr)
if  flag&DATA_OKAY_FLAG==0||flag&TURN_HAPPENED_FLAG ==0||game_data.hand_plB[diamonds]!=Cint(2)
    flag_identifiers(flag)
    error("The take single good action test failed in the library test")
end
print("OK\n")

## Test the sell goods function works
print("Testing sell goods action...")
action=SELL_GOOD_STR
hand_card=LEATHER_STR
number_of_sold_cards=string(2)
action_arr=[action,hand_card,number_of_sold_cards]
flag=process_game_action(game_data_ptr, action_arr,true)
game_data = unsafe_load(game_data_ptr)
if  flag&DATA_OKAY_FLAG==0||flag&TURN_HAPPENED_FLAG ==0 || game_data.playerA.points!=Cint(7)
    flag_identifiers(flag)
    error("The sell goods action test failed in the library test")
end
print("OK\n")

# println("game_data: $game_data")

## Test round management
print("Testing round over state...")
flag|=ROUND_OVER
round_management(game_data_ptr, flag,() -> nothing,() -> nothing,() -> nothing,() -> nothing)
game_data=unsafe_load(game_data_ptr)
if game_data.turn_of!=PLAYER_A_NUM || game_data.playerB.seals!=1 
    error("The test of round over failed in the library test")
end
print("OK\n")

print("Testing game over state...")
flag|=ROUND_OVER
flag|=GAME_OVER
flag|=PLAYER_A_WINS
round_management(game_data_ptr, flag,() -> nothing,() -> nothing,() -> nothing,() -> nothing)
game_data=unsafe_load(game_data_ptr)
if  game_data.playerB.seals!=0 
    error("The test of round over failed in the library test")
end
print("OK\n")

# flag_set_bit_positions(flag)
# println(unsafe_load(game_data_ptr::Ptr{Cint},1))
# ref=Ref{Ptr{GameData}}(game_data_ptr)
# ptr=Base.unsafe_convert(Ptr{Ptr{GameData}},ref)
# println(unsafe_load(ptr))
# println(unsafe_load(game_data_ptr).turn_of)
print("Testing pointer freeing...")
game_data_ptr=free_game_data(game_data_ptr)
if game_data_ptr!=C_NULL
    error("The pointer was not properly freed.")
end
print("OK\n")
println("All the tests passed.")
# println(unsafe_load(ptr))
# Libdl.dlclose(library)
