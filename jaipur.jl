import .Sys
import Libdl
import Pkg
Pkg

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
    println("File exists at $libname")
    global library = Libdl.dlopen_e(libname)
    if library == C_NULL
        println("Failed to load library.")
    else
        println("Library loaded successfully.")
        println("Performing a test.")

        local c_array = Vector{Cint}(undef, 7)
        local test_result=0
        for i in 1:7
            c_array[i] = i
            test_result+=i
        end

        sumOfCardsGroup_func = Libdl.dlsym(library, :sumOfCardsGroup)
        result = test_result==ccall(sumOfCardsGroup_func, Cint, (Ptr{Cint}, Cint), c_array, 0)
        println("The test resulted in a $result value.")
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
    hand_plA::NTuple{CARD_GROUP_SIZE,Cint} #State/secret
    hand_plB::NTuple{CARD_GROUP_SIZE,Cint} #State/secret
    
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

initGameData = Libdl.dlsym(library, :initLibGameDataScratch)
freeGameData = Libdl.dlsym(library, :freeLibGameData)
freeGameData = Libdl.dlsym(library, :freeLibGameData)
freeGameData = Libdl.dlsym(library, :freeLibGameData)
freeGameData = Libdl.dlsym(library, :freeLibGameData)
freeGameData = Libdl.dlsym(library, :freeLibGameData)
freeGameData = Libdl.dlsym(library, :freeLibGameData)

function create_game_data()::Ptr{GameData}
    return ccall(initGameData, Ptr{GameData}, (Cuint,),0)
end
function free_game_data(ptr::Ptr{GameData})::Cvoid
    return ccall(freeGameData, Cvoid, (Ptr{GameData},),ptr)
end
function free_game_data(ptr::Ptr{GameData})::Cvoid
    return ccall(freeGameData, Cvoid, (Ptr{GameData},),ptr)
end
function free_game_data(ptr::Ptr{GameData})::Cvoid
    return ccall(freeGameData, Cvoid, (Ptr{GameData},),ptr)
end
function free_game_data(ptr::Ptr{GameData})::Cvoid
    return ccall(freeGameData, Cvoid, (Ptr{GameData},),ptr)
end
function free_game_data(ptr::Ptr{GameData})::Cvoid
    return ccall(freeGameData, Cvoid, (Ptr{GameData},),ptr)
end
function free_game_data(ptr::Ptr{GameData})::Cvoid
    return ccall(freeGameData, Cvoid, (Ptr{GameData},),ptr)
end
#Tests
game_data_ptr=create_game_data()
# Convert the pointer to a Julia struct
if game_data_ptr == C_NULL
    error("Failed to allocate GameData struct")
end
# game_data = unsafe_load(game_data_ptr)
was_initialized_ptr = Ptr{Cint}(game_data_ptr)
was_initialized = unsafe_load(was_initialized_ptr)
println("was_initialized: $was_initialized")
# println(unsafe_load(game_data_ptr::Ptr{Cint},1))
free_game_data(game_data_ptr)

# Libdl.dlclose(library)
