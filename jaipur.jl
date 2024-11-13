import .Sys
import Libdl

# Determine the appropriate library file name based on the operating system
libname = ""
if Sys.iswindows()
    libname = abspath("bin", "libjaipur.dll")
elseif Sys.islinux()
    libname = "./bin/libjaipur.so"
else
    libname = "./bin/libjaipur.dylib"
end

# Check if the library file exists and try to load it
if isfile(libname)
    # println("File exists at $libname")
    global library = Libdl.dlopen_e(libname)
    if library == C_NULL
        println("Failed to load library.")
    else
        println("Library loaded successfully.")
        println("Testing the dynamic library...")

        local c_array = Vector{Cint}(undef, 7)
        local test_result=0
        for i in 1:7
            c_array[i] = i
            test_result+=i
        end

        sumOfCardsGroup_func = Libdl.dlsym(library, :sumOfCardsGroup)
        result = test_result==ccall(sumOfCardsGroup_func, Cint, (Ptr{Cint}, Cint), c_array, 0)
        if result
            println("The test passed.")
        else
            println("The test failed.")
        end
    end
else
    error("Library not found at $libname")
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
const diamonds=0
const golds=1
const silvers=2
const spices=3
const cloths=4
const leather=5
const camels=6

#Info/data flags

const DATA_WAS_INIT          =1 << 0 
const TURN_HAPPENED_FLAG     =1 << 1

const DATA_NOT_INIT_FLAG     =1 << 2
const TOO_FEW_ARGS_FLAG      =1 << 3
const ERROR_PRINTING_FLAG    =1 << 4
const TOO_MANY_C_MARKET_FLAG =1 << 5
const TOO_MANY_C_HAND_FLAG   =1 << 6


const TOO_FEW_C_MARKET_FLAG =1 << 7  
const TOO_FEW_C_HAND_FLAG   =1 << 8  
const ARGS_MISS_MATCH_FLAG  =1 << 9   
const ARG_OVERFLOW_FLAG     =1 << 10  

const NOT_ALLOWED_FLAG      =1 << 11
const MISSING_CARD_FLAG     =1 << 12
const MIXING_GOODS_CAMELS   =1 << 13
const DATA_CORRUPTED_FLAG   =1 << 14
const DATA_OKAY_FLAG        =1 << 15
const DRAW_FLAG             =1 << 16

const NO_CAMELS             =1 << 17
const GAME_OVER             =1 << 18
const ROUND_OVER            =1 << 19
const NO_GAME_PRINT_FLAG    =1 << 20
const TOO_FEW_CARDS_SALE    =1 << 21

const CANNOT_SELL_CAMELS    =1 << 22
const ONLY_PRINT_HAND       =1 << 23
const CARD_DOES_NOT_EXIST   =1 << 24
const LOGIC_ERROR_FLAG      =1 << 25
const ONLY_PRINT_MARKET     =1 << 26

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

initGameDataScratch = Libdl.dlsym(library, :initLibGameDataScratch)
initGameDataCustom = Libdl.dlsym(library, :initLibGameDataCustom)
cloneGameData = Libdl.dlsym(library, :cloneLibGameData)
processAction = Libdl.dlsym(library, :processLibAction)
freeGameData = Libdl.dlsym(library, :freeLibGameData)

function create_game_data(seed::Cuint=Cuint(0))::Ptr{GameData}
    #Function wrapper to create a random game.
    #All allocations in the library are currently handled by malloc()
    #Seed=0 will give you a random seed
    return ccall(initGameDataScratch, Ptr{GameData}, (Cuint,),seed)
end

function duplicate_game_data(game_ptr::Ptr{GameData},seed::Cuint=Cuint(0))::Ptr{GameData}
    #Function wrapper to create a game in the same public state, but different secret state.
    #All allocations in the library are currently handled by malloc()
    #Seed=0 will give you a random seed
    return ccall(initGameDataCustom, Ptr{GameData}, (Ptr{GameData},Cuint),game_ptr,seed)
end

function clone_game_data(game_ptr::Ptr{GameData})::Ptr{GameData}
    #Function wrapper to create an exact copy of the game
    #All allocations in the library are currently handled by malloc()
    return ccall(cloneGameData, Ptr{GameData}, (Ptr{GameData},),game_ptr)
end

function process_game_action(game_ptr::Ptr{GameData},argc::Cint, argv::Vector{Cstring},error_flag::Cint)::Cint
    #Function wrapper to perform actions in the game
    #It returns an int with flag bits set. Look in the constants for checking
    return ccall(processAction, Cint, (Ptr{GameData},Cint,Vector{Cstring},Cint),game_ptr,argc,argv, error_flag)
end

function free_game_data(game_ptr::Ptr{GameData})::Cvoid
    return ccall(freeGameData, Cvoid, (Ptr{GameData},),game_ptr)
end
#Tests
game_data_ptr=create_game_data(Cuint(0))
# Convert the pointer to a Julia struct
if game_data_ptr == C_NULL
    error("Failed to allocate GameData struct")
end
# game_data = unsafe_load(game_data_ptr)
game_data = unsafe_load(game_data_ptr)
println("game_data: $game_data")
data=Cuint(42)
println("Cuint: $data")
# println(unsafe_load(game_data_ptr::Ptr{Cint},1))
free_game_data(game_data_ptr)

# Libdl.dlclose(library)
